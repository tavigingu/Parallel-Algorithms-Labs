# Laborator 7

## Exercitiul 1 - sample-par

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/07  ‹main*› 
╰─➤ ./sample-par 10 1 2

Something 0 from thread 0 we processed 1 tasks and submitted 1 tasks
Something 1 from thread 0 we processed 2 tasks and submitted 2 tasks
Something 2 from thread 1 we processed 3 tasks and submitted 3 tasks
Something 3 from thread 0 we processed 4 tasks and submitted 4 tasks
Something 4 from thread 1 we processed 5 tasks and submitted 5 tasks
Something 5 from thread 0 we processed 6 tasks and submitted 6 tasks
Something 6 from thread 0 we processed 7 tasks and submitted 7 tasks
Something 7 from thread 1 we processed 8 tasks and submitted 8 tasks
Something 8 from thread 1 we processed 9 tasks and submitted 9 tasks
Something 9 from thread 0 we processed 10 tasks and submitted 10 tasks
Something 10 from thread 0 we processed 11 tasks and submitted 11 tasks

## Exercitiul 2 - queens-par

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/07  ‹main*› 
╰─➤ ./queens-par 4 1 2

  1   3   0   2 
  2   0   3   1 

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/07  ‹main*› 
╰─➤ ./queens-par 8 1 4

  3   1   6   2   5   7   4   0 
  4   1   3   6   2   7   5   0 
  0   6   3   5   7   1   4   2 
  5   3   0   4   7   1   6   2 
  4   6   1   3   7   0   2   5 
  5   3   6   0   2   4   1   7 
  4   2   7   3   6   0   5   1 
  6   2   0   5   7   4   1   3 
  6   1   3   0   7   4   2   5 
  5   1   6   0   2   4   7   3 
  5   2   6   3   0   7   1   4 
  1   4   6   3   0   7   5   2 
  3   6   2   7   1   4   0   5 
  2   4   6   0   3   1   7   5 
  3   0   4   7   5   2   6   1 
  4   7   3   0   6   1   5   2 
  4   6   0   3   1   7   5   2 
  5   2   0   7   4   1   3   6 
  3   6   4   1   5   0   2   7 
  6   3   1   7   5   0   2   4 
  5   2   6   1   7   4   0   3 
  1   6   2   5   7   4   0   3 
  2   5   7   1   3   0   6   4 
  1   7   5   0   2   4   6   3 
  4   2   0   6   1   7   5   3 
  2   6   1   7   4   0   3   5 
  3   5   7   2   0   6   4   1 
  6   4   2   0   5   7   1   3 
  6   2   7   1   4   0   5   3 
  4   0   7   5   2   6   1   3 
  5   7   1   3   0   6   4   2 
  4   1   5   0   6   3   7   2 
  3   6   0   7   4   1   5   2 
  4   6   1   5   2   0   3   7 
  5   3   1   7   4   6   0   2 
  1   3   5   7   2   0   6   4 
  2   5   7   0   3   6   4   1 
  3   1   7   5   0   2   4   6 
  5   2   4   6   0   3   1   7 
  6   3   1   4   7   0   2   5 
  2   5   1   4   7   0   6   3 
  1   6   4   7   0   3   5   2 
  2   4   1   7   0   6   3   5 
  5   7   2   0   3   6   4   1 
  3   0   4   7   1   6   2   5 
  2   5   3   1   7   4   6   0 
  3   6   4   2   0   5   7   1 
  6   0   2   7   5   3   1   4 
  2   5   3   0   7   1   4   6 
  4   0   3   5   7   1   6   2 
  3   1   6   4   0   7   5   2 
  4   6   3   0   2   7   5   1 
  5   0   4   1   7   2   6   3 
  1   5   0   6   3   7   2   4 
  3   5   0   4   1   7   2   6 
  1   4   6   0   2   7   5   3 
  2   7   3   6   0   5   1   4 
  4   1   7   0   3   6   2   5 
  2   6   1   7   5   3   0   4 
  3   7   0   4   6   1   5   2 
  5   1   6   0   3   7   4   2 
  0   5   7   2   6   3   1   4 
  4   2   0   5   7   1   3   6 
  1   7   5   0   2   4   6   3 
  3   5   7   1   6   0   2   4 
  1   6   2   5   7   4   0   3 
  4   6   0   2   7   5   3   1 
  6   4   7   1   3   0   2   5 
  6   0   2   7   5   3   1   4 
  5   3   6   0   7   1   4   2 
  6   1   5   2   0   3   7   4 
  2   4   1   7   5   3   6   0 
  7   2   0   5   1   4   6   3 
  3   6   2   5   1   4   7   0 
  4   7   3   0   2   5   1   6 
  2   0   6   4   7   1   3   5 
  3   5   7   2   0   6   4   1 
  7   3   0   2   5   1   6   4 
  5   7   1   3   0   6   4   2 
  1   3   5   7   2   0   6   4 
  2   5   7   0   4   6   1   3 
  4   2   7   3   6   0   5   1 
  7   1   3   0   6   4   2   5 
  5   2   0   6   4   7   1   3 
  0   4   7   5   2   6   1   3 
  3   7   4   2   0   6   1   5 
  1   4   6   0   3   5   7   2 
  6   3   1   7   5   0   2   4 
  2   0   6   4   7   1   3   5 
  3   1   7   4   6   0   2   5 
  4   0   7   3   1   6   2   5 
  2   7   3   6   0   5   1   4 

