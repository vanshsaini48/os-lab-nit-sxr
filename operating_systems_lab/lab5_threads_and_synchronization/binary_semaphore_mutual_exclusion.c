/*
 * Lab 5 - Question 4
 * Uses a binary semaphore (sem_t) to enforce mutual exclusion while
 * updating a shared variable. Eliminates the race condition shown
 * in the previous program.
 */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>

void *fun1(void *arg);
void *fun2(void *arg);

int shared = 1;
sem_t s;

int main() {
    sem_init(&s, 0, 1);   /* binary semaphore */

    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, fun1, NULL);
    pthread_create(&thread2, NULL, fun2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("\nFinal value of shared = %d\n", shared);

    sem_destroy(&s);
    return 0;
}

void *fun1(void *arg) {
    (void)arg;
    int x;
    sem_wait(&s);
    x = shared;
    printf("T1 read = %d\n", x);
    x++;
    printf("T1 local = %d\n", x);
    sleep(1);
    shared = x;
    printf("T1 wrote shared = %d\n", shared);
    sem_post(&s);
    return NULL;
}

void *fun2(void *arg) {
    (void)arg;
    int y;
    sem_wait(&s);
    y = shared;
    printf("T2 read = %d\n", y);
    y++;
    sleep(1);
    shared = y;
    printf("T2 wrote shared = %d\n", shared);
    sem_post(&s);
    return NULL;
}
