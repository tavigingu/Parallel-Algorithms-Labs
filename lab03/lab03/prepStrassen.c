#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int printLevel;
int N;
int P;
int A11, A12, A21, A22, B11, B12, B21, B22;
int M1, M2, M3, M4, M5, M6, M7;
int C11, C12, C21, C22;

pthread_barrier_t barrier1;
pthread_barrier_t barrier2;

typedef struct {
    int id;
    int A11, A12, A21, A22;
    int B11, B12, B21, B22;
} thread_args;

void getArgs(int argc, char **argv)
{
	if(argc < 4) {
		printf("Not enough paramters: ./program N printLevel P\nprintLevel: 0=no, 1=some, 2=verbouse\n");
		exit(1);
	}
	N = atoi(argv[1]);
	printLevel = atoi(argv[2]);
	P = atoi(argv[3]);
}

void init()
{
	A11 = 3213215;
	A12 = 5454;
	A21 = 5456;
	A22 = 9898;
	B11 = 54544;
	B12 = 90821;
	B21 = 9807879;
	B22 = 329132;
}

void printPartial()
{
	printf("%i %i %i %i \n", C11, C12, C21, C22);
}

void printAll()
{
	printPartial();
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

void* calc_M1(void* arg)
{
	M1 = (A11 + A22) * (B11 + B22);
	pthread_barrier_wait(&barrier1);
	pthread_barrier_wait(&barrier2);
	return NULL;
}

void* calc_M2(void* arg)
{
	M2 = (A21 + A22) * B11 ;
	pthread_barrier_wait(&barrier1);
	pthread_barrier_wait(&barrier2);
	return NULL;
}

void* calc_M3(void* arg)
{
	M3 = A11 * (B12 - B22);
	pthread_barrier_wait(&barrier1);
	pthread_barrier_wait(&barrier2);
	return NULL;
}

void* calc_M4(void* arg)
{
    M4 = A22 * (B21 - B11);
    pthread_barrier_wait(&barrier1);
    pthread_barrier_wait(&barrier2);
    return NULL;
}

void* calc_M5(void* arg)
{
	M5 = (A11 + A12) * B22;
	pthread_barrier_wait(&barrier1);
	pthread_barrier_wait(&barrier2);
	return NULL;
}

void* calc_M6(void* arg)
{
	M6 = (A21 - A11) * (B11 + B12);
	pthread_barrier_wait(&barrier1);
	pthread_barrier_wait(&barrier2);
	return NULL;
}

void* calc_M7(void* arg)
{
    M7 = (A12 - A22) * (B21 + B22);
    pthread_barrier_wait(&barrier1);
    
	//barrier 1 finished, M1-M7 done
    // calc c11
    C11 = M1 + M4 - M5 + M7;
    
    pthread_barrier_wait(&barrier2);
    return NULL;
}

void* calc_C12(void* arg)
{
    pthread_barrier_wait(&barrier1); // wait M1-M7	
    
    C12 = M3 + M5;
    
    pthread_barrier_wait(&barrier2);
    return NULL;
}

void* calc_C21(void* arg)
{
    pthread_barrier_wait(&barrier1); 
    
    C21 = M2 + M4;
    
    pthread_barrier_wait(&barrier2);
    return NULL;
}

void* calc_C22(void* arg)
{
    pthread_barrier_wait(&barrier1); 
    
    C22 = M1 - M2 + M3 + M6;
    
    pthread_barrier_wait(&barrier2);
    return NULL;
}

int main(int argc, char *argv[])
{
	getArgs(argc, argv);
	init();

	long long i;

	pthread_t threads[10];

	pthread_barrier_init(&barrier1, NULL, 10);
    pthread_barrier_init(&barrier2, NULL, 10);

	pthread_create(&threads[0], NULL, calc_M1, NULL);
    pthread_create(&threads[1], NULL, calc_M2, NULL);
    pthread_create(&threads[2], NULL, calc_M3, NULL);
    pthread_create(&threads[3], NULL, calc_M4, NULL);
    pthread_create(&threads[4], NULL, calc_M5, NULL);
    pthread_create(&threads[5], NULL, calc_M6, NULL);
    pthread_create(&threads[6], NULL, calc_M7, NULL);

	pthread_create(&threads[7], NULL, calc_C12, NULL);
    pthread_create(&threads[8], NULL, calc_C21, NULL);
    pthread_create(&threads[9], NULL, calc_C22, NULL);

	// M1 = (A11 + A22) * (B11 + B22);
	// M2 = (A21 + A22) * B11;
	// M3 = A11 * (B12 - B22);
	// M4 = A22 * (B21 - B11);
	// M5 = (A11 + A12) * B22;
	// M6 = (A21 - A11) * (B11 + B12);
	// M7 = (A12 - A22) * (B21 + B22);
	// C11 = M1 + M4 - M5 + M7;
	// C12 = M3 + M5;
	// C21 = M2 + M4;
	// C22 = M1 - M2 + M3 + M6;
	for(int i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }

	pthread_barrier_destroy(&barrier1);
    pthread_barrier_destroy(&barrier2);
	print();

	return 0;
}
