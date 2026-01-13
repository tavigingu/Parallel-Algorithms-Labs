# Lab 11 - IAsyncEnumerable and Parallel Operations

## ex01 - IAsyncEnumerable with yield return

Demonstrates IAsyncEnumerable with yield return, intercalating DoOtherWork as a parallel Task.

```
DoOtherWork(0)...
Processing value 0
DoOtherWork(1)...
Processing value 1
DoOtherWork(2)...
Processing value 2
DoOtherWork(3)...
Processing value 3
DoOtherWork(4)...
DoOtherWork(5)...
Processing value 4
DoOtherWork(6)...
Processing value 5
DoOtherWork(7)...
Processing value 6
DoOtherWork(8)...
Processing value 7
DoOtherWork(9)...
DoOtherWork(10)...
Processing value 8
Processing value 9
```

## ex02 - Pagination with IAsyncEnumerable

ProductClient with IAsyncEnumerable for paginated REST API calls.

Note: Requires backend server running on http://localhost:5000 with /api/products endpoint.

```csharp
ProductClient client = new ProductClient("http://localhost:5000/api/products");
await foreach (var product in client.GetProductsAsync(limit: 5))
{
    Console.WriteLine($"Processing product [{product.Id}]: {product.Name}");
}
```

## ex03 - Search with CancellationToken

Search for K products with price P, stop when found using CancellationToken.

```csharp
int K = 3;
decimal targetPrice = 100.0m;
CancellationTokenSource cts = new CancellationTokenSource();

await foreach (var product in client.GetProductsAsync(limit: 5, cancellationToken: cts.Token))
{
    if (product.Price == targetPrice)
    {
        foundCount++;
        if (foundCount >= K)
        {
            cts.Cancel();
            break;
        }
    }
}
```

## ex04 - Parallel.ForEach

Analysis exercise - checks even numbers using Parallel.ForEach.

```
0 is even
2 is even
4 is even
6 is even
8 is even
```

## ex05 - Primality with Parallel.ForEach

Checks primality of 1,000,000 numbers using Parallel.ForEach, writes results to file.

```
Checking 1000000 numbers for primality using Parallel.ForEach...

Total primes found: 78498
Primes written to primes.txt

First 10 primes: 2, 3, 5, 7, 11, 13, 17, 19, 23, 29
Last 10 primes: 999863, 999883, 999907, 999917, 999931, 999953, 999959, 999961, 999979, 999983
```

## ex06 - External cancellation

External interruption with CancellationToken (cancels after 2 seconds).

```
Checking 1000000 numbers for primality (will cancel after 2 seconds)...

Prime found: 999883
Prime found: 999931
Prime found: 999979
Prime found: 999953
Prime found: 999983
...

Processing completed without cancellation.
Total primes found before cancellation: 78498
```

Note: With 2 second timeout, processing may complete before cancellation on fast systems.

## ex07 - Internal break with ParallelLoopState

Internal interruption using ParallelLoopState.Stop() after finding 1000 primes.

```
Checking 1000000 numbers for primality (will stop after finding 1000 primes)...

Prime found: 2 (count: 1)
Prime found: 3 (count: 2)
...
Prime found: 7919 (count: 999)
Reached 1000 primes. Stopping...
Prime found: 7927 (count: 1000)
...
Prime found: 917659 (count: 1012)
Reached 1000 primes. Stopping...

Total primes found: 1012
```

Note: Due to parallel execution, count may exceed 1000 before all threads stop.

## ex08 - Parallel.ForEach aggregation

Analysis exercise - demonstrates aggregation pattern with localInit, body, localFinally.

```
120
```

Computes product of numbers 1-5 using thread-local aggregation.

## ex09 - Primality with aggregation

Counts primes using Parallel.ForEach aggregation pattern.

```
Counting primes in 1000000 numbers using Parallel.ForEach with aggregation...

Total primes found: 78498
```

## ex10 - Parallel.Invoke

Analysis exercise - processes array in two sections using Parallel.Invoke.

```
[5, 10] => 5
[0, 5] => 0
[0, 5] => 1
[5, 10] => 6
[5, 10] => 7
[0, 5] => 2
[0, 5] => 3
[5, 10] => 8
[0, 5] => 4
[5, 10] => 9
```

Shows parallel execution of two sections processing different array ranges.

## ex11 - Primality with Parallel.Invoke

Counts primes using Parallel.Invoke with 4 parameterized sections.

```
Counting primes in 100 numbers using Parallel.Invoke with 4 sections...

Section 1 (range 0-25): 9 primes found
Section 4 (range 75-100): 4 primes found
Section 2 (range 25-50): 6 primes found
Section 3 (range 50-75): 6 primes found

Results:
  Section 1: 9 primes
  Section 2: 6 primes
  Section 3: 6 primes
  Section 4: 4 primes
  Total: 25 primes
```

## Key Concepts

- **IAsyncEnumerable**: Async streaming of data with `yield return`
- **CancellationToken**: Cooperative cancellation with `[EnumeratorCancellation]` attribute
- **Parallel.ForEach**: Data parallelism for collections
- **ParallelOptions**: External cancellation via CancellationToken
- **ParallelLoopState**: Internal break with `state.Stop()`
- **Aggregation**: Thread-local state with localInit, body, localFinally
- **Parallel.Invoke**: Task parallelism for independent operations
