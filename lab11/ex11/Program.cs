namespace ex11
{
    internal class Program
    {
        static readonly int ARRAY_SIZE = 100;

        static void Main(string[] args)
        {
            int[] v = new int[ARRAY_SIZE];

            init(v);

            int section1Primes = 0;
            int section2Primes = 0;
            int section3Primes = 0;
            int section4Primes = 0;

            int sectionSize = ARRAY_SIZE / 4;

            Console.WriteLine($"Counting primes in {ARRAY_SIZE} numbers using Parallel.Invoke with 4 sections...\n");

            Parallel.Invoke(
                () => section1Primes = CountPrimesInRange(v, 0, sectionSize, "Section 1"),
                () => section2Primes = CountPrimesInRange(v, sectionSize, sectionSize * 2, "Section 2"),
                () => section3Primes = CountPrimesInRange(v, sectionSize * 2, sectionSize * 3, "Section 3"),
                () => section4Primes = CountPrimesInRange(v, sectionSize * 3, ARRAY_SIZE, "Section 4")
            );

            int totalPrimes = section1Primes + section2Primes + section3Primes + section4Primes;

            Console.WriteLine($"\nResults:");
            Console.WriteLine($"  Section 1: {section1Primes} primes");
            Console.WriteLine($"  Section 2: {section2Primes} primes");
            Console.WriteLine($"  Section 3: {section3Primes} primes");
            Console.WriteLine($"  Section 4: {section4Primes} primes");
            Console.WriteLine($"  Total: {totalPrimes} primes");
        }

        static int CountPrimesInRange(int[] v, int start, int end, string sectionName)
        {
            int count = 0;
            for (int i = start; i < end; i++)
            {
                if (IsPrime(v[i]))
                {
                    count++;
                }
            }
            Console.WriteLine($"{sectionName} (range {start}-{end}): {count} primes found");
            return count;
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