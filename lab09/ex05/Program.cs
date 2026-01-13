using Newtonsoft.Json;
using System.Net;
using SixLabors.ImageSharp;
using SixLabors.ImageSharp.Processing;
using SixLabors.ImageSharp.Drawing.Processing;
using SixLabors.Fonts;

namespace ex05
{
    internal class Program
    {
        static List<string> urlQueue = new List<string>();
        static List<string> downloadedImages = new List<string>();
        static object urlLock = new object();
        static object downloadLock = new object();

        static void Main(string[] args)
        {
            Thread requester = new Thread(RequesterThread);
            Thread downloader = new Thread(DownloaderThread);
            Thread processer = new Thread(ProcesserThread);

            requester.Start();
            downloader.Start();
            processer.Start();

            requester.Join();
            downloader.Join();
            processer.Join();

            Console.WriteLine("All threads completed.");
        }

        static void RequesterThread()
        {
            int waitTime = 1000; // Start with 1 second
            int imageCount = 0;
            const int maxImages = 10; // Get 10 images

            using (WebClient webClient = new WebClient())
            {
                while (imageCount < maxImages)
                {
                    try
                    {
                        string apiResponseJsonString = webClient.DownloadString("http://localhost:5000/image");
                        ApiResponse apiResponse = JsonConvert.DeserializeObject<ApiResponse>(apiResponseJsonString);

                        if (apiResponse.Status == "SUCCESS")
                        {
                            lock (urlLock)
                            {
                                urlQueue.Add(apiResponse.Url);
                                Console.WriteLine($"[Requester] Added URL: {apiResponse.Url}");
                            }
                            waitTime = 1000; // Reset wait time on success
                            imageCount++;
                        }
                        else if (apiResponse.Status == "RETRY-LATER")
                        {
                            Console.WriteLine($"[Requester] Server busy, waiting {waitTime}ms");
                            Thread.Sleep(waitTime);
                            waitTime = Math.Min(waitTime * 2, 32000); // Exponential backoff, max 32 seconds
                        }
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine($"[Requester] Error: {ex.Message}");
                        Thread.Sleep(waitTime);
                        waitTime = Math.Min(waitTime * 2, 32000);
                    }
                }
            }
        }

        static void DownloaderThread()
        {
            using (WebClient webClient = new WebClient())
            {
                while (true)
                {
                    string url = null;
                    lock (urlLock)
                    {
                        if (urlQueue.Count > 0)
                        {
                            url = urlQueue[0];
                            urlQueue.RemoveAt(0);
                        }
                    }

                    if (url != null)
                    {
                        try
                        {
                            string fileName = Path.GetFileName(new Uri(url).LocalPath);
                            byte[] imageData = webClient.DownloadData(url);
                            File.WriteAllBytes(fileName, imageData);
                            
                            lock (downloadLock)
                            {
                                downloadedImages.Add(fileName);
                            }
                            
                            Console.WriteLine($"[Downloader] Downloaded: {fileName}");
                        }
                        catch (Exception ex)
                        {
                            Console.WriteLine($"[Downloader] Error downloading {url}: {ex.Message}");
                        }
                    }
                    else
                    {
                        Thread.Sleep(100);
                        // Check if requester is done (heuristic: no new URLs for a while)
                        lock (urlLock)
                        {
                            if (urlQueue.Count == 0)
                            {
                                Thread.Sleep(2000); // Wait a bit more
                                if (urlQueue.Count == 0)
                                    break; // Exit if still no URLs
                            }
                        }
                    }
                }
            }
        }

        static void ProcesserThread()
        {
            HashSet<string> processedImages = new HashSet<string>();

            while (true)
            {
                string fileName = null;
                lock (downloadLock)
                {
                    foreach (var img in downloadedImages)
                    {
                        if (!processedImages.Contains(img))
                        {
                            fileName = img;
                            processedImages.Add(img);
                            break;
                        }
                    }
                }

                if (fileName != null)
                {
                    try
                    {
                        string watermarkedFileName = fileName.Replace(".jpg", ".watermarked.jpg")
                                                             .Replace(".png", ".watermarked.png");
                        
                        using (Image image = Image.Load(fileName))
                        {
                            // Add watermark
                            var font = SystemFonts.CreateFont("Arial", 48);
                            image.Mutate(ctx => ctx.DrawText("WATERMARK", font, Color.White, new PointF(10, 10)));
                            image.Save(watermarkedFileName);
                        }
                        
                        Console.WriteLine($"[Processer] Watermarked: {watermarkedFileName}");
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine($"[Processer] Error processing {fileName}: {ex.Message}");
                    }
                }
                else
                {
                    Thread.Sleep(100);
                    // Check if downloader is done
                    lock (downloadLock)
                    {
                        if (downloadedImages.Count > 0 && processedImages.Count >= downloadedImages.Count)
                        {
                            Thread.Sleep(2000); // Wait a bit more
                            if (processedImages.Count >= downloadedImages.Count)
                                break; // Exit if all processed
                        }
                    }
                }
            }
        }
    }
}