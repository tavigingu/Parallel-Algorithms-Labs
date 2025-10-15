# Laborator 3

## ex 1
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab03/lab03$ ./raceCondition 1000 1 2
4000 answer should be 4000
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab03/lab03$ ./raceCondition 10000 1 2
40000 answer should be 40000
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab03/lab03$ ./raceCondition 100000 1 2
210908 answer should be 400000
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab03/lab03$ ./raceCondition 1000000 1 2
2128136 answer should be 4000000

- cu N mic rezultatul in general este corect
- cu N mare threadurile au mai mult timp sa interfereze 

tavi@Tavi:/mnt/d/Algoritmi paraleli/lab03/lab03$ ./raceCondition 1 1 2
4 answer should be 4
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab03/lab03$ ./raceCondition 1 1 2
4 answer should be 4
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab03/lab03$ ./raceCondition 1 1 2
4 answer should be 4
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab03/lab03$ ./raceCondition 1 1 2
4 answer should be 4
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab03/lab03$ ./raceCondition 1 1 2
4 answer should be 4
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab03/lab03$ ./raceCondition 1 1 2
4 answer should be 4
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab03/lab03$ ./raceCondition 1 1 2
4 answer should be 4
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab03/lab03$ ./raceCondition 1 1 2
4 answer should be 4
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab03/lab03$ ./raceCondition 1 1 2
4 answer should be 4
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab03/lab03$ ./raceCondition 1 1 2
4 answer should be 4
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab03/lab03$ ./raceCondition 1 1 2
2 answer should be 4

- fiind doar o operatie pe thread sansele sunt foarte mici ca acestea sa se suprapuna
- ocazional threadurile se executa exact simultan

## ex 2

tavi@Tavi:/mnt/d/Algoritmi paraleli/lab03/lab03$ ./testCorrectnessIntensive.sh raceCondition-seq raceCondition 1 1000
...
Test 983/1000
Test 984/1000
Test 985/1000
Test 986/1000
Test 987/1000
Test 988/1000
Test 989/1000
Test 990/1000
Test 991/1000
Test 992/1000
Test 993/1000
Test 994/1000
Test 995/1000
Test 996/1000
Test 997/1000
Test 998/1000
Test 999/1000
Test 1000/1000
Files out and out.273.4 differ
Files out and out.539.8 differ
Files out and out.783.8 differ

- scriptul a detectat 3 erori din 1000 
- desi programul pare corect la o rulare superficiala nu este sigur pentru ca race condition exista si poate cauza rezultate incorecte

## ex 3

- am adaugat mutex in programul raceCondition.c si am numit noua sursa ex3.c
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab03/lab03$ ./testCorrectnessIntensive.sh raceCondition-seq ex3  1 1000
...
Test 991/1000
Test 992/1000
Test 993/1000
Test 994/1000
Test 995/1000
Test 996/1000
Test 997/1000
Test 998/1000
Test 999/1000
Test 1000/1000
Output correct on intensive test

- output corect nu au mai fost rezultate incorecte din cauza race condition

## ex 4

tavi@Tavi:/mnt/d/Algoritmi paraleli/lab03/lab03$ ./testCorrectnessIntensive.sh barrier-seq barrier 1 1000
...
Test 995/1000
Test 996/1000
Test 997/1000
Test 998/1000
Test 999/1000
Test 1000/1000
Output correct on intensive test

## ex 5

tavi@Tavi:/mnt/d/Algoritmi paraleli/lab03/lab03$ ./testCorrectnessIntensive.sh semaphoreSignal-seq semaphoreSignal 1 1000
...
Test 992/1000
Test 993/1000
Test 994/1000
Test 995/1000
Test 996/1000
Test 997/1000
Test 998/1000
Test 999/1000
Test 1000/1000
Output correct on intensive test

## ex 6 

- avem dead lock pentru ca threadurile dau lock mutexului fara unlock ulterior
  
## ex 7

- thread 0 tine mutex A si vrea mutex B
- thread 1 tine mutex B si vrea mutex A

- fara sleep cele 2 threaduri executa foarte rapid iar celalalt nu apuca sa blocheze
- foarte rar la un numar mare de rulari poate aparea deadlock deoarece threadurile se pot executa simultan

## ex 8 

- threadul asteapta ca mutex-ul să fie liber dar acelasi thread ține mutex-ul adica SELF-DEADLOCK → se blocheaza pe sine insusi

ATENTIE!
În pthread standard, mutex-urile sunt NON-RECURSIVE:
Un thread NU poate face lock de 2 ori pe același mutex
Alte limbaje/framework-uri (Java, C#) au mutex-uri recursive care permit asta

- am folosit thread recursiv  care permite aceluiasi thread sa faca lock de mai multe ori
- contorizeaza de cate ori a facut lock si tot de atatea ori trebuie sa faca unlock

## ex 9 

tavi@Tavi:/mnt/d/Algoritmi paraleli/lab03/lab03$ time ./sumVectorValues 100000000 0 8

real    0m1.214s
user    0m1.380s
sys     0m0.667s
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab03/lab03$ time ./sumVectorValues-seq 100000000 0 1

real    0m1.115s
user    0m0.444s
sys     0m0.608s
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab03/lab03$ time ./sumVectorValues 100000000 0 16

real    0m1.284s
user    0m3.130s
sys     0m0.536s
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab03/lab03$ time ./sumVectorValues 100000000 0 4

real    0m1.079s
user    0m0.859s
sys     0m0.483s
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab03/lab03$ time ./sumVectorValues 100000000 0 2

real    0m1.121s
user    0m0.684s
sys     0m0.477s

Motive pentru care nu am obtinut scalabilitate
- mutexul produce blocaje
- operatiile sum+=v[i] este foarte simpla asa ca paralelizarea nu aduce beneficii foarte mari (beneficii sesizabile pentru operatii CPU intensive)
- se produce bottleneck la citirea din memorie deoarece toate threadurile citesc din RAM simultan

## ex 10 sumVectorValueScale.c
in loc sa folosim un mutex pentru suma globala am calculat suma locala in fiecare tren si facem o singura adunare la final

## ex 11 prepStrassen.c

tavi@Tavi:/mnt/d/Algoritmi paraleli/lab03/lab03$ ./testCorrectnessIntensive.sh prepStrassen-seq prepStrassen 1 1000
The result of your parallel program is
======================================
1120504338 1564709315 -1408269402 -541699384 
======================================
Running intensive correctness test with threads
Test 1/1000
Test 2/1000
Test 3/1000
Test 4/1000
...
Test 995/1000
Test 996/1000
Test 997/1000
Test 998/1000
Test 999/1000
Test 1000/1000
Output correct on intensive test

tavi@Tavi:/mnt/d/Algoritmi paraleli/lab03/lab03$ time ./prepStrassen 1000 1 10
1120504338 1564709315 -1408269402 -541699384 

real    0m0.005s
user    0m0.002s
sys     0m0.002s
tavi@Tavi:/mnt/d/Algoritmi paraleli/lab03/lab03$ time ./prepStrassen-seq 1000 1 10
1120504338 1564709315 -1408269402 -541699384 

real    0m0.006s
user    0m0.001s
sys     0m0.001s
