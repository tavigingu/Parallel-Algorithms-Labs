## ex 2
# sanity check
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab04$ ./multiplyMatrices-out 5 2 10
1       2       3       4       5
0       1       2       3       4
0       0       1       2       3
0       0       0       1       2
0       0       0       0       1

# stress test
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab04$ ./testCorrectnessIntensive.sh multiplyMatrices-seq multiplyMatrices-out 100 10 4
rm: cannot remove 'out*': No such file or directory
The result of your parallel program is
======================================
1       2       3       4       5       6       7       8       9       10      11      12      13      14      15      16      17      18      19      20      21       22      23      24      25      26      27      28      29      30      31      32      33      34      35      36      37      38      39      40      41       42      43      44      45      46      47      48      49      50      51      52      53      54      55      56      57      58      59      60      61       62      63      64      65      66      67      68      69      70      71      72      73      74      75      76      77      78      7
...
0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       00       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       00       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       00       0       0       0       0       0       0       0       0       0       0       0       0       0       0       1
======================================
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

# scalability test
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab04$ time ./multiplyMatrices-out 2000 0 1

real    0m21.177s
user    0m21.763s
sys     0m0.027s
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab04$ time ./multiplyMatrices-out 2000 0 2

real    0m13.208s
user    0m24.889s
sys     0m0.038s
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab04$ time ./multiplyMatrices-out 2000 0 4

real    0m7.991s
user    0m35.105s
sys     0m0.023s

## ex 4
# sanity check
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab04$ ./multiplyMatrices-mid 5 2 10
1       2       3       4       5
0       1       2       3       4
0       0       1       2       3
0       0       0       1       2
0       0       0       0       1

# stress test
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab04$ ./testCorrectnessIntensive.sh multiplyMatrices-seq multiplyMatrices-mid 100 10 4
rm: cannot remove 'out*': No such file or directory
The result of your parallel program is
======================================
1       2       3       4       5       6       7       8       9       10      11      12      13      14      15      16      17      18      19      20      21       22      23      24      25      26      27      28      29      30      31      32      33      34      35      36      37      38      39      40      4
...
0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       00       0       0       0       0       0       0       0       0       0       0       0       0       0       0       1
======================================
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

# scalability test
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab04$ time ./multiplyMatrices-mid 2000 0 4

real    0m8.551s
user    0m30.844s
sys     0m0.031s
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab04$ time ./multiplyMatrices-mid 2000 0 2

real    0m12.660s
user    0m23.841s
sys     0m0.027s
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab04$ time ./multiplyMatrices-mid 2000 0 1

real    0m20.930s
user    0m21.222s
sys     0m0.024s

## ex 6 
# sanity test
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab04$ ./multiplyMatrices-in 5 1 1
1       2       3       4       5
0       1       2       3       4
0       0       1       2       3
0       0       0       1       2
0       0       0       0       1

# stress test
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab04$ ./testCorrectnessIntensive.sh multiplyMatrices-in multiplyMatrices-mid 100 10 4
0       0       0       0       0       0       0       0       0       0       0       0       0    00       1
======================================
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

# scalability test
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab04$ time ./multiplyMatrices-in 2000 0 1

real    0m21.800s
user    0m20.831s
sys     0m0.054s
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab04$ time ./multiplyMatrices-in 2000 0 2

real    0m3.982s
user    0m11.145s
sys     0m0.054s
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab04$ time ./multiplyMatrices-in 2000 0 4

real    0m2.730s
user    0m10.040s
sys     0m0.098s

## ex 7
Am creat cate un fir de executie pentru fiecare dintre calculele intermediare M1–M7, dar in comparatie cu laboratorul trecut calcularea M1-M7 presupune adunari si scaderi de matrici in loc de scalari. Cu o bariera am sincronizat firele inainte de combinarea rezultatelor finale în matricea C

## ex 8 
# sanity check 
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab04$ ./strassen 4 1 2
1       2       3       4
0       1       2       3
0       0       1       2
0       0       0       1

# stress check
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab04$ ./testCorrectnessIntensive.sh strassen-seq strassen 16 10 4
0       0       0       0       0       0       0       0       0       0       0       0       0       0       1       2
0       0       0       0       0       0       0       0       0       0       0       0       0       0       0       1
======================================
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

# scalability check
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab04$ time ./strassen-seq 1024 0 0

real    0m6.339s
user    0m5.866s
sys     0m0.157s
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab04$ time ./strassen 1024 0 0

real    0m1.815s
user    0m10.900s
sys     0m0.046s
