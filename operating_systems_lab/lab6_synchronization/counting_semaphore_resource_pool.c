/*
 * Lab 6 - Question 3
 * Implements a counting semaphore to control access to a limited
 * pool of resources. Five worker threads attempt to use a resource
 * pool of size 2 (e.g., printers or database connections).
 * The semaphore guarantees that at most two threads access the
 * resource concurrently - remaining threads block on sem_wait()
 * and resume when a slot is released by sem_post().
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N_THREADS 5
#define POOL_SIZE 2

sem_t pool;   /* counting semaphore (initial value = POOL_SIZE) */

void *worker(void *arg) {
    int id = *(int *)arg;

    printf("[Worker %d] requesting a resource...\n", id);
    sem_wait(&pool);                              /* wait() - acquire a slot (P) */
    printf("[Worker %d] >>> acquired resource, working.\n", id);
    sleep(2);                                     /* simulate work */
    printf("[Worker %d] <<< releasing resource.\n", id);
    sem_post(&pool);                              /* signal() - release the slot (V) */

    return NULL;
}

int main() {
    pthread_t t[N_THREADS];
    int ids[N_THREADS];

    sem_init(&pool, 0, POOL_SIZE);   /* 2 resources available */

    for (int i = 0; i < N_THREADS; i++) {
        ids[i] = i + 1;
        pthread_create(&t[i], NULL, worker, &ids[i]);
    }

    for (int i = 0; i < N_THREADS; i++)
        pthread_join(t[i], NULL);

    sem_destroy(&pool);
    printf("Main: all workers finished.\n");
    return 0;
}
