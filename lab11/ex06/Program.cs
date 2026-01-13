namespace ex06
{
    internal class Program
    {
        static readonly int ARRAY_SIZE = 1000000;

        static void Main(string[] args)
        {
            int[] v = new int[ARRAY_SIZE];

            init(v);

            int primeCount = 0;
            CancellationTokenSource cts = new CancellationTokenSource();

            // Cancel after 2 seconds
            cts.CancelAfter(2000);

            Console.WriteLine($"Checking {ARRAY_SIZE} numbers for primality (will cancel after 2 seconds)...\n");

            try
            {
                Parallel.ForEach(v, new ParallelOptions { CancellationToken = cts.Token }, number =>
                {
                    if (IsPrime(number))
                    {
                        Interlocked.Add(ref primeCount, 1);
                        Console.WriteLine($"Prime found: {number}");
                    }
                });

                Console.WriteLine("\\nProcessing completed without cancellation.");
            }
            catch (OperationCanceledException)
            {
                Console.WriteLine("\\nProcessing was cancelled!");
            }

            Console.WriteLine($"Total primes found before cancellation: {primeCount}");
        }

        static void init(int[] v)
        {
            for (int i = 0; i < v.Length; i++)
            {
                v[i] = i;
            }
        }

        static void print(int[] v)
        {
            for (int i = 0; i < v.Length; i++)
            {
                Console.Write(v[i]);
                Console.Write(' ');
            }
            Console.WriteLine();
        }

        static void write(int[] v, string filename)
        {
            File.WriteAllText(filename, string.Join(" ", v));
        }

        static bool IsPrime(int number)
        {
            if (number < 2) return false;
            if (number == 2) return true;
            if (number % 2 == 0) return false;

            int sqrt = (int)Math.Sqrt(number);
            for (int i = 3; i <= sqrt; i += 2)
            {
                if (number % i == 0)
                    return false;
            }

            return true;
        }
    }
}