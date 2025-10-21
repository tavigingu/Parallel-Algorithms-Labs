#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int printLevel;
int N;
int P;
int **a;
int **b;
int **c;
int ***c_partial; // rezultate parțiale pentru fiecare thread

void *threadFunction(void *args)
{
    int thread_id = *(int *)args;

    int start_k = thread_id * (N / P);
    int end_k = (thread_id + 1) * (N / P);
    if (thread_id == P - 1) {
        end_k = N;
    }

    int i, j, k;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            int sum = 0;
            for (k = start_k; k < end_k; k++) {
                sum += a[i][k] * b[k][j];
            }
            c_partial[thread_id][i][j] = sum;
        }
    }

    return NULL;
}

void getArgs(int argc, char **argv)
{
    if (argc < 4) {
        printf("Not enough parameters: ./program N printLevel P\n");
        exit(1);
    }
    N = atoi(argv[1]);
    printLevel = atoi(argv[2]);
    P = atoi(argv[3]);
}

void init()
{
    a = malloc(sizeof(int *) * N);
    b = malloc(sizeof(int *) * N);
    c = malloc(sizeof(int *) * N);
    c_partial = malloc(sizeof(int **) * P);
    if (a == NULL || b == NULL || c == NULL || c_partial == NULL) {
        printf("malloc failed!\n");
        exit(1);
    }

    for (int p = 0; p < P; p++) {
        c_partial[p] = malloc(sizeof(int *) * N);
        for (int i = 0; i < N; i++) {
            c_partial[p][i] = calloc(N, sizeof(int));
        }
    }

    for (int i = 0; i < N; i++) {
        a[i] = malloc(sizeof(int) * N);
        b[i] = malloc(sizeof(int) * N);
        c[i] = calloc(N, sizeof(int));
        if (a[i] == NULL || b[i] == NULL || c[i] == NULL) {
            printf("malloc failed!\n");
            exit(1);
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i <= j) {
                a[i][j] = 1;
                b[i][j] = 1;
            } else {
                a[i][j] = 0;
                b[i][j] = 0;
            }
        }
    }
}

void combineResults()
{
    for (int p = 0; p < P; p++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                c[i][j] += c_partial[p][i][j];
            }
        }
    }
}

void printAll()
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%i\t", c[i][j]);
        }
        printf("\n");
    }
}

void printPartial()
{
    printAll();
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

int main(int argc, char *argv[])
{
    getArgs(argc, argv);
    init();

    pthread_t tid[P];
    int thread_id[P];
    for (int i = 0; i < P; i++)
        thread_id[i] = i;

    for (int i = 0; i < P; i++) {
        pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
    }

    for (int i = 0; i < P; i++) {
        pthread_join(tid[i], NULL);
    }

    combineResults();
    print();

    return 0;
}
