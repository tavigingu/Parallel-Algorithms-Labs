# Laborator 2

## ex 6 addMatrix-seq.c

## ex 7 addMatric-par.c
Paralelizarea trateaza matricea ca pe un vector liniar, impartind indicii intre threaduri; fiecare thread parcurge segmentul sau si aduna elementele corespunzatoare in c[row][col], calculand row = index / nrCol si col = index % nrCol

## ex 8 subString-seq.c

## ex 9 subString-par.c
Paralelizarea se face impartind stringul in segmente pentru fiecare thread, fiecare thread verificand caracterele din segmentul sau si tinand un contor pentru substringul cautat. Daca substringul este gasit, threadul seteaza un flag global, iar daca contorul este mai mare de zero la sfarsitul segmentului, threadul poate extinde temporar segmentul (end++) pentru a prinde cazurile in care substringul este impartit intre doua segmente.