## Exercitiul 3 - getPath-par

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/07  ‹main*› 
╰─➤ ./getPath-par 10 1 2

 0  1  2  3 
 0  4  3 
 0  5  8  3 
 0  1  6  8  3 
 0  5  7  2  3 
 0  1  6  9  4  3 
 0  5  7  9  4  3 
 0  4  9  6  8  3 
 0  4  9  7  2  3 
 0  1  2  7  5  8  3 
 0  5  8  6  1  2  3 
 0  5  7  9  6  8  3 
 0  4  9  6  1  2  3 
 0  5  8  6  9  4  3 
 0  4  9  7  5  8  3 
 0  1  6  9  7  2  3 
 0  1  2  7  9  4  3 
 0  5  7  2  1  6  8  3 
 0  5  7  9  6  1  2  3 
 0  1  2  7  9  6  8  3 
 0  5  8  6  9  7  2  3 
 0  1  6  8  5  7  2  3 
 0  4  9  6  8  5  7  2  3 
 0  1  6  9  7  5  8  3 
 0  5  7  2  1  6  9  4  3 
 0  4  9  7  2  1  6  8  3 
 0  1  6  8  5  7  9  4  3 
 0  4  9  7  5  8  6  1  2  3 
 0  5  8  6  1  2  7  9  4  3 
 0  4  9  6  1  2  7  5  8  3 
 0  1  2  7  5  8  6  9  4  3 

## Exercitiul 4 - colorGraph-par

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/07  ‹main*› 
╰─➤ ./colorGraph-par 10 1 2 | head -20

 0  2  0  1  2  1  0  2  2  1 
 0  2  0  1  2  1  1  2  2  0 
 0  2  0  1  2  1  1  2  0  0 
 0  2  0  1  2  2  1  1  0  0 
 0  2  0  2  1  2  1  1  0  0 
 0  2  0  2  1  2  1  1  0  2 
 0  2  1  0  1  1  0  0  2  2 
 0  2  0  2  1  2  0  1  1  2 
 0  2  0  2  1  1  1  2  0  0 
 0  2  1  0  1  2  0  0  1  2 
 0  2  1  0  1  1  1  2  2  0 
 0  2  1  0  1  1  1  0  2  2 
 0  2  1  0  2  2  0  0  1  1 
 0  2  1  0  2  1  0  0  2  1 
 0  2  1  2  1  2  0  0  1  2 
 0  2  1  0  2  1  1  2  2  0 
 0  2  1  2  1  2  1  0  0  2 
 0  2  1  2  1  1  1  2  0  0 
 0  2  1  2  1  1  1  0  0  2 
 1  0  1  0  2  0  1  2  2  0 

