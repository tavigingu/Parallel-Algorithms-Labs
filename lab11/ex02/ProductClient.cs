using System.Text.Json;

namespace ex02
{
    internal class ProductClient
    {
        private readonly HttpClient _httpClient;
        private readonly string _baseUrl;

        public ProductClient(string baseUrl)
        {
            _baseUrl = baseUrl;
            _httpClient = new HttpClient();
        }

        public async IAsyncEnumerable<Product> GetProductsAsync(int limit = 10)
        {
            int offset = 0;
            bool hasMore = true;

            while (hasMore)
            {
                string url = $"{_baseUrl}?offset={offset}&limit={limit}";
                
                try
                {
                    string response = await _httpClient.GetStringAsync(url);
                    
                    JsonSerializerOptions options = new JsonSerializerOptions
                    {
                        PropertyNameCaseInsensitive = true
                    };
                    
                    Product[]? products = JsonSerializer.Deserialize<Product[]>(response, options);
                    
                    if (products == null || products.Length == 0)
                    {
                        hasMore = false;
                        yield break;
                    }
                    
                    foreach (var product in products)
                    {
                        yield return product;
                    }
                    
                    offset += limit;
                    
                    if (products.Length < limit)
                    {
                        hasMore = false;
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"Error fetching products: {ex.Message}");
                    hasMore = false;
                }
            }
        }
    }
}
