#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

void* threadFunction(void *var)
{
	int thread_id = *(int*)var;

	printf("Hello world from thread %i\n", thread_id);
}

void* threadFunction2(void *var)
{
	int thread_id = *(int*)var;

	printf("Salutare planeta! %i\n", thread_id);
}

int main(int argc, char **argv)
{
	int P = 2;
	int i;

	pthread_t tid[P];
	int thread_id[P];
	for(i = 0;i < P; i++)
		thread_id[i] = i;

	
	pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[0]));
	pthread_create(&(tid[i]), NULL, threadFunction2, &(thread_id[1]));
	
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	

	return 0;
}
