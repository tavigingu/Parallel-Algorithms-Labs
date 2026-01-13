namespace ex02
{
    internal class Program
    {
        static async Task Main(string[] args)
        {
            Requester requester = new Requester("http://localhost:5000/image");
            List<string> urls = new List<string>();
            
            // Start requester task
            Task requesterTask = Task.Run(async () =>
            {
                for (int i = 0; i < 5; i++)
                {
                    ApiResponse response = await requester.GetImageURL();
                    lock (urls)
                    {
                        urls.Add(response.Url);
                    }
                }
            });
            
            // Start downloader task
            Task downloaderTask = Task.Run(async () =>
            {
                HashSet<string> downloaded = new HashSet<string>();
                
                while (true)
                {
                    string url = null;
                    lock (urls)
                    {
                        foreach (var u in urls)
                        {
                            if (!downloaded.Contains(u))
                            {
                                url = u;
                                downloaded.Add(u);
                                break;
                            }
                        }
                    }
                    
                    if (url != null)
                    {
                        try
                        {
                            using (HttpClient client = new HttpClient())
                            {
                                byte[] imageData = await client.GetByteArrayAsync(url);
                                string fileName = $"image_{downloaded.Count}.jpg";
                                await File.WriteAllBytesAsync(fileName, imageData);
                                Console.WriteLine($"[Downloader] Downloaded: {fileName}");
                            }
                        }
                        catch (Exception ex)
                        {
                            Console.WriteLine($"[Downloader] Error: {ex.Message}");
                        }
                    }
                    else
                    {
                        await Task.Delay(100);
                        
                        // Check if requester is done
                        if (requesterTask.IsCompleted)
                        {
                            lock (urls)
                            {
                                if (downloaded.Count >= urls.Count)
                                    break;
                            }
                        }
                    }
                }
            });
            
            await Task.WhenAll(requesterTask, downloaderTask);
            Console.WriteLine("All tasks completed.");
        }
    }
}
