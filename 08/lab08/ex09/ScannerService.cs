namespace ex09
{
    public class ScannerService
    {
        private Mutex _mutex = new Mutex(false, "AV_0xAAEC");
        private string _logFilename;

        public ScannerService(string logfilename)
        {
            _logFilename = logfilename;
        }

        public void Scan()
        {
            bool mutexAcquired = false;
            try
            {
                mutexAcquired = _mutex.WaitOne(1000);
                if (!mutexAcquired)
                {
                    Console.WriteLine($"[{Environment.ProcessId}] A scanning session is already running");
                    return;
                }

                Console.WriteLine($"[{Environment.ProcessId}] Scanning your device for malware...");
                List<string> results = new List<string>();

                for (int ri = 0; ri < 50; ri++)
                {
                    results.Add($"{DateTime.Now} - PID=[{Environment.ProcessId}] - File['{ri}'] is {(Random.Shared.Next() % 3) switch { 0 => "CLEAN", 1 => "MALWARE", 2 => "VIRUS" }}\n");
                    Console.WriteLine($"[{Environment.ProcessId}] Scanned File['{ri}']");
                    Thread.Sleep(100);

                    // Append log to the file
                    File.AppendAllText(_logFilename, results[ri]);
                    Console.WriteLine($"[{Environment.ProcessId}] Written results for File['{ri}']");
                    Thread.Sleep(100);
                }
                Console.WriteLine($"[{Environment.ProcessId}] Finished!");
            }
            catch (AbandonedMutexException ex)
            {
                // Mutex was abandoned by another process but we now own it
                Console.WriteLine($"[{Environment.ProcessId}] Mutex was abandoned: {ex.Message}");
                Console.WriteLine($"[{Environment.ProcessId}] Acquired abandoned mutex, continuing scan...");
                mutexAcquired = true;
            }
            catch (Exception ex)
            {
                // Treat other exceptions
                Console.WriteLine($"[{Environment.ProcessId}] Exception occurred: {ex.Message}");
            }
            finally
            {
                if (mutexAcquired)
                {
                    Console.WriteLine($"[{Environment.ProcessId}] Releasing the mutex...");
                    _mutex.ReleaseMutex();
                }
            }
        }
    }
}
