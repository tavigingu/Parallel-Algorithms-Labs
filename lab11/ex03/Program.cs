namespace ex03
{
    internal class Program
    {
        static async Task Main(string[] args)
        {
            int K = 3; // Number of products to find
            decimal targetPrice = 100.0m; // Price to search for

            ProductClient client = new ProductClient("http://localhost:5000/api/products");
            CancellationTokenSource cts = new CancellationTokenSource();

            int foundCount = 0;
            List<Product> foundProducts = new List<Product>();

            try
            {
                await foreach (var product in client.GetProductsAsync(limit: 5, cancellationToken: cts.Token))
                {
                    Console.WriteLine($"Checking product [{product.Id}]: Name=[{product.Name}], Price=[{product.Price}]");

                    if (product.Price == targetPrice)
                    {
                        foundProducts.Add(product);
                        foundCount++;
                        Console.WriteLine($"*** Found matching product! ({foundCount}/{K}) ***");

                        if (foundCount >= K)
                        {
                            Console.WriteLine($"\nFound {K} products with price {targetPrice}. Stopping search.");
                            cts.Cancel();
                            break;
                        }
                    }
                }
            }
            catch (OperationCanceledException)
            {
                // Expected when cancellation is requested
            }

            Console.WriteLine($"\nSearch complete. Found {foundProducts.Count} product(s):");
            foreach (var product in foundProducts)
            {
                Console.WriteLine($"  [{product.Id}] {product.Name} - ${product.Price}");
            }
        }
    }
}