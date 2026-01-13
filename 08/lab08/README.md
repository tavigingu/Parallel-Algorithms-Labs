# Laborator 8 

## Exercitiul 1 


╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/08/lab08/ex01 
╰─➤ dotnet run

Thread with ID 4 is now executing with priority Normal
Thread with ID 4 is executing iteration 0
Thread with ID 5 is now executing with priority Normal
Thread with ID 5 is executing iteration 0
Thread with ID 6 is now executing with priority Normal
Thread with ID 6 is executing iteration 0
Thread with ID 4 is executing iteration 1
Thread with ID 4 is executing iteration 2
Thread with ID 5 is executing iteration 1
Thread with ID 6 is executing iteration 1
Thread with ID 4 is executing iteration 3
Thread with ID 5 is executing iteration 2
Thread with ID 6 is executing iteration 2
Thread with ID 4 is executing iteration 4
Thread with ID 5 is executing iteration 3
Thread with ID 6 is executing iteration 3
Thread with ID 5 is executing iteration 4
Thread with ID 6 is executing iteration 4

**Explicatie:** Thread-urile sunt executate concurent, fiecare avand un ID unic si prioritate normala. Ordinea de executie nu este determinista.

---

## Exercitiul 2 


╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/08/lab08/ex02 
╰─➤ dotnet run

Shared Variable: 0

**Explicatie:** Rezultatul final ar trebui sa fie 0 (2000 incrementari si 2000 decrementari), dar fara sincronizare, operatiile se suprapun si produc rezultate inconsistente. Acest lucru demonstreaza necesitatea sincronizarii.

---

## Exercitiul 3 

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/08/lab08/ex03 
╰─➤ dotnet run

Worker thread is executing iteration 0
Worker thread is executing iteration 1
Worker thread is executing iteration 2
Worker thread is executing iteration 3
Worker thread is executing iteration 4
Worker thread was interrupted!
Worker thread is doing some cleanup...
Worker thread terminated!

**Explicatie:** Thread-ul worker este intrerupt dupa 500ms folosind `Interrupt()`. Thread-ul prinde exceptia, face cleanup si se termina gracefully.

---

## Exercitiul 4 

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/08/lab08/ex04 
╰─➤ dotnet run 1000 4

Thread 0: [0, 250] => 53
Thread 1: [250, 500] => 48
Thread 2: [500, 750] => 46
Thread 3: [750, 1000] => 54
Elapsed Time: 9ms

**Explicatie:** Intervalul [0, 1000] este impartit intre 4 thread-uri, fiecare procesand un subset. Thread-ul 0 gaseste 53 de numere prime in intervalul [0, 250], etc.

---

## Exercitiul 5 


╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/08/lab08/ex05 
╰─➤ dotnet run 1000 4

Thread 0: [0, 250] => 53
Thread 3: [750, 1000] => 54
Elapsed Time: 8ms

**Explicatie:** Thread-urile sunt marcate ca background threads. Daca thread-ul principal se termina inaintea lor, aplicatia se inchide fara sa astepte finalizarea acestora.

---

## Exercitiul 6 

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/08/lab08/ex06

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/08/lab08/ex06 
╰─➤ dotnet run

Shared Variable: 0
Elapsed Time: 1004ms

**Explicatie:** Codul are un bug potential - daca o exceptie apare intre `Monitor.Enter()` si `Monitor.Exit()`, lock-ul nu va fi eliberat, cauzand deadlock.

---

## Exercitiul 7


╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/08/lab08/ex07 
╰─➤ dotnet run

Shared Variable: 0
Elapsed Time: 1002ms

**Explicatie:** Implementarea corecta foloseste `lockTaken` flag si blocul `finally` pentru a garanta ca `Monitor.Exit()` este apelat chiar daca apare o exceptie.

---

## Exercitiul 8 

**Descriere:** Folosirea `Mutex` pentru a asigura ca doar o instanta a procesului de scanare antivirus ruleaza simultan.

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/08/lab08/ex08 
╰─➤ dotnet run

[120004] Scanning your device for malware...
[120004] Scanned File['0']
[120004] Written results for File['0']
[120004] Scanned File['1']
...
[120004] Finished!
[120004] Releasing the mutex...
Press any key to close the program.

Output (a doua instanță, rulată simultan):

[120123] A scanning session is already running
Press any key to close the program.

**Explicatie:** Mutex-ul numit "AV_0xAAEC" asigura ca doar o instanta a scanner-ului poate rula. A doua instanta detecteaza mutex-ul si se inchide cu un mesaj.

---

## Exercitiul 9 

**Descriere:** Gestionarea situatiei cand un proces anterior a achizitionat mutex-ul dar a terminat brusc fara sa-l elibereze.

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/08/lab08/ex09 
╰─➤ dotnet run

[120004] Scanning your device for malware...
[120004] Scanned File['0']
[120004] Written results for File['0']
...
[120004] Finished!
[120004] Releasing the mutex...
Press any key to close the program.

**Explicatie:** Implementarea corecta foloseste `mutexAcquired` flag si trateaza `AbandonedMutexException`. Cand mutex-ul este abandonat, procesul curent il preia si continua operatia.

---

## Exercitiul 10 

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/08/lab08/ex10 
╰─➤ dotnet run

**Explicatie:** `ReaderWriterLockSlim` permite ca multiple thread-uri sa citeasca simultan din dictionary, dar asigura acces exclusiv pentru scriere. Acest lucru imbunatateste performanta fata de un simple lock in scenarii cu multe operatii de citire.

Validarile din `Main()` verifica ca:
- `READ_READ_CHECK != N * 2 * P` (citirile nu se blocheaza reciproc)
- `READ_WRITE_CHECK == N * 2 * P * 2` (citirile si scrierile se sincronizeaza)
- `WRITE_WRITE_CHECK == N * 2 * P` (scrierile se exclud reciproc)

