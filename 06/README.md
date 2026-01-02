# Laborator 6

## Exercitiul 1 - oneProducerOneConsumerOneBuffer

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs  ‹main*› 
╰─➤ ./oneProducerOneConsumerOneBuffer 10 1

Passed all

## Exercitiul 2 - oneProducerOneConsumerFiveBuffer

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs  ‹main*› 
╰─➤ ./oneProducerOneConsumerFiveBuffer 10 1

Passed all

## Exercitiul 3 - multipleProducersMultipleConsumers

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs  ‹main*› 
╰─➤ ./multipleProducersMultipleConsumers 100 1 4

Passed all

## Exercitiul 4 - philosophers

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs  ‹main*› 
╰─➤./philosophers 10 1 4

All phylosophers have eaten

## Exercitiul 5 - readersWriters

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs  ‹main*› 
╰─➤./readersWriters 100 1 4

Passed all

## Exercitiul 6 - Verificare corectitudine

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs  ‹main*› 
╰─➤./testCorrectnessIntensive.sh oneProducerOneConsumer-fakeForScriptSeq oneProducerOneConsumerOneBuffer 10 10 "1 2 4"

The result of your parallel program is
======================================
I finished Correctly
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

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs  ‹main*› 
╰─➤./testCorrectnessIntensive.sh oneProducerOneConsumer-fakeForScriptSeq oneProducerOneConsumerFiveBuffer 10 10 "1 2 4"

The result of your parallel program is
======================================
I finished Correctly
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

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs  ‹main*› 
╰─➤./testCorrectnessIntensive.sh multipleProducersMultipleConsumers-fakeForScriptSeq multipleProducersMultipleConsumers 10 10 "2 4"

The result of your parallel program is
======================================
CORRECT
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
Files out and out.1.2 differ
Files out and out.2.2 differ
Files out and out.3.2 differ
Files out and out.4.2 differ
Files out and out.5.2 differ
Files out and out.6.2 differ
Files out and out.7.2 differ
Files out and out.8.2 differ
Files out and out.9.2 differ

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs  ‹main*› 
╰─➤./testCorrectnessIntensive.sh philosophers-fakeForScriptSeq philosophers 10 10 "2 4"

The result of your parallel program is
======================================
All phylosophers have eaten
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

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs  ‹main*› 
╰─➤./testCorrectnessIntensive.sh readersWriters-fakeForScriptSeq readersWriters 10 10 "2 4"

The result of your parallel program is
======================================
Passed all
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
Files out and out.6.2 differ
Files out and out.6.4 differ
Files out and out.7.2 differ
Files out and out.7.4 differ
Files out and out.8.2 differ
Files out and out.8.4 differ
Files out and out.9.2 differ
Files out and out.9.4 differ

## Exercitiul 7 - Rezolvarea deadlock-ului la philosophers

Solutia implementata pentru evitarea deadlock-ului:
Ultimul filozof ia furculitele in ordine inversa comparativ cu ceilalti. 
In loc sa ia mai intai furculita stanga si apoi pe cea dreapta, el ia mai intai furculita dreapta 
si apoi pe cea stanga. Aceasta sparge ciclul de asteptare circulara, deoarece cel putin un filozof 
va putea lua ambele furculite si va manca, eliberand apoi resursele pentru altii.

Implementare:
- Filozofii 0 la P-2: mutex_lock(left), mutex_lock(right)
- Filozoful P-1: mutex_lock(right), mutex_lock(left)

## Exercitiul 8 - Verificare corectitudine dupa rezolvarea deadlock-ului

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs  ‹main*› 
╰─➤./testCorrectnessIntensive.sh philosophers-fakeForScriptSeq philosophers 10 10 "2 4"

The result of your parallel program is
======================================
All phylosophers have eaten
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

## Exercitiul 9 - smokers

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs  ‹main*› 
╰─➤./smokers 30 1 3

Smoker with tobacco smoked: 11 times
Smoker with paper smoked: 12 times
Smoker with matches smoked: 7 times
Total: 30 times
CORRECT

Verificare corectitudine:
╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs  ‹main*› 
╰─➤./testCorrectnessIntensive.sh smokers-fakeForScriptSeq smokers 30 10

The result of your parallel program is
======================================
CORRECT
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

## Exercitiul 10 - barber

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs  ‹main*› 
╰─➤./barber 5 1 10

Customers served: 10
Customers rejected: 0
Total customers: 10
CORRECT

Verificare corectitudine:
./testCorrectnessIntensive.sh barber-fakeForScriptSeq barber 5 10 1

The result of your parallel program is
======================================
CORRECT
======================================
Running intensive correctness test with threads
Test 1/10
Test 2/10
Test 3/10
Test 4/10
Test 5/10
Test 6/102024: Participant. 2025
Test 7/10
Test 8/10
Test 9/10
Test 10/10
Output correct on intensive test
