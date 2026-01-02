/*
 * Problema frizerului (Sleeping Barber Problem)
 * 
 * Un frizer cu o sala de asteptare cu N scaune.
 * Cand nu sunt clienti, frizerul doarme.
 * Cand vine un client:
 *   - daca frizerul doarme, il trezeste si se aseaza in scaunul frizerului
 *   - daca frizerul e ocupat si sunt scaune libere, asteapta
 *   - daca frizerul e ocupat si nu sunt scaune libere, pleaca
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int N;              // numarul de scaune in sala de asteptare
int printLevel;
int P;              // numarul de clienti

sem_t customers;    // semnalizeaza ca sunt clienti
sem_t barber;       // semnalizeaza ca frizerul e gata
pthread_mutex_t mutex;

int waiting = 0;    // numarul de clienti in asteptare
int served = 0;     // numarul de clienti serviti
int rejected = 0;   // numarul de clienti refuzati

void* barber_thread(void* arg) {
    (void)arg;
    
    while(1) {
        // Asteapta clienti (doarme daca nu sunt)
        sem_wait(&customers);
        
        pthread_mutex_lock(&mutex);
        
        // Verifica daca mai sunt clienti
        if(served >= P) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        
        waiting--;
        
        pthread_mutex_unlock(&mutex);
        
        // Simuleaza tunderea (foarte scurta pentru teste)
        // usleep(100);
        
        served++;
        
        // Semnalizeaza ca a terminat
        sem_post(&barber);
    }
    
    return NULL;
}

void* customer_thread(void* arg) {
    pthread_mutex_lock(&mutex);
    
    if(waiting < N) {
        // Sunt scaune libere
        waiting++;
        
        pthread_mutex_unlock(&mutex);
        
        // Semnalizeaza frizerul
        sem_post(&customers);
        
        // Asteapta sa fie servit
        sem_wait(&barber);
    } else {
        // Nu sunt scaune libere
        rejected++;
        
        pthread_mutex_unlock(&mutex);
    }
    
    free(arg);
    return NULL;
}

int main(int argc, char* argv[]) {
    if(argc != 4) {
        printf("Not enough paramters: ./program N printLevel P\n");
        printf("printLevel: 0=no, 1=some, 2=verbouse\n");
        return 1;
    }
    
    N = atoi(argv[1]);       // numarul de scaune
    printLevel = atoi(argv[2]);
    P = atoi(argv[3]);       // numarul de clienti
    
    // Initializare
    sem_init(&customers, 0, 0);
    sem_init(&barber, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    
    // Creaza thread-ul frizerului
    pthread_t barber_t;
    pthread_create(&barber_t, NULL, barber_thread, NULL);
    
    // Creaza thread-urile clientilor
    pthread_t* customers_t = malloc(P * sizeof(pthread_t));
    
    for(int i = 0; i < P; i++) {
        int* id = malloc(sizeof(int));
        *id = i;
        pthread_create(&customers_t[i], NULL, customer_thread, id);
        
        // Adauga un mic delay intre sosirea clientilor (optional)
        // usleep(10);
    }
    
    // Asteapta toti clientii
    for(int i = 0; i < P; i++) {
        pthread_join(customers_t[i], NULL);
    }
    
    // Trezeste frizerul pentru terminare
    sem_post(&customers);
    pthread_join(barber_t, NULL);
    
    // Rezultate
    if(printLevel == 1) {
        printf("Customers served: %d\n", served);
        printf("Customers rejected: %d\n", rejected);
        printf("Total customers: %d\n", P);
    }
    
    if(served + rejected == P) {
        printf("CORRECT\n");
    } else {
        printf("INCORRECT: served=%d + rejected=%d != total=%d\n", served, rejected, P);
    }
    
    // Cleanup
    free(customers_t);
    sem_destroy(&customers);
    sem_destroy(&barber);
    pthread_mutex_destroy(&mutex);
    
    return 0;
}
