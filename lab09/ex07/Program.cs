using System.Diagnostics;
using System.Net;

namespace ex07
{
    internal class Program
    {
        static List<string> responses = new List<string>();
        static object responseLock = new object();
        static int successCount = 0;
        static int failCount = 0;
        static List<long> responseTimes = new List<long>();

        static void Main(string[] args)
        {
            // Parse arguments
            int parallelRequests = 1;
            bool saveResponse = false;
            bool statCountSuccess = false;
            bool statCountFail = false;
            bool statMeanTime = false;
            string url = "http://localhost:5007/product";
            string method = "GET";

            foreach (var arg in args)
            {
                if (arg.StartsWith("-P="))
                {
                    parallelRequests = int.Parse(arg.Substring(3));
                }
                else if (arg == "--save-response")
                {
                    saveResponse = true;
                }
                else if (arg == "--stat-countsuccess")
                {
                    statCountSuccess = true;
                }
                else if (arg == "--stat-countfail")
                {
                    statCountFail = true;
                }
                else if (arg == "--stat-meantime")
                {
                    statMeanTime = true;
                }
                else if (arg.StartsWith("--url="))
                {
                    url = arg.Substring(6);
                }
                else if (arg.StartsWith("--method="))
                {
                    method = arg.Substring(9);
                }
            }

            Console.WriteLine($"Testing {url} with {parallelRequests} parallel requests...");

            Thread[] threads = new Thread[parallelRequests];
            Stopwatch globalStopwatch = Stopwatch.StartNew();

            for (int i = 0; i < parallelRequests; i++)
            {
                int threadId = i;
                threads[i] = new Thread(() => MakeRequest(url, method, threadId, saveResponse));
                threads[i].Start();
            }

            for (int i = 0; i < parallelRequests; i++)
            {
                threads[i].Join();
            }

            globalStopwatch.Stop();

            // Print statistics
            Console.WriteLine("\n=== Statistics ===");
            if (statCountSuccess)
            {
                Console.WriteLine($"Successful requests: {successCount}");
            }
            if (statCountFail)
            {
                Console.WriteLine($"Failed requests: {failCount}");
            }
            if (statMeanTime)
            {
                double meanTime = responseTimes.Count > 0 ? responseTimes.Average() : 0;
                Console.WriteLine($"Mean response time: {meanTime:F2}ms");
            }
            Console.WriteLine($"Total time: {globalStopwatch.ElapsedMilliseconds}ms");
            Console.WriteLine($"Error rate: {(failCount * 100.0 / parallelRequests):F2}%");
        }

        static void MakeRequest(string url, string method, int threadId, bool saveResponse)
        {
            Stopwatch stopwatch = Stopwatch.StartNew();
            try
            {
                using (WebClient client = new WebClient())
                {
                    string response;
                    if (method == "GET")
                    {
                        response = client.DownloadString(url);
                    }
                    else if (method == "POST")
                    {
                        client.Headers[HttpRequestHeader.ContentType] = "application/json";
                        response = client.UploadString(url, "POST", "{}");
                    }
                    else
                    {
                        throw new Exception($"Unsupported method: {method}");
                    }

                    stopwatch.Stop();

                    lock (responseLock)
                    {
                        successCount++;
                        responseTimes.Add(stopwatch.ElapsedMilliseconds);
                        
                        if (saveResponse)
                        {
                            responses.Add(response);
                            File.WriteAllText($"response_{threadId}.json", response);
                        }
                    }

                    Console.WriteLine($"[Thread {threadId}] Success - {stopwatch.ElapsedMilliseconds}ms");
                }
            }
            catch (Exception ex)
            {
                stopwatch.Stop();
                lock (responseLock)
                {
                    failCount++;
                    responseTimes.Add(stopwatch.ElapsedMilliseconds);
                }
                Console.WriteLine($"[Thread {threadId}] Failed - {ex.Message}");
            }
        }
    }
}