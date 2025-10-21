#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

pthread_barrier_t barrier1;
pthread_barrier_t barrier2;

int printLevel;
int N;
int P;


void* threadFunction(void *var)
{
	int thread_id = *(int*)var;
	
	//TODO preserve the correct order by using barriers
	//abia dupa ce toate 3 threadurile au ajuns la bariera 1 pot merge mai departe adica dupa ce deja thread 2 a afisat
	//abia dupa ce toate 3 threadurile au ajuns la bariera 2 pot merge mai departe adica dupa ce deja si thread 1 a afisat
	//ramane de afisat doar thread 0
	if(thread_id==0) {
		pthread_barrier_wait(&barrier1);
		pthread_barrier_wait(&barrier2);
		printf("I should be displayed last\n");
	}
	else if(thread_id==1) {
		pthread_barrier_wait(&barrier1);
		printf("I should be displayed in the middle\n");
		pthread_barrier_wait(&barrier2);
	}
	else if(thread_id==2) {
		printf("I should be displayed first\n");
		pthread_barrier_wait(&barrier1);
		pthread_barrier_wait(&barrier2);
	}
}

void getArgs(int argc, char **argv)
{

}

void init() 
{
	pthread_barrier_init(&barrier1, NULL, 3);
	pthread_barrier_init(&barrier2, NULL, 3);
}	

void printAll()
{
}

void printPartial()
{
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

int main(int argc, char *argv[])
{
	getArgs(argc, argv);
	init();

	P = 3; // ATTENTION, WE OVERWRITE THE NUMBER OF THREADS. WE ONLY NEED 3
	int i;

	pthread_t tid[P];
	int thread_id[P];
	for(i = 0;i < P; i++)
		thread_id[i] = i;
	//DO NOT EDIT
	for(i = 0; i < P; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}
	//DO NOT EDIT
	for(i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}
	//DO NOT EDIT
	print();

	pthread_barrier_destroy(&barrier1);
	pthread_barrier_destroy(&barrier2);

	return 0;
}