## Exercitiul 5 - Verificare corectitudine queens-par

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/07  ‹main*› 
╰─➤ bash testCorrectnessIntensive.sh queens-seq queens-par 4 10 "1 2 4"

The result of your parallel program is
======================================
  1   3   0   2 
  2   0   3   1 
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
Files out and out.1.4 differ
Files out and out.2.4 differ
Files out and out.4.4 differ
Files out and out.5.4 differ
Files out and out.6.4 differ
Files out and out.7.4 differ
Files out and out.8.4 differ
Files out and out.9.4 differ

Fisierele difera in ordinea solutiilor din cauza paralelizarii, dar toate solutiile sunt corecte.
Verificare numar de solutii:

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/07  ‹main*› 
╰─➤ wc -l out out.1.4 out.5.4

   2 out
   2 out.1.4
   2 out.5.4
   6 total

## Exercitiul 6 - Verificare corectitudine getPath-par

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/07  ‹main*› 
╰─➤ bash testCorrectnessIntensive.sh getPath-seq getPath-par 10 10 "1 2 4"

The result of your parallel program is
======================================
 0  1  2  3 
 0  1  2  7  5  8  3 
 0  1  2  7  5  8  6  9  4  3 
 0  1  2  7  9  4  3 
 0  1  2  7  9  6  8  3 
 0  1  6  8  3 
 0  1  6  8  5  7  2  3 
 0  1  6  8  5  7  9  4  3 
 0  1  6  9  4  3 
 0  1  6  9  7  2  3 
 0  1  6  9  7  5  8  3 
 0  4  3 
 0  4  9  6  1  2  3 
 0  4  9  6  1  2  7  5  8  3 
 0  4  9  6  8  3 
 0  4  9  6  8  5  7  2  3 
 0  4  9  7  2  1  6  8  3 
 0  4  9  7  2  3 
 0  4  9  7  5  8  3 
 0  4  9  7  5  8  6  1  2  3 
 0  5  7  2  1  6  8  3 
 0  5  7  2  1  6  9  4  3 
 0  5  7  2  3 
 0  5  7  9  4  3 
 0  5  7  9  6  1  2  3 
 0  5  7  9  6  8  3 
 0  5  8  3 
 0  5  8  6  1  2  3 
 0  5  8  6  1  2  7  9  4  3 
 0  5  8  6  9  4  3 
 0  5  8  6  9  7  2  3 
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
Files out and out.10.1 differ
Files out and out.10.2 differ
Files out and out.10.4 differ
Files out and out.1.1 differ
Files out and out.1.2 differ
Files out and out.1.4 differ
Files out and out.2.1 differ
Files out and out.2.2 differ
Files out and out.2.4 differ
Files out and out.3.1 differ
Files out and out.3.2 differ
Files out and out.3.4 differ
Files out and out.4.1 differ
Files out and out.4.2 differ
Files out and out.4.4 differ
Files out and out.5.1 differ
Files out and out.5.2 differ
Files out and out.5.4 differ
Files out and out.6.1 differ
Files out and out.6.2 differ
Files out and out.6.4 differ
Files out and out.7.1 differ
Files out and out.7.2 differ
Files out and out.7.4 differ
Files out and out.8.1 differ
Files out and out.8.2 differ
Files out and out.8.4 differ
Files out and out.9.1 differ
Files out and out.9.2 differ
Files out and out.9.4 differ

Fisierele difera in ordinea solutiilor din cauza paralelizarii, dar toate drumurile sunt gasite.
Verificare numar de drumuri:

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/07  ‹main*› 
╰─➤ wc -l out out.1.1 out.1.2 out.1.4

  31 out
  31 out.1.1
  31 out.1.2
  31 out.1.4
 124 total

