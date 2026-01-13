namespace ex07
{
    internal class Program
    {
        private static int NUM_OF_ITERATIONS = 50;

        static async Task Main(string[] args)
        {
            Console.WriteLine("Starting tasks...");

            try
            {
                CancellationTokenSource cts1 = new CancellationTokenSource();
                CancellationTokenSource cts2 = new CancellationTokenSource();

                var progress_1 = new Progress<float>();
                progress_1.ProgressChanged += (sender, percent) =>
                {
                    Console.WriteLine($"DoWork_1_Async: {percent}%");
                };
                Task<int> task1 = DoWork_1_Async(cts1.Token, progress_1);

                var progress_2 = new Progress<float>();
                progress_2.ProgressChanged += (sender, percent) =>
                {
                    Console.WriteLine($"DoWork_2_Async: {percent}%");
                };
                Task<int> task2 = DoWork_2_Async(cts2.Token, progress_2);

                // Wait for first task to complete
                Task<int> completedTask = await Task.WhenAny(task1, task2);
                
                // Cancel the other task
                if (completedTask == task1)
                {
                    cts2.Cancel();
                    Console.WriteLine($"Task 1 finished first with result: {await task1}");
                }
                else
                {
                    cts1.Cancel();
                    Console.WriteLine($"Task 2 finished first with result: {await task2}");
                }
                
                await Task.Delay(1000); // Give time for cancellation
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Exception: {ex.Message}");
            }

        }

        static async Task<int> DoWork_1_Async(CancellationToken cancellationToken, IProgress<float> progress = null)
        {
            int result = 0;
            Random random = new Random();

            for (int i = 1; i <= NUM_OF_ITERATIONS; i++)
            {
                cancellationToken.ThrowIfCancellationRequested();
                
                progress?.Report((i * 100.0f) / NUM_OF_ITERATIONS);
                await Task.Delay(random.Next(1, 20) * 100, cancellationToken);
                result += i;
            }

            return result;
        }

        static async Task<int> DoWork_2_Async(CancellationToken cancellationToken, IProgress<float> progress = null)
        {
            int result = 0;
            Random random = new Random();

            for (int i = 1; i <= NUM_OF_ITERATIONS; i++)
            {
                cancellationToken.ThrowIfCancellationRequested();
                
                progress?.Report((i * 100.0f) / NUM_OF_ITERATIONS);
                await Task.Delay(random.Next(1, 20) * 100, cancellationToken);
                result += i;
            }

            return result;
        }
    }
}