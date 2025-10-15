#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

char* inString;
char* subString;
int printLevel;
int P; 
int found = 0; //  1 dacă s-a gasit substringul

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void getArgs(int argc, char** argv) {
    if (argc < 5) {
        printf("Usage: ./program <input_string> <sub_string> <printLevel> <P>\n");
        exit(EXIT_FAILURE);
    }

    inString = argv[1];
    subString = argv[2];
    printLevel = atoi(argv[3]);
    P = atoi(argv[4]);
}

void init() {
    if (!inString || !subString || strlen(inString) == 0 || strlen(subString) == 0) {
        printf("Input string sau substring invalid\n");
        exit(EXIT_FAILURE);
    }
}

void printResult() {
    if (printLevel == 0) return;
    if (printLevel >= 1) {
        if (found) printf("Substringul a fost gasit.\n");
        else printf("Substringul NU a fost gasit.\n");
    }
    if (printLevel == 2) { // verbose
        printf("Input string: %s\n", inString);
        printf("Substring cautat: %s\n", subString);
    }
}

void* thread_function(void* var) {
    int id = *(int*)var;
    int inLen = strlen(inString);
    int subLen = strlen(subString);

    int start = inLen * id / P;
    int end = inLen * (id + 1) / P;

    int counter = 0;

    for (int i = start; i < end; i++) {
        pthread_mutex_lock(&mutex);
        if (found) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        pthread_mutex_unlock(&mutex);

        if (inString[i] == subString[counter]) {
            counter++;
            if (counter == subLen) {
                pthread_mutex_lock(&mutex);
                found = 1;
                pthread_mutex_unlock(&mutex);
                break;
            }
        } else {
            counter = 0;
        }

		if (counter > 0 && i == end - 1 && end <= inLen)
			end++;
    }

    return NULL;
}

int main(int argc, char** argv) {
    getArgs(argc, argv);
    init();

    pthread_t tids[P];
    int thread_id[P];

    for (int i = 0; i < P; i++) thread_id[i] = i;

    for (int i = 0; i < P; i++) {
        pthread_create(&tids[i], NULL, thread_function, &(thread_id[i]));
    }

    for (int i = 0; i < P; i++) {
        pthread_join(tids[i], NULL);
    }

    printResult();

    return 0;
}
