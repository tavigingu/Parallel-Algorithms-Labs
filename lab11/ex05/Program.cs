namespace ex05
{
    internal class Program
    {
        static readonly int ARRAY_SIZE = 1000000;

        static void Main(string[] args)
        {
            int[] v = new int[ARRAY_SIZE];

            init(v);

            int primeCount = 0;
            List<int> primes = new List<int>();
            object lockObj = new object();

            Console.WriteLine($"Checking {ARRAY_SIZE} numbers for primality using Parallel.ForEach...\n");

            Parallel.ForEach(v, number =>
            {
                if (IsPrime(number))
                {
                    lock (lockObj)
                    {
                        primes.Add(number);
                    }

                    Interlocked.Add(ref primeCount, 1);
                }
            });

            Console.WriteLine($"Total primes found: {primeCount}");
            
            primes.Sort();
            write(primes.ToArray(), "primes.txt");
            Console.WriteLine("Primes written to primes.txt");
            
            Console.WriteLine($"\nFirst 10 primes: {string.Join(", ", primes.Take(10))}");
            Console.WriteLine($"Last 10 primes: {string.Join(", ", primes.TakeLast(10))}");
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