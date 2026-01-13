using System.Diagnostics;

namespace ex02
{
    internal class Program
    {
        static void Main(string[] args)
        {
            int numThreads = 1;

            string booksString = File.ReadAllText("booksLarge.txt");
            //string substring = "I need no medicine";//"This eBook is for the use of anyone anywhere";
            string substring = @"“This is Edgar’s legal nephew,” I reflected—“mine in a manner; I must
shake hands, and—yes—I must kiss him. It is right to establish a good
understanding at the beginning.”

I approached, and, attempting to take his chubby fist, said—“How do you
do, my dear?”

He replied in a jargon I did not comprehend.

“Shall you and I be friends, Hareton?” was my next essay at
conversation.

An oath, and a threat to set Throttler on me if I did not “frame off”
rewarded my perseverance.

“Hey, Throttler, lad!” whispered the little wretch, rousing a half-bred
bull-dog from its lair in a corner. “Now, wilt thou be ganging?” he
asked authoritatively.

Love for my life urged a compliance; I stepped over the threshold to
wait till the others should enter. Mr. Heathcliff was nowhere visible;
and Joseph, whom I followed to the stables, and requested to accompany
me in, after staring and muttering to himself, screwed up his nose and
replied—“Mim! mim! mim! Did iver Christian body hear aught like it?
Mincing un’ munching! How can I tell whet ye say?”";

            CancellationTokenSource cts = new CancellationTokenSource();
            Thread[] threads = new Thread[numThreads];

            Stopwatch stopwatch = new Stopwatch();
            stopwatch.Start();

            /////////////////////////////////////////////////////////////////////////////
            // Implement your solution here
            int chunkSize = booksString.Length / numThreads;
            
            for (int i = 0; i < numThreads; i++)
            {
                int threadId = i;
                int start = i * chunkSize;
                int end = (i == numThreads - 1) ? booksString.Length : (i + 1) * chunkSize + substring.Length - 1;
                
                threads[i] = new Thread(() => SearchSubstring(booksString, substring, start, end, threadId, cts, stopwatch));
                threads[i].Start();
            }

            for (int i = 0; i < numThreads; i++)
            {
                threads[i].Join();
            }

            /////////////////////////////////////////////////////////////////////////////
            
            if (!cts.Token.IsCancellationRequested)
            {
                stopwatch.Stop();
                Console.WriteLine("Elapsed time: {0}ms", stopwatch.ElapsedMilliseconds);
            }
        }

        static void SearchSubstring(string text, string substring, int start, int end, int threadId, CancellationTokenSource cts, Stopwatch stopwatch)
        {
            try
            {
                for (int i = start; i < end - substring.Length + 1; i++)
                {
                    if (cts.Token.IsCancellationRequested)
                    {
                        return;
                    }

                    if (text.Substring(i, substring.Length) == substring)
                    {
                        stopwatch.Stop();
                        Console.WriteLine($"Thread {threadId}: Found at [{i}].");
                        Console.WriteLine($"Elapsed time: {stopwatch.ElapsedMilliseconds}ms");
                        cts.Cancel(); // Cancel all other threads
                        return;
                    }
                }
            }
            catch (OperationCanceledException)
            {
                // Thread was cancelled
            }
        }
    }
}