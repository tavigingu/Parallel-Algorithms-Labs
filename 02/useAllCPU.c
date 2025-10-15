#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *threadFunction(void *var)
{
	int thread_id = *(int *)var;

	int a = 2;
	int b = 0;

	for (int i = 0; i < 1000000; i++) {
		b = pow(a, 2);

		for (int j = 0; j < 1000000; j++) {
			b = pow(a, 2);
		}
	}
	// TODO Write code to make me run for at least a minute
}

int main(int argc, char **argv)
{
	int P = 20;
	int i;

	pthread_t tid[P];
	int thread_id[P];
	for (i = 0; i < P; i++)
		thread_id[i] = i;

	for (i = 0; i < P; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}

	for (i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

	return 0;
}
