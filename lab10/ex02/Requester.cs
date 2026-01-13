using System.Text.Json;

namespace ex02
{
    public class Requester
    {
        private string _targetUrl;
        private HttpClient _httpClient;

        public Requester(string targetUrl)
        {
            _targetUrl = targetUrl;
            _httpClient = new HttpClient();
        }

        public async Task<ApiResponse> GetImageURL()
        {
            int waitTime = 1000; // Start with 1 second
            
            while (true)
            {
                try
                {
                    string apiResponseString = await _httpClient.GetStringAsync(_targetUrl);

                    JsonSerializerOptions serializerOptions = new JsonSerializerOptions();
                    serializerOptions.PropertyNameCaseInsensitive = true;

                    ApiResponse response = JsonSerializer.Deserialize<ApiResponse>(apiResponseString, serializerOptions);

                    if (response.Status == Constants.API_RESPONSE_SUCCESS)
                    {
                        return response;
                    }
                    else if (response.Status == "RETRY-LATER")
                    {
                        Console.WriteLine($"[Requester] Server busy, waiting {waitTime}ms");
                        await Task.Delay(waitTime);
                        waitTime = Math.Min(waitTime * 2, 32000); // Exponential backoff, max 32 seconds
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"[Requester] Error: {ex.Message}");
                    await Task.Delay(waitTime);
                    waitTime = Math.Min(waitTime * 2, 32000);
                }
            }
        }

        public async Task<List<string>> GetMultipleImageURLs(int count)
        {
            List<string> urls = new List<string>();
            
            for (int i = 0; i < count; i++)
            {
                ApiResponse response = await GetImageURL();
                urls.Add(response.Url);
                Console.WriteLine($"[Requester] Added URL: {response.Url}");
            }
            
            return urls;
        }
    }
}
