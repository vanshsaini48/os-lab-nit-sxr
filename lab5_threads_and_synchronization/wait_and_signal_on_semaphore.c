/*
 * Lab 5 - Question 1
 * Implements wait() and signal() operations on a counting semaphore.
 * wait()   (P operation) decrements the semaphore value and blocks if zero.
 * signal() (V operation) increments the semaphore and wakes a waiting thread.
 * POSIX equivalents: sem_wait() and sem_post().
 * Thread B must wait for a signal from Thread A before it can proceed.
 */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sync_sem;   /* semaphore used for signalling */

void *thread_A(void *arg) {
    (void)arg;
    printf("[Thread A] doing some work...\n");
    sleep(2);
    printf("[Thread A] work done, calling signal() on semaphore.\n");
    sem_post(&sync_sem);   /* signal() - V operation */
    return NULL;
}

void *thread_B(void *arg) {
    (void)arg;
    printf("[Thread B] calling wait() on semaphore, will block until signalled.\n");
    sem_wait(&sync_sem);   /* wait() - P operation */
    printf("[Thread B] received signal, now executing critical section.\n");
    return NULL;
}

int main() {
    pthread_t t1, t2;

    /* initialize semaphore with value 0 - so wait() blocks initially */
    sem_init(&sync_sem, 0, 0);

    pthread_create(&t2, NULL, thread_B, NULL);
    pthread_create(&t1, NULL, thread_A, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&sync_sem);
    printf("Main: both threads finished.\n");
    return 0;
}
