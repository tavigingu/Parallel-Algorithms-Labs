#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int printLevel;
int nrLin;
int nrCol;
int P;
int** a;
int** b;
int** c;

int min(int a, int b)
{
	if (a < b) return a;
	return b;
}

// sunt necesare 4 argumente: nrLinii, nrColoane, printLevel, nrThreads
void getArgs(int argc, char** argv)
{
	if (argc < 5) {
		printf("Not enough paramters: ./program N printLevel P\nprintLevel: 0=no, 1=some, 2=verbouse\n");
		exit(1);
	}
	nrLin = atoi(argv[1]);
	nrCol = atoi(argv[2]);
	printLevel = atoi(argv[3]);
	P = atoi(argv[4]);
}

void init()
{
	a = malloc(sizeof(int*) * nrLin);
	b = malloc(sizeof(int*) * nrLin);
	c = malloc(sizeof(int*) * nrLin);

	for (int i = 0; i < nrLin; i++) {
		a[i] = malloc(sizeof(int) * nrCol);
		b[i] = malloc(sizeof(int) * nrCol);
		c[i] = malloc(sizeof(int) * nrCol);
	}
	if (a == NULL || b == NULL || c == NULL) {
		printf("malloc failed!");
		exit(1);
	}

	for (int i = 0; i < nrLin; i++)
		for (int j = 0; j < nrCol; j++) {
			a[i][j] = (i + j) % 500;
			b[i][j] = (i + j) % 500;
		}
}

void printPartial()
{
	int i, j;
	for (i = 0; i < min(10, nrLin); i++)
		for (j = 0; j < nrCol; j++)
			printf("%i ", c[i][j]);
	printf("\n");

	for (i = 20; i < nrLin; i += nrLin / 10)
		for (j = 0; j < nrCol; j++)
			printf("%i ", c[i][j]);
	printf("\n");

	for (i = nrLin - 10; i < nrLin; i++)
		for (j = 0; j < nrCol; j++)
			printf("%i ", c[i][j]);
	printf("\n");
}

void printAll()
{
	int i, j;
	for (i = 0; i < nrLin; i++) {
		for (j = 0; j < nrCol; j++)
			printf("%i ", c[i][j]);
		printf("\n");
	}

	printf("\n");
}

void print()
{
	if (printLevel == 0)
		return;
	else if (printLevel == 1)
		printPartial();
	else
		printAll();
}

void* worker_routine(void* params)
{
	int id = *(int*)params;

	int startIndex = (nrLin * nrCol) * id / P;
	int endIndex = (nrLin * nrCol) * (id + 1) / P;

	for (int i = startIndex; i < endIndex; i++) {
		int row = i / nrCol;
		int col = i % nrCol;
		c[row][col] = a[row][col] + b[row][col];
	}

	return NULL;
}

int main(int argc, char* argv[])
{
	getArgs(argc, argv);
	init();

	pthread_t tids[P];
	int args[P];
	for (int i = 0; i < P; i++) {
		args[i] = i;
	}

	for (int i = 0; i < P; i++) {
		pthread_create(&tids[i], NULL, worker_routine, &(args[i]));
	}

	for (int i = 0; i < P; i++) {
		pthread_join(tids[i], NULL);
	}

	print();

	return 0;
}
