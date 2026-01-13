using System.Text.Json;

namespace ex08
{
    internal class Program
    {
        static async Task Main(string[] args)
        {
            Console.WriteLine("Querying stock APIs...");

            CancellationTokenSource cts = new CancellationTokenSource();

            // Create tasks for different APIs
            Task<string> alphaVantageTask = QueryAlphaVantage("IBM", cts.Token);
            Task<string> finnhubTask = QueryFinnhub("AAPL", cts.Token);

            try
            {
                // Wait for first successful response
                Task<string> completedTask = await Task.WhenAny(alphaVantageTask, finnhubTask);
                string result = await completedTask;

                Console.WriteLine($"\nFirst response received:");
                Console.WriteLine(result);

                // Cancel other tasks
                cts.Cancel();
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error: {ex.Message}");
            }

            await Task.Delay(1000); // Give time for cleanup
        }

        static async Task<string> QueryAlphaVantage(string symbol, CancellationToken ct)
        {
            // Free API key - demo purposes (replace with your own)
            string apiKey = "demo";
            string url = $"https://www.alphavantage.co/query?function=GLOBAL_QUOTE&symbol={symbol}&apikey={apiKey}";

            using (HttpClient client = new HttpClient())
            {
                Console.WriteLine($"[AlphaVantage] Querying {symbol}...");
                
                for (int i = 0; i < 5; i++)
                {
                    ct.ThrowIfCancellationRequested();
                    
                    try
                    {
                        string response = await client.GetStringAsync(url, ct);
                        
                        using (JsonDocument doc = JsonDocument.Parse(response))
                        {
                            if (doc.RootElement.TryGetProperty("Global Quote", out JsonElement quote))
                            {
                                if (quote.TryGetProperty("05. price", out JsonElement price))
                                {
                                    return $"[AlphaVantage] {symbol}: ${price.GetString()}";
                                }
                            }
                        }
                    }
                    catch (TaskCanceledException)
                    {
                        throw;
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine($"[AlphaVantage] Attempt {i + 1} failed: {ex.Message}");
                    }

                    await Task.Delay(1000, ct);
                }

                throw new Exception("AlphaVantage: Max retries reached");
            }
        }

        static async Task<string> QueryFinnhub(string symbol, CancellationToken ct)
        {
            // Free API key - demo purposes (sign up at finnhub.io for your own)
            string apiKey = "sandbox_c7qj6dqad3i8g3kbqsgg";
            string url = $"https://finnhub.io/api/v1/quote?symbol={symbol}&token={apiKey}";

            using (HttpClient client = new HttpClient())
            {
                Console.WriteLine($"[Finnhub] Querying {symbol}...");
                
                for (int i = 0; i < 5; i++)
                {
                    ct.ThrowIfCancellationRequested();
                    
                    try
                    {
                        string response = await client.GetStringAsync(url, ct);
                        
                        using (JsonDocument doc = JsonDocument.Parse(response))
                        {
                            if (doc.RootElement.TryGetProperty("c", out JsonElement currentPrice))
                            {
                                double price = currentPrice.GetDouble();
                                if (price > 0)
                                {
                                    return $"[Finnhub] {symbol}: ${price}";
                                }
                            }
                        }
                    }
                    catch (TaskCanceledException)
                    {
                        throw;
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine($"[Finnhub] Attempt {i + 1} failed: {ex.Message}");
                    }

                    await Task.Delay(1000, ct);
                }

                throw new Exception("Finnhub: Max retries reached");
            }
        }
    }
}