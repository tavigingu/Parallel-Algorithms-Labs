CC = gcc
CFLAGS = -Wall -Wextra -pthread

all: bubbleSort-seq mergeSort-seq mergeSort-par oets-par sheerSort-seq sheerSort-par

bubbleSort-seq: bubbleSort-seq.c
	$(CC) $(CFLAGS) bubbleSort-seq.c -o bubbleSort-seq -lm

mergeSort-seq: mergeSort-seq.c
	$(CC) $(CFLAGS) mergeSort-seq.c -o mergeSort-seq -lm

mergeSort-par: mergeSort-par.c
	$(CC) $(CFLAGS) mergeSort-par.c -o mergeSort-par -lm

oets-par: oets-par.c
	$(CC) $(CFLAGS) oets-par.c -o oets-par -lm

sheerSort-seq: sheerSort-seq.c
	$(CC) $(CFLAGS) sheerSort-seq.c -o sheerSort-seq -lm

sheerSort-par: sheerSort-par.c
	$(CC) $(CFLAGS) sheerSort-par.c -o sheerSort-par -lm

clean:
	rm -f bubbleSort-seq mergeSort-seq mergeSort-par oets-par sheerSort-seq sheerSort-par out*

.PHONY: all clean
