namespace ex04
{
    internal class Program
    {
        static async Task Main(string[] args)
        {
            var progress1 = new Progress<float>();
            progress1.ProgressChanged += (sender, percent) =>
            {
                Console.WriteLine($"TID {Thread.CurrentThread.ManagedThreadId}: Task1 ProgressChanged => {percent}%");
            };
            
            var progress2 = new Progress<float>();
            progress2.ProgressChanged += (sender, percent) =>
            {
                Console.WriteLine($"TID {Thread.CurrentThread.ManagedThreadId}: Task2 ProgressChanged => {percent}%");
            };

            Task<int> task_1 = DoSomeWorkAsync(progress1);
            Task<string> task_2 = DoSomeStringWorkAsync(progress2);
            Task task_3 = ThrowNotImplementedExceptionAsync();

            try
            {
                await Task.WhenAll(task_3, task_1, task_2);
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Something went wrong! => {ex.Message}");
            }
            
            // Print results even after exception
            if (task_1.IsCompletedSuccessfully)
            {
                Console.WriteLine($"Task1 result: {task_1.Result}");
            }
            
            if (task_2.IsCompletedSuccessfully)
            {
                Console.WriteLine($"Task2 result: {task_2.Result}");
            }
        }

        static async Task<int> DoSomeWorkAsync(IProgress<float> progress = null)
        {
            int result = 0;
            for (int i = 1; i <= 10; i++)
            {
                // Simulate processing item i
                await Task.Delay(i * 200);

                result += Random.Shared.Next(1, 10);

                // Report progress
                progress?.Report(i * 10.0f);
            }

            return result;
        }

        static async Task<string> DoSomeStringWorkAsync(IProgress<float> progress = null)
        {
            string result = string.Empty;

            for (int i = 1; i <= 10; i++)
            {
                // Simulate processing item i
                await Task.Delay(i * 100);

                result += i;

                // Report progress
                progress?.Report(i * 10.0f);
            }

            return result;
        }

        static async Task ThrowNotImplementedExceptionAsync()
        {
            throw new NotImplementedException();
        }
    }
}