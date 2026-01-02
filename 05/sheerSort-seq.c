#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int printLevel;
int N;
int *v;
int *vQSort;
int rows, cols;

void compareVectors(int *a, int *b) {
	// DO NOT MODIFY
	int i;
	for(i = 0; i < N; i++) {
		if(a[i] != b[i]) {
			printf("Sorted incorrectly\n");
			return;
		}
	}
	printf("Sorted correctly\n");
}

void displayVector(int *v) {
	// DO NOT MODIFY
	int i;
	int max = 1;
	for(i = 0; i < N; i++)
		if(max < log10(v[i]))
			max = log10(v[i]);
	int displayWidth = 2 + max;
	for(i = 0; i < N; i++) {
		printf("%*i", displayWidth, v[i]);
		if(!((i + 1) % 20))
			printf("\n");
	}
	printf("\n");
}

void displayMatrix(int *v, int rows, int cols) {
	int i, j;
	for(i = 0; i < rows; i++) {
		for(j = 0; j < cols; j++) {
			printf("%4d ", v[i * cols + j]);
		}
		printf("\n");
	}
	printf("\n");
}

int cmp(const void *a, const void *b) {
	// DO NOT MODIFY
	int A = *(int*)a;
	int B = *(int*)b;
	return A - B;
}

int cmpDesc(const void *a, const void *b) {
	int A = *(int*)a;
	int B = *(int*)b;
	return B - A;
}

void getArgs(int argc, char **argv)
{
	if(argc < 3) {
		printf("Not enough parameters: ./program N printLevel\nprintLevel: 0=no, 1=some, 2=verbose\n");
		exit(1);
	}
	N = atoi(argv[1]);
	printLevel = atoi(argv[2]);
	
	// Calculate rows and cols (make it square root if possible)
	rows = (int)sqrt(N);
	cols = (N + rows - 1) / rows;
	if(rows * cols != N) {
		printf("N should be perfect square or rows*cols\n");
		exit(1);
	}
}

void init()
{
	int i;
	v = malloc(sizeof(int) * N);
	vQSort = malloc(sizeof(int) * N);
	if(v == NULL) {
		printf("malloc failed!");
		exit(1);
	}

	// generate the vector v with random values
	// DO NOT MODIFY
	srand(42);
	for(i = 0; i < N; i++)
		v[i] = rand() % N;
}

void printPartial()
{
	compareVectors(v, vQSort);
}

void printAll()
{
	displayVector(v);
	displayVector(vQSort);
	compareVectors(v, vQSort);
}

void print()
{
	if(printLevel == 0)
		return;
	else if(printLevel == 1)
		printPartial();
	else
		printAll();
}

void sortRow(int *v, int row, int ascending) {
	if(ascending)
		qsort(&v[row * cols], cols, sizeof(int), cmp);
	else
		qsort(&v[row * cols], cols, sizeof(int), cmpDesc);
}

void sortColumn(int *v, int col) {
	int i, j;
	int *temp = malloc(sizeof(int) * rows);
	
	// Extract column
	for(i = 0; i < rows; i++)
		temp[i] = v[i * cols + col];
	
	// Sort column
	qsort(temp, rows, sizeof(int), cmp);
	
	// Put back
	for(i = 0; i < rows; i++)
		v[i * cols + col] = temp[i];
	
	free(temp);
}

int main(int argc, char *argv[])
{
	int i, j;
	getArgs(argc, argv);
	init();

	// make copy to check it against qsort
	// DO NOT MODIFY
	for(i = 0; i < N; i++)
		vQSort[i] = v[i];
	qsort(vQSort, N, sizeof(int), cmp);

	// Sheer Sort algorithm
	int phase;
	int numPhases = (int)ceil(log2(rows > cols ? rows : cols)) + 1;
	
	for(phase = 0; phase < numPhases; phase++) {
		// Sort rows
		for(i = 0; i < rows; i++) {
			if(i % 2 == 0)
				sortRow(v, i, 1); // ascending
			else
				sortRow(v, i, 0); // descending
		}
		
		// Sort columns
		for(j = 0; j < cols; j++) {
			sortColumn(v, j);
		}
	}
	
	// Final row sort - all ascending
	for(i = 0; i < rows; i++) {
		sortRow(v, i, 1);
	}

	print();

	free(v);
	free(vQSort);
	return 0;
}
