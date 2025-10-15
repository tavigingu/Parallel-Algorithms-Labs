#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int printLevel;
int N;
int P;
long long* v;
long long* partial_sums; // suma partiala a fiecarui thread

void getArgs(int argc, char **argv) {
    if(argc < 4) {
        printf("Not enough parameters: ./program N printLevel P\n");
        exit(1);
    }
    N = atoi(argv[1]);
    printLevel = atoi(argv[2]);
    P = atoi(argv[3]);
}

long long * allocVector(int N) {
    long long *v = malloc(sizeof(long long) * N);
    if(v == NULL) {
        printf("malloc failed!");
        exit(1);
    }
    return v;
}

void init() {
    v = allocVector(N);
    partial_sums = calloc(P, sizeof(long long));
    if(partial_sums == NULL) {
        printf("calloc failed!\n");
        exit(1);
    }

    for(long long i = 0; i < N; i++)
        v[i] = i + 1;
}

void* threadFunction(void *var) {
    int tid = *(int*)var;
    long long start = tid * (N / P);
    long long end = (tid == P-1) ? N : (tid + 1) * (N / P);

    long long local_sum = 0;
    for(long long i = start; i < end; i++)
        local_sum += v[i];

    partial_sums[tid] = local_sum;
    return NULL;
}

void printResult() {
    long long sum = 0;
    for(int i = 0; i < P; i++)
        sum += partial_sums[i];

    if(printLevel > 0)
        printf("Sum: %lli\n", sum);
}

int main(int argc, char *argv[]) {
    getArgs(argc, argv);
    init();

    pthread_t tid[P];
    int thread_id[P];
    for(int i = 0; i < P; i++)
        thread_id[i] = i;

    for(int i = 0; i < P; i++)
        pthread_create(&tid[i], NULL, threadFunction, &thread_id[i]);

    for(int i = 0; i < P; i++)
        pthread_join(tid[i], NULL);

    printResult();

    free(v);
    free(partial_sums);
    return 0;
}
