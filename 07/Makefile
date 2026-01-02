par: sample-par getPath-par colorGraph-par queens-par hanoi-par

seq: getPath-seq colorGraph-seq queens-seq hanoi-seq

checkSubset: checkSubset.c
	gcc -o checkSubset checkSubset.c -Wall -O3 -std=gnu99

sample-par: sample-par.c Workers.c Workers.h
	gcc -o sample-par sample-par.c Workers.h Workers.c -Wall -O3 -pthread -std=gnu99 -lm
getPath-par: getPath-par.c Workers.c Workers.h
	gcc -o getPath-par getPath-par.c Workers.h Workers.c -Wall -O3 -pthread -std=gnu99 -lm
colorGraph-par: colorGraph-par.c Workers.c Workers.h
	gcc -o colorGraph-par colorGraph-par.c Workers.h Workers.c -Wall -O3 -pthread -std=gnu99 -lm
queens-par: queens-par.c Workers.c Workers.h
	gcc -o queens-par queens-par.c Workers.h Workers.c -Wall -O3 -pthread -std=gnu99 -lm
hanoi-par: hanoi-par.c Workers.c Workers.h
	gcc -o hanoi-par hanoi-par.c Workers.h Workers.c -Wall -O3 -pthread -std=gnu99 -lm

sample-seq: sample-seq.c
	gcc -o sample-seq sample-seq.c -Wall -O3 -std=gnu99 -lm
getPath-seq: getPath-seq.c
	gcc -o getPath-seq getPath-seq.c -Wall -O3 -std=gnu99 -lm
colorGraph-seq: colorGraph-seq.c
	gcc -o colorGraph-seq colorGraph-seq.c -Wall -O3 -std=gnu99 -lm
queens-seq: queens-seq.c
	gcc -o queens-seq queens-seq.c -Wall -O3 -std=gnu99 -lm
hanoi-seq: hanoi-seq.c
	gcc -o hanoi-seq hanoi-seq.c -Wall -O3 -std=gnu99 -lm

clean:
	rm -f sample-par sample-seq
	rm -f getPath-par getPath-seq
	rm -f colorGraph-par colorGraph-seq
	rm -f queens-par queens-seq
	rm -f hanoi-par hanoi-seq
	rm -f checkSubset
	rm -f out* test*.txt *.sorted