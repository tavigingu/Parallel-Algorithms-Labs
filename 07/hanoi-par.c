#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "Workers.h"

int N;
int printLevel;
pthread_mutex_t printMutex;
pthread_mutex_t countMutex;
long long moveCount = 0;

typedef struct HanoiData {
	int n;
	char from;
	char to;
	char aux;
} HanoiData;

void getArgs(int argc, char **argv)
{
	if(argc < 4) {
		printf("Not enough parameters: ./program N printLevel P\nprintLevel: 0=no, 1=some, 2=verbose\n");
		exit(1);
	}
	N = atoi(argv[1]);
	printLevel = atoi(argv[2]);
	P = atoi(argv[3]);
}

void hanoi(void * data, int thread_id) {
	HanoiData hanoiData = *(HanoiData*)data;
	int n = hanoiData.n;
	char from = hanoiData.from;
	char to = hanoiData.to;
	char aux = hanoiData.aux;
	
	if (n == 1) {
		pthread_mutex_lock(&countMutex);
		moveCount++;
		pthread_mutex_unlock(&countMutex);
		
		if (printLevel >= 1) {
			pthread_mutex_lock(&printMutex);
			printf("Move disk 1 from %c to %c\n", from, to);
			pthread_mutex_unlock(&printMutex);
		}
		return;
	}
	
	// Move n-1 disks from 'from' to 'aux', using 'to' as auxiliary
	Task task1;
	HanoiData * newData1 = (HanoiData*)malloc(sizeof(HanoiData));
	newData1->n = n - 1;
	newData1->from = from;
	newData1->to = aux;
	newData1->aux = to;
	task1.data = newData1;
	task1.runTask = hanoi;
	putTask(task1);
	
	// Move the nth disk from 'from' to 'to'
	pthread_mutex_lock(&countMutex);
	moveCount++;
	pthread_mutex_unlock(&countMutex);
	
	if (printLevel >= 1) {
		pthread_mutex_lock(&printMutex);
		printf("Move disk %d from %c to %c\n", n, from, to);
		pthread_mutex_unlock(&printMutex);
	}
	
	// Move n-1 disks from 'aux' to 'to', using 'from' as auxiliary
	Task task2;
	HanoiData * newData2 = (HanoiData*)malloc(sizeof(HanoiData));
	newData2->n = n - 1;
	newData2->from = aux;
	newData2->to = to;
	newData2->aux = from;
	task2.data = newData2;
	task2.runTask = hanoi;
	putTask(task2);
}

int main(int argc, char** argv)
{
	getArgs(argc, argv);
	pthread_mutex_init(&printMutex, NULL);
	pthread_mutex_init(&countMutex, NULL);
	
	startWorkers();
	
	Task task;
	HanoiData * newData = (HanoiData*)malloc(sizeof(HanoiData));
	newData->n = N;
	newData->from = 'A';
	newData->to = 'C';
	newData->aux = 'B';
	task.data = newData;
	task.runTask = hanoi;
	putTask(task);
	
	// Wait for all tasks to finish
	while(gotTasks < putTasks) {
		usleep(1000);
	}
	forceShutDownWorkers();
	joinWorkerThreads();
	
	printf("Total moves: %lld\n", moveCount);
	printf("Expected moves: %lld\n", (1LL << N) - 1);
	
	if (moveCount == (1LL << N) - 1) {
		printf("CORRECT\n");
	} else {
		printf("INCORRECT\n");
	}
	
	pthread_mutex_destroy(&printMutex);
	pthread_mutex_destroy(&countMutex);
	return 0;
}
