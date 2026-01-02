# Laborator 5

## Exercitiul 1
tavi@Tavi:~/Parallel-Algorithms-Labs/05$ ./bubbleSort-seq 100 1
Sorted correctly

## Exercitiul 2
tavi@Tavi:~/Parallel-Algorithms-Labs/05$ ./mergeSort-seq 16 2
  0  1  2  2  4  4  5  6  6  7  7  8  9 12 13 15
  0  1  2  2  4  4  5  6  6  7  7  8  9 12 13 15
Sorted correctly

## Exercitiul 3
tavi@Tavi:~/Parallel-Algorithms-Labs/05$ ./mergeSort-par 16 2 2
  0  1  2  2  4  4  5  6  6  7  7  8  9 12 13 15
  0  1  2  2  4  4  5  6  6  7  7  8  9 12 13 15
Sorted correctly
tavi@Tavi:~/Parallel-Algorithms-Labs/05$ bash testCorrectnessIntensive.sh mergeSort-seq mergeSort-par 100 10 4
Running intensive correctness test with threads
Test 1/10
Test 2/10
Test 3/10
Test 4/10
Test 5/10
Test 6/10
Test 7/10
Test 8/10
Test 9/10
Test 10/10
Output correct on intensive test
tavi@Tavi:~/Parallel-Algorithms-Labs/05$ time ./mergeSort-par 8192 0 1

real    0m0.003s
user    0m0.000s
sys     0m0.000s
tavi@Tavi:~/Parallel-Algorithms-Labs/05$ time ./mergeSort-par 8192 0 2

real    0m0.003s
user    0m0.000s
sys     0m0.000s
tavi@Tavi:~/Parallel-Algorithms-Labs/05$ time ./mergeSort-par 8192 0 4

real    0m0.003s
user    0m0.000s
sys     0m0.000s

## Exercitul 4
tavi@Tavi:~/Parallel-Algorithms-Labs/05$ ./oets-par 16 2 2
  0  1  2  2  4  4  5  6  6  7  7  8  9 12 13 15
  0  1  2  2  4  4  5  6  6  7  7  8  9 12 13 15
Sorted correctly
tavi@Tavi:~/Parallel-Algorithms-Labs/05$ bash testCorrectnessIntensive.sh bubbleSort-seq oets-par 100 10 4
Running intensive correctness test with threads
Test 1/10
Test 2/10
Test 3/10
Test 4/10
Test 5/10
Test 6/10
Test 7/10
Test 8/10
Test 9/10
Test 10/10
Output correct on intensive test
tavi@Tavi:~/Parallel-Algorithms-Labs/05$ time ./oets-par 2000 0 1

real    0m0.011s
user    0m0.010s
sys     0m0.000s
tavi@Tavi:~/Parallel-Algorithms-Labs/05$ time ./oets-par 2000 0 2

real    0m0.012s
user    0m0.010s
sys     0m0.000s
tavi@Tavi:~/Parallel-Algorithms-Labs/05$ time ./oets-par 2000 0 4

real    0m0.018s
user    0m0.030s
sys     0m0.010s

## Exercitiul 5
tavi@Tavi:~/Parallel-Algorithms-Labs/05$ ./sheerSort-seq 16 2
  0  1  2  2  4  4  5  6  6  7  7  8  9 12 13 15
  0  1  2  2  4  4  5  6  6  7  7  8  9 12 13 15
Sorted correctly

## Exercitiul 6
tavi@Tavi:~/Parallel-Algorithms-Labs/05$ ./sheerSort-par 16 2 2
  0  1  2  2  4  4  5  6  6  7  7  8  9 12 13 15
  0  1  2  2  4  4  5  6  6  7  7  8  9 12 13 15
Sorted correctly
tavi@Tavi:~/Parallel-Algorithms-Labs/05$ bash testCorrectnessIntensive.sh sheerSort-seq sheerSort-par 100 10 4
Running intensive correctness test with threads
Test 1/10
Test 2/10
Test 3/10
Test 4/10
Test 5/10
Test 6/10
Test 7/10
Test 8/10
Test 9/10
Test 10/10
Output correct on intensive test
tavi@Tavi:~/Parallel-Algorithms-Labs/05$ time ./sheerSort-par 10000 0 1

real    0m0.009s
user    0m0.010s
sys     0m0.000s
tavi@Tavi:~/Parallel-Algorithms-Labs/05$ time ./sheerSort-par 10000 0 2

real    0m0.006s
user    0m0.010s
sys     0m0.000s
tavi@Tavi:~/Parallel-Algorithms-Labs/05$ time ./sheerSort-par 10000 0 4

real    0m0.004s
user    0m0.010s
sys     0m0.000s