## Exercitiul 7 - Verificare corectitudine colorGraph-par

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/07  ‹main*› 
╰─➤ bash testCorrectnessIntensive.sh colorGraph-seq colorGraph-par 10 10 "1 2 4"

The result of your parallel program is
======================================
 0  1  0  1  2  1  0  2  2  1 
 0  1  0  1  2  1  2  2  0  0 
 0  1  0  1  2  1  2  2  0  1 
 0  1  0  1  2  2  2  1  0  0 
 0  1  0  2  1  1  2  2  0  0 
 0  1  0  2  1  2  0  1  1  2 
 0  1  0  2  1  2  2  1  0  0 
 0  1  0  2  1  2  2  1  1  0 
 0  1  2  0  1  1  0  0  2  2 
 0  1  2  0  1  2  0  0  1  2 
 0  1  2  0  1  2  0  1  1  2 
 0  1  2  0  1  2  2  1  1  0 
 0  1  2  0  2  1  0  0  2  1 
 0  1  2  0  2  2  0  0  1  1 
 0  1  2  0  2  2  2  0  1  1 
 0  1  2  0  2  2  2  1  1  0 
 0  1  2  1  2  1  0  0  2  1 
 0  1  2  1  2  1  2  0  0  1 
 0  1  2  1  2  2  2  0  0  1 
 0  1  2  1  2  2  2  1  0  0 
 0  2  0  1  2  1  0  2  2  1 
 0  2  0  1  2  1  1  2  0  0 
 0  2  0  1  2  1  1  2  2  0 
 0  2  0  1  2  2  1  1  0  0 
 0  2  0  2  1  1  1  2  0  0 
 0  2  0  2  1  2  0  1  1  2 
 0  2  0  2  1  2  1  1  0  0 
 0  2  0  2  1  2  1  1  0  2 
 0  2  1  0  1  1  0  0  2  2 
 0  2  1  0  1  1  1  0  2  2 
 0  2  1  0  1  1  1  2  2  0 
 0  2  1  0  1  2  0  0  1  2 
 0  2  1  0  2  1  0  0  2  1 
 0  2  1  0  2  1  0  2  2  1 
 0  2  1  0  2  1  1  2  2  0 
 0  2  1  0  2  2  0  0  1  1 
 0  2  1  2  1  1  1  0  0  2 
 0  2  1  2  1  1  1  2  0  0 
 0  2  1  2  1  2  0  0  1  2 
 0  2  1  2  1  2  1  0  0  2 
 1  0  1  0  2  0  1  2  2  0 
 1  0  1  0  2  0  2  2  1  0 
 1  0  1  0  2  0  2  2  1  1 
 1  0  1  0  2  2  2  0  1  1 
 1  0  1  2  0  0  2  2  1  1 
 1  0  1  2  0  2  1  0  0  2 
 1  0  1  2  0  2  2  0  0  1 
 1  0  1  2  0  2  2  0  1  1 
 1  0  2  0  2  0  1  1  2  0 
 1  0  2  0  2  0  2  1  1  0 
 1  0  2  0  2  2  2  0  1  1 
 1  0  2  0  2  2  2  1  1  0 
 1  0  2  1  0  0  1  1  2  2 
 1  0  2  1  0  2  1  0  0  2 
 1  0  2  1  0  2  1  1  0  2 
 1  0  2  1  0  2  2  0  0  1 
 1  0  2  1  2  0  1  1  2  0 
 1  0  2  1  2  2  1  1  0  0 
 1  0  2  1  2  2  2  0  0  1 
 1  0  2  1  2  2  2  1  0  0 
 1  2  0  1  0  0  0  1  2  2 
 1  2  0  1  0  0  0  2  2  1 
 1  2  0  1  0  0  1  1  2  2 
 1  2  0  1  0  2  1  1  0  2 
 1  2  0  1  2  0  0  2  2  1 
 1  2  0  1  2  0  1  1  2  0 
 1  2  0  1  2  0  1  2  2  0 
 1  2  0  1  2  2  1  1  0  0 
 1  2  0  2  0  0  0  1  1  2 
 1  2  0  2  0  0  0  2  1  1 
 1  2  0  2  0  2  0  1  1  2 
 1  2  0  2  0  2  1  1  0  2 
 1  2  1  0  2  0  0  2  1  1 
 1  2  1  0  2  0  0  2  2  1 
 1  2  1  0  2  0  1  2  2  0 
 1  2  1  0  2  2  0  0  1  1 
 1  2  1  2  0  0  0  2  1  1 
 1  2  1  2  0  2  0  0  1  1 
 1  2  1  2  0  2  0  0  1  2 
 1  2  1  2  0  2  1  0  0  2 
 2  0  1  0  1  0  1  2  2  0 
 2  0  1  0  1  0  2  2  1  0 
 2  0  1  0  1  1  1  0  2  2 
 2  0  1  0  1  1  1  2  2  0 
 2  0  1  2  0  0  2  2  1  1 
 2  0  1  2  0  1  1  0  0  2 
 2  0  1  2  0  1  2  0  0  1 
 2  0  1  2  0  1  2  2  0  1 
 2  0  1  2  1  0  2  2  1  0 
 2  0  1  2  1  1  1  0  0  2 
 2  0  1  2  1  1  1  2  0  0 
 2  0  1  2  1  1  2  2  0  0 
 2  0  2  0  1  0  1  1  2  0 
 2  0  2  0  1  0  1  1  2  2 
 2  0  2  0  1  0  2  1  1  0 
 2  0  2  0  1  1  1  0  2  2 
 2  0  2  1  0  0  1  1  2  2 
 2  0  2  1  0  1  1  0  0  2 
 2  0  2  1  0  1  1  0  2  2 
 2  0  2  1  0  1  2  0  0  1 
 2  1  0  1  0  0  0  1  2  2 
 2  1  0  1  0  0  0  2  2  1 
 2  1  0  1  0  1  0  2  2  1 
 2  1  0  1  0  1  2  2  0  1 
 2  1  0  2  0  0  0  1  1  2 
 2  1  0  2  0  0  0  2  1  1 
 2  1  0  2  0  0  2  2  1  1 
 2  1  0  2  0  1  2  2  0  1 
 2  1  0  2  1  0  0  1  1  2 
 2  1  0  2  1  0  2  1  1  0 
 2  1  0  2  1  0  2  2  1  0 
 2  1  0  2  1  1  2  2  0  0 
 2  1  2  0  1  0  0  1  1  2 
 2  1  2  0  1  0  0  1  2  2 
 2  1  2  0  1  0  2  1  1  0 
 2  1  2  0  1  1  0  0  2  2 
 2  1  2  1  0  0  0  1  2  2 
 2  1  2  1  0  1  0  0  2  1 
 2  1  2  1  0  1  0  0  2  2 
 2  1  2  1  0  1  2  0  0  1 
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
Files out and out.10.2 differ
Files out and out.10.4 differ
Files out and out.1.2 differ
Files out and out.1.4 differ
Files out and out.2.2 differ
Files out and out.2.4 differ
Files out and out.3.2 differ
Files out and out.3.4 differ
Files out and out.4.2 differ
Files out and out.4.4 differ
Files out and out.5.2 differ
Files out and out.5.4 differ
Files out and out.6.4 differ
Files out and out.7.2 differ
Files out and out.7.4 differ
Files out and out.8.2 differ
Files out and out.8.4 differ
Files out and out.9.2 differ
Files out and out.9.4 differ

