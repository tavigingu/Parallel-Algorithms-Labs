/*
 * Problema fumatorilor (Cigarette Smokers Problem)
 * 
 * Sunt 3 fumatori si un agent.
 * Fiecare fumator are o resursa: unul are tutun, altul hartie, altul chibrituri.
 * Pentru a fuma, un fumator are nevoie de toate 3 resursele.
 * Agentul pune pe masa 2 resurse random.
 * Fumatorul care are a 3-a resursa ia cele 2 de pe masa, fumeaza si semnalizeaza agentul.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define TOBACCO 0
#define PAPER 1
#define MATCHES 2

int N;           // numarul de iteratii
int printLevel;
int P;           // ignorat, folosim 3 fumatori

// Semafoare pentru fiecare fumator
sem_t smoker_sem[3];
sem_t agent_sem;

// Mutex pentru afisare si contorizare
pthread_mutex_t print_mutex;

int smoke_count[3] = {0, 0, 0};
int agent_done = 0;

void* agent_thread(void* arg) {
    (void)arg;
    
    for(int i = 0; i < N; i++) {
        // Asteapta sa fie gata sa puna ingrediente
        sem_wait(&agent_sem);
        
        // Alege random 2 ingrediente de pus pe masa
        int ingredients = rand() % 3;
        
        // Semnalizeaza fumatorul corespunzator
        sem_post(&smoker_sem[ingredients]);
    }
    
    // Asteapta ultimul fumator
    sem_wait(&agent_sem);
    
    pthread_mutex_lock(&print_mutex);
    agent_done = 1;
    pthread_mutex_unlock(&print_mutex);
    
    // Trezeste toti fumatorii pentru a termina
    for(int i = 0; i < 3; i++) {
        sem_post(&smoker_sem[i]);
    }
    
    return NULL;
}

void* smoker_thread(void* arg) {
    int id = *(int*)arg;
    
    while(1) {
        sem_wait(&smoker_sem[id]);
        
        pthread_mutex_lock(&print_mutex);
        if(agent_done) {
            pthread_mutex_unlock(&print_mutex);
            break;
        }
        smoke_count[id]++;
        pthread_mutex_unlock(&print_mutex);
        
        // Semnalizeaza agentul ca a terminat
        sem_post(&agent_sem);
    }
    
    return NULL;
}

int main(int argc, char* argv[]) {
    if(argc != 4) {
        printf("Not enough paramters: ./program N printLevel P\n");
        printf("printLevel: 0=no, 1=some, 2=verbouse\n");
        return 1;
    }
    
    N = atoi(argv[1]);
    printLevel = atoi(argv[2]);
    P = atoi(argv[3]);
    
    srand(time(NULL));
    
    // Initializare semafoare
    for(int i = 0; i < 3; i++) {
        sem_init(&smoker_sem[i], 0, 0);
    }
    sem_init(&agent_sem, 0, 1);
    pthread_mutex_init(&print_mutex, NULL);
    
    // Creare thread-uri
    pthread_t agent;
    pthread_t smokers[3];
    int smoker_ids[3] = {0, 1, 2};
    
    pthread_create(&agent, NULL, agent_thread, NULL);
    
    for(int i = 0; i < 3; i++) {
        pthread_create(&smokers[i], NULL, smoker_thread, &smoker_ids[i]);
    }
    
    // Asteptare thread-uri
    pthread_join(agent, NULL);
    
    for(int i = 0; i < 3; i++) {
        pthread_join(smokers[i], NULL);
    }
    
    // Verificare corectitudine
    int total = smoke_count[0] + smoke_count[1] + smoke_count[2];
    
    if(printLevel == 1) {
        printf("Smoker with tobacco smoked: %d times\n", smoke_count[0]);
        printf("Smoker with paper smoked: %d times\n", smoke_count[1]);
        printf("Smoker with matches smoked: %d times\n", smoke_count[2]);
        printf("Total: %d times\n", total);
    }
    
    if(total == N) {
        printf("CORRECT\n");
    } else {
        printf("INCORRECT: expected %d, got %d\n", N, total);
    }
    
    // Cleanup
    for(int i = 0; i < 3; i++) {
        sem_destroy(&smoker_sem[i]);
    }
    sem_destroy(&agent_sem);
    pthread_mutex_destroy(&print_mutex);
    
    return 0;
}
