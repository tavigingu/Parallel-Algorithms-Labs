#include <stdio.h>
#include <stdlib.h>

int N;
int printLevel;
long long moveCount = 0;

void getArgs(int argc, char **argv)
{
	if(argc < 3) {
		printf("Not enough parameters: ./program N printLevel\nprintLevel: 0=no, 1=some, 2=verbose\n");
		exit(1);
	}
	N = atoi(argv[1]);
	printLevel = atoi(argv[2]);
}

void hanoi(int n, char from, char to, char aux) {
	if (n == 1) {
		moveCount++;
		if (printLevel >= 1) {
			printf("Move disk 1 from %c to %c\n", from, to);
		}
		return;
	}
	
	// Move n-1 disks from 'from' to 'aux', using 'to' as auxiliary
	hanoi(n - 1, from, aux, to);
	
	// Move the nth disk from 'from' to 'to'
	moveCount++;
	if (printLevel >= 1) {
		printf("Move disk %d from %c to %c\n", n, from, to);
	}
	
	// Move n-1 disks from 'aux' to 'to', using 'from' as auxiliary
	hanoi(n - 1, aux, to, from);
}

int main(int argc, char** argv)
{
	getArgs(argc, argv);
	
	hanoi(N, 'A', 'C', 'B');
	
	printf("Total moves: %lld\n", moveCount);
	printf("Expected moves: %lld\n", (1LL << N) - 1);
	
	if (moveCount == (1LL << N) - 1) {
		printf("CORRECT\n");
	} else {
		printf("INCORRECT\n");
	}
	
	return 0;
}