Fisierele difera in ordinea solutiilor din cauza paralelizarii, dar toate colorarile valide sunt gasite.
Verificare numar de solutii:

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/07  ‹main*› 
╰─➤ wc -l out out.1.1 out.1.2 out.1.4

  120 out
  120 out.1.1
  120 out.1.2
  120 out.1.4
  480 total


## Exercitiul 8 - checkSubset

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/07  ‹main*› 
╰─➤ ./checkSubset test1.txt test2.txt

All lines from test1.txt are present in test2.txt

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/07  ‹main*› 
╰─➤ ./checkSubset test2.txt test1.txt

Line 4 from test2.txt not found in test1.txt: line4
Some lines from test2.txt are NOT present in test1.txt

## Exercitiul 9 - testCorrectnessIntensiveSubset.sh

Script modificat care folosește checkSubset pentru verificarea corectitudinii.
In loc de diff care verifică ordinea exactă, checkSubset verifică doar dacă toate soluțiile sunt prezente.

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/07  ‹main*› 
╰─➤ bash testCorrectnessIntensiveSubset.sh queens-seq queens-par 4 10 "1 2 4"

The result of your parallel program is
======================================
  1   3   0   2 
  2   0   3   1 
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

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/07  ‹main*› 
╰─➤ bash testCorrectnessIntensiveSubset.sh getPath-seq getPath-par 10 10 "1 2 4"

