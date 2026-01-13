using System.Security.Cryptography;
using System.Text;

namespace ex04
{
    internal class Program
    {
        static void Main(string[] args)
        {
            if (args.Length < 2)
            {
                Console.WriteLine("Usage: ex04 <encrypted_file> <num_threads>");
                return;
            }

            string encryptedFile = args[0];
            int numThreads = int.Parse(args[1]);
            string keysFile = encryptedFile.Replace("_encrypted.bin", "_encrypted_keys.txt");
            string outputFile = encryptedFile.Replace("_encrypted.bin", "_decrypted.txt");

            var stopwatch = System.Diagnostics.Stopwatch.StartNew();

            // Read encrypted data
            byte[] encryptedBytes = File.ReadAllBytes(encryptedFile);

            // Read keys metadata
            string[] lines = File.ReadAllLines(keysFile);
            int numKeys = int.Parse(lines[0]);

            byte[][] decryptedSegments = new byte[numKeys][];
            Thread[] threads = new Thread[numKeys];

            for (int i = 0; i < numKeys; i++)
            {
                int threadId = i;
                string[] parts = lines[i + 1].Split(' ');
                int start = int.Parse(parts[0]);
                int end = int.Parse(parts[1]);
                string keyFile = parts[2];
                string ivFile = parts[3];

                threads[i] = new Thread(() =>
                {
                    byte[] key = File.ReadAllBytes(keyFile);
                    byte[] iv = File.ReadAllBytes(ivFile);

                    // Calculate encrypted segment boundaries
                    // We need to figure out where this segment is in the encrypted file
                    // For simplicity, we'll decrypt the whole encrypted file in segments
                    int encChunkSize = encryptedBytes.Length / numKeys;
                    int encStart = threadId * encChunkSize;
                    int encEnd = (threadId == numKeys - 1) ? encryptedBytes.Length : (threadId + 1) * encChunkSize;
                    int encLength = encEnd - encStart;

                    byte[] encSegment = new byte[encLength];
                    Array.Copy(encryptedBytes, encStart, encSegment, 0, encLength);

                    decryptedSegments[threadId] = DecryptSegment(encSegment, key, iv);
                });
                threads[i].Start();
            }

            for (int i = 0; i < numKeys; i++)
            {
                threads[i].Join();
            }

            // Concatenate decrypted segments
            using (FileStream fs = new FileStream(outputFile, FileMode.Create))
            {
                for (int i = 0; i < numKeys; i++)
                {
                    fs.Write(decryptedSegments[i], 0, decryptedSegments[i].Length);
                }
            }

            stopwatch.Stop();
            Console.WriteLine($"Decryption completed in {stopwatch.ElapsedMilliseconds}ms");
        }

        static byte[] DecryptSegment(byte[] input, byte[] key, byte[] iv)
        {
            using Aes aes = Aes.Create();
            aes.Key = key;
            aes.IV = iv;
            using MemoryStream inputStream = new(input);
            using CryptoStream cryptoStream = new(inputStream, aes.CreateDecryptor(), CryptoStreamMode.Read);
            using MemoryStream output = new();
            cryptoStream.CopyTo(output);
            return output.ToArray();
        }
    }
}