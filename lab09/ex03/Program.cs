using System.Security.Cryptography;
using System.Text;

namespace ex03
{
    internal class Program
    {
        static void Main(string[] args)
        {
            if (args.Length < 2)
            {
                Console.WriteLine("Usage: ex03 <input_file> <num_threads>");
                return;
            }

            string inputFile = args[0];
            int numThreads = int.Parse(args[1]);
            string outputEncryptedFile = inputFile + "_encrypted.bin";
            string outputKeysFile = inputFile + "_encrypted_keys.txt";

            byte[] inputBytes = File.ReadAllBytes(inputFile);
            string password = "thisisasimplepassword";

            var stopwatch = System.Diagnostics.Stopwatch.StartNew();

            // Encrypt in parallel
            byte[][] encryptedSegments = new byte[numThreads][];
            Thread[] threads = new Thread[numThreads];
            byte[][] keys = new byte[numThreads][];
            byte[][] ivs = new byte[numThreads][];
            
            int chunkSize = inputBytes.Length / numThreads;

            for (int i = 0; i < numThreads; i++)
            {
                int threadId = i;
                int start = i * chunkSize;
                int end = (i == numThreads - 1) ? inputBytes.Length : (i + 1) * chunkSize;

                threads[i] = new Thread(() =>
                {
                    int length = end - start;
                    byte[] segment = new byte[length];
                    Array.Copy(inputBytes, start, segment, 0, length);

                    // Generate unique IV for this segment
                    byte[] iv = new byte[16];
                    using (var rng = System.Security.Cryptography.RandomNumberGenerator.Create())
                    {
                        rng.GetBytes(iv);
                    }

                    encryptedSegments[threadId] = EncryptSegment(segment, password, iv);
                    keys[threadId] = Rfc2898DeriveBytes.Pbkdf2(Encoding.Unicode.GetBytes(password), Array.Empty<byte>(), 1234, HashAlgorithmName.SHA256, 16);
                    ivs[threadId] = iv;
                });
                threads[i].Start();
            }

            for (int i = 0; i < numThreads; i++)
            {
                threads[i].Join();
            }

            // Concatenate encrypted segments
            using (FileStream fs = new FileStream(outputEncryptedFile, FileMode.Create))
            {
                for (int i = 0; i < numThreads; i++)
                {
                    fs.Write(encryptedSegments[i], 0, encryptedSegments[i].Length);
                }
            }

            // Save keys and metadata
            using (StreamWriter sw = new StreamWriter(outputKeysFile))
            {
                sw.WriteLine(numThreads);
                int currentPos = 0;
                for (int i = 0; i < numThreads; i++)
                {
                    int start = i * chunkSize;
                    int end = (i == numThreads - 1) ? inputBytes.Length : (i + 1) * chunkSize;
                    
                    string keyFile = $"{inputFile}_key_{i}.bin";
                    string ivFile = $"{inputFile}_iv_{i}.bin";
                    
                    File.WriteAllBytes(keyFile, keys[i]);
                    File.WriteAllBytes(ivFile, ivs[i]);
                    
                    sw.WriteLine($"{start} {end} {keyFile} {ivFile}");
                }
            }

            stopwatch.Stop();
            Console.WriteLine($"Encryption completed in {stopwatch.ElapsedMilliseconds}ms");
        }

        static byte[] EncryptSegment(byte[] input, string password, byte[] iv)
        {
            using Aes aes = Aes.Create();
            aes.Key = Rfc2898DeriveBytes.Pbkdf2(Encoding.Unicode.GetBytes(password), Array.Empty<byte>(), 1234, HashAlgorithmName.SHA256, 16);
            aes.IV = iv;
            using MemoryStream output = new();
            using CryptoStream cryptoStream = new(output, aes.CreateEncryptor(), CryptoStreamMode.Write);
            cryptoStream.Write(input);
            cryptoStream.FlushFinalBlock();
            return output.ToArray();
        }

        static byte[] DecryptSegment(byte[] input, string password, byte[] iv)
        {
            using Aes aes = Aes.Create();
            aes.Key = Rfc2898DeriveBytes.Pbkdf2(Encoding.Unicode.GetBytes(password), Array.Empty<byte>(), 1234, HashAlgorithmName.SHA256, 16);
            aes.IV = iv;
            using MemoryStream inputStream = new(input);
            using CryptoStream cryptoStream = new(inputStream, aes.CreateDecryptor(), CryptoStreamMode.Read);
            using MemoryStream output = new();
            cryptoStream.CopyTo(output);
            return output.ToArray();
        }
    }
}