The result of your parallel program is
======================================
 0  1  2  3 
 0  1  2  7  5  8  3 
 0  1  2  7  5  8  6  9  4  3 
 0  1  2  7  9  4  3 
 0  1  2  7  9  6  8  3 
 0  1  6  8  3 
 0  1  6  8  5  7  2  3 
 0  1  6  8  5  7  9  4  3 
 0  1  6  9  4  3 
 0  1  6  9  7  2  3 
 0  1  6  9  7  5  8  3 
 0  4  3 
 0  4  9  6  1  2  3 
 0  4  9  6  1  2  7  5  8  3 
 0  4  9  6  8  3 
 0  4  9  6  8  5  7  2  3 
 0  4  9  7  2  1  6  8  3 
 0  4  9  7  2  3 
 0  4  9  7  5  8  3 
 0  4  9  7  5  8  6  1  2  3 
 0  5  7  2  1  6  8  3 
 0  5  7  2  1  6  9  4  3 
 0  5  7  2  3 
 0  5  7  9  4  3 
 0  5  7  9  6  1  2  3 
 0  5  7  9  6  8  3 
 0  5  8  3 
 0  5  8  6  1  2  3 
 0  5  8  6  1  2  7  9  4  3 
 0  5  8  6  9  4  3 
 0  5  8  6  9  7  2  3 
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

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/07  ‹main*› 
╰─➤ bash testCorrectnessIntensiveSubset.sh colorGraph-seq colorGraph-par 10 10 "1 2 4"

