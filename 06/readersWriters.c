#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>

int N;
int P;
int printLevel;

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

int resource = 0;

int read_write_check = 0;
int write_write_check = 0;
int read_read_check = 0;
pthread_mutex_t rwmutex;

sem_t write_sem;
pthread_mutex_t read_mutex;
int read_count = 0;

int get() {
	int temp = read_read_check;
	// Small delay to increase chance of concurrent access
	for(volatile int i = 0; i < 10; i++);
	read_read_check = temp + 2;
	
	read_write_check += 2;
	return resource;
}

void put(int value) {
	write_write_check += 2;
	read_write_check += 2;
	resource = value;
}


//HERE IS WHERE YOU NEED TO IMPLEMENT YOUR SOLUTION
int get_safe() {
	pthread_mutex_lock(&read_mutex);
	read_count++;
	if (read_count == 1) {
		sem_wait(&write_sem);
	}
	pthread_mutex_unlock(&read_mutex);
	
	int aux = get();
	
	pthread_mutex_lock(&read_mutex);
	read_count--;
	if (read_count == 0) {
		sem_post(&write_sem);
	}
	pthread_mutex_unlock(&read_mutex);
	
	return aux;
}

void put_safe(int value) {
	sem_wait(&write_sem);
	put(value);
	sem_post(&write_sem);
}
//END HERE IS WHERE YOU NEED TO IMPLEMENT YOUR SOLUTION


int value;
void* readerThread(void *var)
{
	int i;

	for (i = 0; i < N; i++) {
		value = get_safe();
	}

	return NULL;
}

void* writerThread(void *var)
{
	int i;

	for (i = 0; i < N; i++) {
		put_safe(i);
	}

	return NULL;
}

int main(int argc, char **argv)
{
	getArgs(argc, argv);

	int i;
	int NREAD=P;
	int NWRITE=P;
	pthread_t tid[NREAD+NWRITE];

	sem_init(&write_sem, 0, 1);
	pthread_mutex_init(&read_mutex, NULL);
	pthread_mutex_init(&rwmutex, NULL);

	for(i = 0; i < NREAD; i++) {
		pthread_create(&(tid[i]), NULL, readerThread, NULL);
	}

	for(; i < NREAD+NWRITE; i++) {
		pthread_create(&(tid[i]), NULL, writerThread, NULL);
	}

	for(i = 0; i < NREAD+NWRITE; i++) {
		pthread_join(tid[i], NULL);
	}

	sem_destroy(&write_sem);
	pthread_mutex_destroy(&read_mutex);
	pthread_mutex_destroy(&rwmutex);

	//printf("read_read_check=%d expected_if_no_parallel=%d\n", read_read_check, N * 2 * P);
	//printf("read_write_check=%d expected=%d\n", read_write_check, N * 2 * P * 2);
	//printf("write_write_check=%d expected=%d\n", write_write_check, N * 2 * P);

	if(N * 2 * P == read_read_check && P > 1) {
		printf("Failed two simultaneous readers\n");
		return 1;
	}
	if(N * 2 * P * 2 != read_write_check) {
		printf("Failed read when write %i %i \n", N * 2 * P * 2, read_write_check);
		return 1;
	}
	if(N * 2 * P != write_write_check) {
		printf("Failed write when write\n");
		return 1;
	}
	printf("Passed all\n");

	return 0;
}
