#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#include "Workers.h"

int N;
int printLevel;
pthread_mutex_t printMutex;
int COLORS = 3;
int numVertices = 10;
int numEdges = 30;
int graphDefault[][2] = { { 0, 1 }, { 0, 4 }, { 0, 5 }, { 1, 0 }, { 1, 2 }, { 1, 6 }, { 2, 1 }, { 2, 3 }, { 2, 7 },
				{ 3, 2 }, { 3, 4 }, { 3, 8 }, { 4, 0 }, { 4, 3 }, { 4, 9 }, { 5, 0 }, { 5, 7 }, { 5, 8 }, { 6, 1 },
				{ 6, 8 }, { 6, 9 }, { 7, 2 }, { 7, 5 }, { 7, 9 }, { 8, 3 }, { 8, 5 }, { 8, 6 }, { 9, 4 }, { 9, 6 },
				{ 9, 7 } };
int ** graph;

void initDefaultGraph() {
	graph = (int**)malloc(sizeof(int*)*numEdges);
	for(int i = 0; i < numEdges; i++) {
		graph[i] = (int*)malloc(sizeof(int)*2);
		graph[i][0] = graphDefault[i][0];
		graph[i][1]= graphDefault[i][1];
	}
}

void generateGraph(int nVertices, int nEdges) {
	srand(42);
	numVertices = nVertices;
	numEdges = nEdges;
	graph = (int**)malloc(sizeof(int*)*numEdges);
	for(int i = 0; i < numEdges; i++) {
		graph[i] = (int*)malloc(sizeof(int)*2);
		graph[i][0] = rand()%numVertices;
		graph[i][1] = rand()%numVertices;
		if(graph[i][0] == graph[i][1])
			i--;
	}
}

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

void printAll(int * v, int N)
{
	int i;
	int max = 1; // Here be dragons: nu vrem min_int pentru ca merge si cu 1
	for(i = 0; i < N; i++)
		if(max < v[i])
			max = v[i];

	int displayWidth = 2 + log10(max);
	char * aux = malloc(1000*sizeof(char)); 
	char * vectorValue = malloc(10*sizeof(char));
	for(i = 0; i < N; i++) {
		sprintf(vectorValue, "%*i", displayWidth, v[i]);
		strcat(aux, vectorValue);
		strcat(aux, " ");
	}
	printf("%s\n", aux);
}

void print(int * v, int N)
{
	if(printLevel == 0)
		return;
	pthread_mutex_lock(&printMutex);
	if(printLevel == 1)
		printAll(v, N);
	else
		printAll(v, N);
	pthread_mutex_unlock(&printMutex);
}

int isEdge(int a, int b) {
	for (int i = 0; i < numEdges; i++) {
		if (graph[i][0] == a && graph[i][1] == b)
			return 1;
	}
	return 0;
}

int verifyColors(int colors[], int step) {
	for (int i = 0; i < step; i++) {
		if (colors[i] == colors[step] && isEdge(i, step))
			return 0;
	}
	return 1;
}

typedef struct ColorData {
	int * colors;
	int step;
} ColorData;

void colorGraph(void * data, int thread_id) {
	ColorData colorData = *(ColorData*)data;
	int * colors = colorData.colors;
	int step = colorData.step;
	
	if (step == numVertices) {
		print(colors, step);
		return;
	}

	// for the node at position step try all possible colors
	for (int i = 0; i < COLORS; i++) {
		int * newColors = (int*) malloc(sizeof(int)*numVertices);
		memcpy ( newColors, colors, sizeof(int)*numVertices );
		
		newColors[step] = i;
		if (verifyColors(newColors, step)) {
			Task task;
			ColorData * newData = (ColorData*)malloc(sizeof(ColorData));
			newData->colors = newColors;
			newData->step = step + 1;
			task.data = newData;
			task.runTask = colorGraph;
			putTask(task);
		}
	}
}

int main(int argc, char** argv) 
{
	getArgs(argc, argv);
	pthread_mutex_init(&printMutex, NULL);
	initDefaultGraph();
	//generateGraph(N, 2*N);
	
	startWorkers();
	
	int * colors = (int*) malloc(sizeof(int)*numVertices);
	
	Task task;
	ColorData * newData = (ColorData*)malloc(sizeof(ColorData));
	newData->colors = colors;
	newData->step = 0;
	task.data = newData;
	task.runTask = colorGraph;
	putTask(task);
	
	// Wait for all tasks to finish
	while(gotTasks < putTasks) {
		usleep(1000);
	}
	forceShutDownWorkers();
	joinWorkerThreads();
	
	pthread_mutex_destroy(&printMutex);
	return 0;
}