The result of your parallel program is
======================================
 0  1  0  1  2  1  0  2  2  1 
 0  1  0  1  2  1  2  2  0  0 
 0  1  0  1  2  1  2  2  0  1 
 0  1  0  1  2  2  2  1  0  0 
 0  1  0  2  1  1  2  2  0  0 
 0  1  0  2  1  2  0  1  1  2 
 0  1  0  2  1  2  2  1  0  0 
 0  1  0  2  1  2  2  1  1  0 
 0  1  2  0  1  1  0  0  2  2 
 0  1  2  0  1  2  0  0  1  2 
 0  1  2  0  1  2  0  1  1  2 
 0  1  2  0  1  2  2  1  1  0 
 0  1  2  0  2  1  0  0  2  1 
 0  1  2  0  2  2  0  0  1  1 
 0  1  2  0  2  2  2  0  1  1 
 0  1  2  0  2  2  2  1  1  0 
 0  1  2  1  2  1  0  0  2  1 
 0  1  2  1  2  1  2  0  0  1 
 0  1  2  1  2  2  2  0  0  1 
 0  1  2  1  2  2  2  1  0  0 
 0  2  0  1  2  1  0  2  2  1 
 0  2  0  1  2  1  1  2  0  0 
 0  2  0  1  2  1  1  2  2  0 
 0  2  0  1  2  2  1  1  0  0 
 0  2  0  2  1  1  1  2  0  0 
 0  2  0  2  1  2  0  1  1  2 
 0  2  0  2  1  2  1  1  0  0 
 0  2  0  2  1  2  1  1  0  2 
 0  2  1  0  1  1  0  0  2  2 
 0  2  1  0  1  1  1  0  2  2 
 0  2  1  0  1  1  1  2  2  0 
 0  2  1  0  1  2  0  0  1  2 
 0  2  1  0  2  1  0  0  2  1 
 0  2  1  0  2  1  0  2  2  1 
 0  2  1  0  2  1  1  2  2  0 
 0  2  1  0  2  2  0  0  1  1 
 0  2  1  2  1  1  1  0  0  2 
 0  2  1  2  1  1  1  2  0  0 
 0  2  1  2  1  2  0  0  1  2 
 0  2  1  2  1  2  1  0  0  2 
 1  0  1  0  2  0  1  2  2  0 
 1  0  1  0  2  0  2  2  1  0 
 1  0  1  0  2  0  2  2  1  1 
 1  0  1  0  2  2  2  0  1  1 
 1  0  1  2  0  0  2  2  1  1 
 1  0  1  2  0  2  1  0  0  2 
 1  0  1  2  0  2  2  0  0  1 
 1  0  1  2  0  2  2  0  1  1 
 1  0  2  0  2  0  1  1  2  0 
 1  0  2  0  2  0  2  1  1  0 
 1  0  2  0  2  2  2  0  1  1 
 1  0  2  0  2  2  2  1  1  0 
 1  0  2  1  0  0  1  1  2  2 
 1  0  2  1  0  2  1  0  0  2 
 1  0  2  1  0  2  1  1  0  2 
 1  0  2  1  0  2  2  0  0  1 
 1  0  2  1  2  0  1  1  2  0 
 1  0  2  1  2  2  1  1  0  0 
 1  0  2  1  2  2  2  0  0  1 
 1  0  2  1  2  2  2  1  0  0 
 1  2  0  1  0  0  0  1  2  2 
 1  2  0  1  0  0  0  2  2  1 
 1  2  0  1  0  0  1  1  2  2 
 1  2  0  1  0  2  1  1  0  2 
 1  2  0  1  2  0  0  2  2  1 
 1  2  0  1  2  0  1  1  2  0 
 1  2  0  1  2  0  1  2  2  0 
 1  2  0  1  2  2  1  1  0  0 
 1  2  0  2  0  0  0  1  1  2 
 1  2  0  2  0  0  0  2  1  1 
 1  2  0  2  0  2  0  1  1  2 
 1  2  0  2  0  2  1  1  0  2 
 1  2  1  0  2  0  0  2  1  1 
 1  2  1  0  2  0  0  2  2  1 
 1  2  1  0  2  0  1  2  2  0 
 1  2  1  0  2  2  0  0  1  1 
 1  2  1  2  0  0  0  2  1  1 
 1  2  1  2  0  2  0  0  1  1 
 1  2  1  2  0  2  0  0  1  2 
 1  2  1  2  0  2  1  0  0  2 
 2  0  1  0  1  0  1  2  2  0 
 2  0  1  0  1  0  2  2  1  0 
 2  0  1  0  1  1  1  0  2  2 
 2  0  1  0  1  1  1  2  2  0 
 2  0  1  2  0  0  2  2  1  1 
 2  0  1  2  0  1  1  0  0  2 
 2  0  1  2  0  1  2  0  0  1 
 2  0  1  2  0  1  2  2  0  1 
 2  0  1  2  1  0  2  2  1  0 
 2  0  1  2  1  1  1  0  0  2 
 2  0  1  2  1  1  1  2  0  0 
 2  0  1  2  1  1  2  2  0  0 
 2  0  2  0  1  0  1  1  2  0 
 2  0  2  0  1  0  1  1  2  2 
 2  0  2  0  1  0  2  1  1  0 
 2  0  2  0  1  1  1  0  2  2 
 2  0  2  1  0  0  1  1  2  2 
 2  0  2  1  0  1  1  0  0  2 
 2  0  2  1  0  1  1  0  2  2 
 2  0  2  1  0  1  2  0  0  1 
 2  1  0  1  0  0  0  1  2  2 
 2  1  0  1  0  0  0  2  2  1 
 2  1  0  1  0  1  0  2  2  1 
 2  1  0  1  0  1  2  2  0  1 
 2  1  0  2  0  0  0  1  1  2 
 2  1  0  2  0  0  0  2  1  1 
 2  1  0  2  0  0  2  2  1  1 
 2  1  0  2  0  1  2  2  0  1 
 2  1  0  2  1  0  0  1  1  2 
 2  1  0  2  1  0  2  1  1  0 
 2  1  0  2  1  0  2  2  1  0 
 2  1  0  2  1  1  2  2  0  0 
 2  1  2  0  1  0  0  1  1  2 
 2  1  2  0  1  0  0  1  2  2 
 2  1  2  0  1  0  2  1  1  0 
 2  1  2  0  1  1  0  0  2  2 
 2  1  2  1  0  0  0  1  2  2 
 2  1  2  1  0  1  0  0  2  1 
 2  1  2  1  0  1  0  0  2  2 
 2  1  2  1  0  1  2  0  0  1 
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

