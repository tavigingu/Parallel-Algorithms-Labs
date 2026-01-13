namespace ex09
{
    internal class Program
    {
        static readonly int ARRAY_SIZE = 1000000;

        static void Main(string[] args)
        {
            int[] v = new int[ARRAY_SIZE];

            init(v);

            Console.WriteLine($"Counting primes in {ARRAY_SIZE} numbers using Parallel.ForEach with aggregation...\n");

            int totalPrimes = 0;

            Parallel.ForEach(
                v,
                () => 0, // localInit: each thread starts with count = 0
                (number, state, localCount) => // body: increment local count if prime
                {
                    if (IsPrime(number))
                    {
                        return localCount + 1;
                    }
                    return localCount;
                },
                localCount => // localFinally: merge all thread-local counts
                {
                    Interlocked.Add(ref totalPrimes, localCount);
                }
            );

            Console.WriteLine($"Total primes found: {totalPrimes}");
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