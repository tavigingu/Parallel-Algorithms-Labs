namespace ex05
{
    internal class Program
    {
        static async Task Main(string[] args)
        {
            CancellationTokenSource cts = new CancellationTokenSource();
            
            string arg_1 = "1";
            Task<string> task_1 = DoSomeWorkAsync(arg_1, cts.Token);
            string arg_2 = "2";
            Task<string> task_2 = DoSomeWorkAsync(arg_2, cts.Token);
            Task<string> task_3 = DoSomeWorkAsync("3", cts.Token);

            Task<string> result = await Task.WhenAny(task_1, task_2, task_3);

            Console.WriteLine($"Final result: {await result}");
            
            // Cancel remaining tasks to prevent resource waste
            cts.Cancel();

            await Task.Delay(4000);
            
            Console.WriteLine("Program finished.");
        }

        static async Task<string> DoSomeWorkAsync(string id, CancellationToken cancellationToken = default)
        {
            Random random = new Random();
            string result = $"[{id}] => ";

            for (int i = 1; i <= 10; i++)
            {
                cancellationToken.ThrowIfCancellationRequested();
                
                await Task.Delay(random.Next(1, 10) * 100, cancellationToken);
                Console.WriteLine($"[{id}] working {i}...");
                result += i;
            }

            return result;
        }
    }
}