## Exercitiul 10 - hanoi-seq

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/07  ‹main*› 
╰─➤ ./hanoi-seq 3 1

Move disk 1 from A to C
Move disk 2 from A to B
Move disk 1 from C to B
Move disk 3 from A to C
Move disk 1 from B to A
Move disk 2 from B to C
Move disk 1 from A to C
Total moves: 7
Expected moves: 7
CORRECT

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/07  ‹main*› 
╰─➤ ./hanoi-seq 5 1

Move disk 1 from A to C
Move disk 2 from A to B
Move disk 1 from C to B
Move disk 3 from A to C
Move disk 1 from B to A
Move disk 2 from B to C
Move disk 1 from A to C
Move disk 4 from A to B
Move disk 1 from C to B
Move disk 2 from C to A
Move disk 1 from B to A
Move disk 3 from C to B
Move disk 1 from A to C
Move disk 2 from A to B
Move disk 1 from C to B
Move disk 5 from A to C
Move disk 1 from B to A
Move disk 2 from B to C
Move disk 1 from A to C
Move disk 3 from B to A
Move disk 1 from C to B
Move disk 2 from C to A
Move disk 1 from B to A
Move disk 4 from B to C
Move disk 1 from A to C
Move disk 2 from A to B
Move disk 1 from C to B
Move disk 3 from A to C
Move disk 1 from B to A
Move disk 2 from B to C
Move disk 1 from A to C
Total moves: 31
Expected moves: 31
CORRECT

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/07  ‹main*› 
╰─➤ ./hanoi-seq 10 0

Total moves: 1023
Expected moves: 1023
CORRECT

## Exercitiul 11 - hanoi-par

Paralelizare a problemei Turnurilor din Hanoi folosind paradigma replicated workers.

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/07  ‹main*› 
╰─➤ ./hanoi-par 3 1 2

Move disk 3 from A to C
Move disk 2 from B to C
Move disk 2 from A to B
Move disk 1 from A to C
Move disk 1 from A to C
Move disk 1 from C to B
Move disk 1 from B to A
Total moves: 7
Expected moves: 7
CORRECT

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/07  ‹main*› 
╰─➤ ./hanoi-par 5 0 2

Total moves: 31
Expected moves: 31
CORRECT

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/07  ‹main*› 
╰─➤ ./hanoi-par 10 0 4

Total moves: 1023
Expected moves: 1023
CORRECT

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/07  ‹main*› 
╰─➤ ./hanoi-par 15 0 4

Total moves: 32767
Expected moves: 32767
CORRECT


