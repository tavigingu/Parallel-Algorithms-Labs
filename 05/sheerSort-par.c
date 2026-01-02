#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int printLevel;
int N;
int P;
int *v;
int *vQSort;
int rows, cols;

pthread_barrier_t barrier;

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
	if(argc < 4) {
		printf("Not enough parameters: ./program N printLevel P\nprintLevel: 0=no, 1=some, 2=verbose\n");
		exit(1);
	}
	N = atoi(argv[1]);
	printLevel = atoi(argv[2]);
	P = atoi(argv[3]);
	
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
	int i;
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

void *threadFunction(void *arg) {
	int thread_id = *(int *)arg;
	int i, j;
	int numPhases = (int)ceil(log2(rows > cols ? rows : cols)) + 1;
	int phase;
	
	for(phase = 0; phase < numPhases; phase++) {
		// Sort rows - each thread handles a subset
		for(i = thread_id; i < rows; i += P) {
			if(i % 2 == 0)
				sortRow(v, i, 1); // ascending
			else
				sortRow(v, i, 0); // descending
		}
		
		pthread_barrier_wait(&barrier);
		
		// Sort columns - each thread handles a subset
		for(j = thread_id; j < cols; j += P) {
			sortColumn(v, j);
		}
		
		pthread_barrier_wait(&barrier);
	}
	
	// Final row sort - all ascending
	for(i = thread_id; i < rows; i += P) {
		sortRow(v, i, 1);
	}
	
	return NULL;
}

int main(int argc, char *argv[])
{
	int i;
	getArgs(argc, argv);
	init();

	// make copy to check it against qsort
	// DO NOT MODIFY
	for(i = 0; i < N; i++)
		vQSort[i] = v[i];
	qsort(vQSort, N, sizeof(int), cmp);

	// Parallel Sheer Sort
	pthread_barrier_init(&barrier, NULL, P);
	
	pthread_t tid[P];
	int thread_id[P];
	for(i = 0; i < P; i++)
		thread_id[i] = i;

	for(i = 0; i < P; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}

	for(i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}
	
	pthread_barrier_destroy(&barrier);

	print();

	free(v);
	free(vQSort);
	return 0;
}
