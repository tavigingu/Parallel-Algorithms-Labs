# Laborator 10

## Exercitiul 1

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/lab10/ex01
╰─➤ dotnet run

TID[1]
TID[4] => 0
TID[4]
TID[8] => 1
TID[4] => 2
TID[4] => 3
TID[4] => 4
TID[4] => 5
TID[8]
TID[8]

**Explicatie:** Programul demonstreaza utilizarea `async/await` si `Task`. TID-urile (Thread IDs) sunt diferite deoarece task-urile async pot rula pe thread-uri diferite din ThreadPool. SynchronizationContext controleaza unde continua executia dupa un `await`.

**Cu linia 32 comentata (`//await task_1`):** Programul se termina dupa afisarea ultimului TID, fara sa astepte finalizarea task_1.

**Cu linia 32 decomentata (`await task_1`):** Programul asteapta finalizarea task_1 inainte de a se termina. Toate cele 50 de iteratii vor fi afisate.

---

## Exercitiul 2

**Explicatie:** Implementeaza un client async care:
- `Requester` obtine URL-uri de imagini cu exponential backoff (1s, 2s, 4s...) cand serverul returneaza RETRY-LATER
- `Downloader` ruleaza in paralel si descarca imaginile din lista URL-urilor obtinute
- Foloseste `HttpClient` si `Task.Delay()` pentru asteptare async
- Sincronizarea se face prin lista partajata cu lock

**Nota:** Necesita backend-ul de la lab09/ex05 sa ruleze pe localhost:5000

---

## Exercitiul 3

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/lab10/ex03
╰─➤ dotnet run

BEFORE ProgressChanged => 10%
AFTER ProgressChanged => 10%
TID 7: ProgressChanged => 10%
BEFORE ProgressChanged => 20%
AFTER ProgressChanged => 20%
TID 5: ProgressChanged => 20%
BEFORE ProgressChanged => 30%
AFTER ProgressChanged => 30%
TID 7: ProgressChanged => 30%
...

**Explicatie:**

**Cu linia 28 comentata:** `ProgressChanged` este apelat sincron, output-ul arata secvential BEFORE -> AFTER -> ProgressChanged pentru fiecare iteratie.

**Cu linia 28 decomentata (`await Task.Delay((i - 1) * 100)`):** Se introduce delay intre raportarea progresului si continuarea loop-ului. Evenimentul `ProgressChanged` este pus in coada si poate fi executat dupa ce loop-ul continua, rezultand o ordine mixata a mesajelor.

---

## Exercitiul 4

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/lab10/ex04
╰─➤ dotnet run

TID 7: Task2 ProgressChanged => 10%
TID 5: Task1 ProgressChanged => 10%
TID 7: Task2 ProgressChanged => 20%
TID 5: Task1 ProgressChanged => 20%
TID 7: Task2 ProgressChanged => 30%
TID 7: Task2 ProgressChanged => 40%
TID 9: Task1 ProgressChanged => 30%
TID 8: Task2 ProgressChanged => 50%
TID 9: Task1 ProgressChanged => 40%
TID 7: Task2 ProgressChanged => 60%
TID 7: Task2 ProgressChanged => 70%
TID 9: Task1 ProgressChanged => 50%
TID 7: Task2 ProgressChanged => 80%
TID 9: Task1 ProgressChanged => 60%
TID 7: Task2 ProgressChanged => 90%
TID 8: Task2 ProgressChanged => 100%
TID 8: Task1 ProgressChanged => 70%
TID 7: Task1 ProgressChanged => 80%
TID 8: Task1 ProgressChanged => 90%
TID 9: Task1 ProgressChanged => 100%
Something went wrong! => The method or operation is not implemented.
Task1 result: 39
Task2 result: 12345678910

**Explicatie - Modificari:**
1. **Raportare diferentiata:** Creaza obiecte `Progress` separate (`progress1`, `progress2`) pentru fiecare task, cu handlere care afiseaza "Task1" sau "Task2" in mesaj.

2. **Salvare rezultate:** Dupa `Task.WhenAll()`, verifica `task_1.IsCompletedSuccessfully` si `task_2.IsCompletedSuccessfully` inainte de a accesa `task_1.Result` si `task_2.Result`. Astfel se pot printa rezultatele chiar daca task_3 arunca exceptie (INTENTIONAT).

**Nota:** Exceptia "The method or operation is not implemented" este INTENTIONATA - task_3 arunca exceptie pentru a demonstra ca putem salva rezultatele task-urilor care au reusit chiar daca alte task-uri esueaza.

---

## Exercitiul 5

**Explicatie:**

**Cu linia 17 comentata:** Dupa afisarea primului rezultat, programul se termina imediat. Task-urile raman sa ruleze in background, consumand resurse inutil.

**Cu linia 17 decomentata (`await Task.Delay(4000)`):** Observam ca celelalte task-uri continua sa lucreze dupa ce programul ar trebui sa se termine.

**Prevenir risipa:** Adauga `CancellationToken` la toate task-urile. Dupa `Task.WhenAny()`, apeleaza `cts.Cancel()` pentru a opri task-urile care nu au terminat.

---

## Exercitiul 6

╭─tavi@tavi-LOQ-15IAX9 ~/Parallel-Algorithms-Labs/lab10/ex06
╰─➤ dotnet run

01
01234
0123456789

**Explicatie:** Pentru a procesa task-urile in ordinea finalizarii (nu in ordinea din array), folosim `Task.WhenAny()` intr-un loop. Task-urile sunt procesate in ordinea: task_2 (2 iteratii) -> task_3 (5 iteratii) -> task_1 (10 iteratii).

---

## Exercitiul 7

**Explicatie - Modificari:**
1. Creaza `CancellationTokenSource` separate pentru fiecare task (`cts1`, `cts2`)
2. Foloseste `Task.WhenAny(task1, task2)` pentru a determina care task termina primul
3. Cancelează task-ul care nu a terminat primul
4. Afiseaza rezultatul task-ului castigator

**Rezultat:** Task-ul care termina primul isi afiseaza rezultatul, celalalt este intrerupt prin `CancellationToken`.

---

## Exercitiul 8

**Explicatie:** Implementeaza client pentru doua API-uri de bursa:
1. **AlphaVantage** - interogheaza pretul actiunii IBM
2. **Finnhub** - interogheaza pretul actiunii AAPL

Ambele task-uri ruleaza in paralel. Primul care returneaza succes afiseaza rezultatul si celelalte sunt anulate prin `CancellationToken`. Fiecare client are retry logic (5 incercari) cu delay de 1 secunda intre incercari.

**Nota:** API key-urile sunt demo/sandbox - pentru productie trebuie inlocuite cu chei valide.

