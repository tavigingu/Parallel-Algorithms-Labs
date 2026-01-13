namespace ex03
{
    internal class Program
    {
        static int filesCount = 0;
        static int foldersCount = 0;
        static long totalFileSize = 0;
        static string lastWrittenFile = "";
        static DateTime lastWrittenTime = DateTime.MinValue;
        static object lockObj = new object();

        static async Task Main(string[] args)
        {
            string rootPath = args.Length > 0 ? args[0] : ".";

            if (!Directory.Exists(rootPath))
            {
                Console.WriteLine($"Directory '{rootPath}' does not exist.");
                return;
            }

            await AnalyzeDirectory(rootPath);

            Console.WriteLine($"Files count: {filesCount}");
            Console.WriteLine($"Folders count: {foldersCount}");
            Console.WriteLine($"Total file size: {totalFileSize} bytes");
            Console.WriteLine($"Last written file: {lastWrittenFile}");
            Console.WriteLine($"Last written file time: {lastWrittenTime}");
        }

        static async Task AnalyzeDirectory(string dirPath)
        {
            List<Task> tasks = new List<Task>();

            // Process files in this directory
            try
            {
                string[] files = Directory.GetFiles(dirPath);
                foreach (string file in files)
                {
                    Task fileTask = Task.Factory.StartNew(() => ProcessFile(file));
                    tasks.Add(fileTask);
                }

                // Process subdirectories
                string[] subdirs = Directory.GetDirectories(dirPath);
                foreach (string subdir in subdirs)
                {
                    lock (lockObj)
                    {
                        foldersCount++;
                    }

                    Task dirTask = Task.Factory.StartNew(
                        async () => await AnalyzeDirectory(subdir),
                        CancellationToken.None,
                        TaskCreationOptions.AttachedToParent,
                        TaskScheduler.Default
                    ).Unwrap();

                    tasks.Add(dirTask);
                }

                await Task.WhenAll(tasks);
            }
            catch (UnauthorizedAccessException)
            {
                // Skip directories we don't have access to
            }
        }

        static void ProcessFile(string filePath)
        {
            try
            {
                FileInfo fileInfo = new FileInfo(filePath);

                lock (lockObj)
                {
                    filesCount++;
                    totalFileSize += fileInfo.Length;

                    if (fileInfo.LastWriteTime > lastWrittenTime)
                    {
                        lastWrittenTime = fileInfo.LastWriteTime;
                        lastWrittenFile = fileInfo.Name;
                    }
                }
            }
            catch (Exception)
            {
                // Skip files we can't access
            }
        }
    }
}