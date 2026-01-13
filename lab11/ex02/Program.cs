namespace ex02
{
    internal class Program
    {
        static async Task Main(string[] args)
        {
            ProductClient client = new ProductClient("http://localhost:5000/api/products");

            await foreach (var product in client.GetProductsAsync(limit: 5))
            {
                Console.WriteLine($"Processing product [{product.Id}]: Name=[{product.Name}], Category=[{product.Category}], Description=[{product.Description}], Price=[{product.Price}]");
            }

            Console.WriteLine("All products processed.");
        }
    }
}