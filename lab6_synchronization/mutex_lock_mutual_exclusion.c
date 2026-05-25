/*
 * Lab 6 - Question 1
 * Implements mutual exclusion on a shared variable using POSIX mutex
 * locks (pthread_mutex_t). Two threads attempt to update the shared
 * variable; the mutex guarantees that only one thread executes its
 * critical section at a time.
 */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int shared = 1;
pthread_mutex_t l;

void *fun1(void *arg);
void *fun2(void *arg);

int main() {
    pthread_mutex_init(&l, NULL);

    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, fun1, NULL);
    pthread_create(&thread2, NULL, fun2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Final value of shared = %d\n", shared);

    pthread_mutex_destroy(&l);
    return 0;
}

void *fun1(void *arg) {
    (void)arg;
    int x;
    printf("Thread1 trying to acquire lock\n");
    pthread_mutex_lock(&l);
    printf("Thread1 acquired lock\n");
    x = shared;
    printf("Thread1 read value of shared variable as %d\n", x);
    x++;
    printf("Local updation by thread1: %d\n", x);
    sleep(1);
    shared = x;
    printf("Value of shared variable updated by thread1 is %d\n", shared);
    pthread_mutex_unlock(&l);
    printf("Thread1 released the lock\n");
    return NULL;
}

void *fun2(void *arg) {
    (void)arg;
    int y;
    printf("Thread2 trying to acquire lock\n");
    pthread_mutex_lock(&l);
    printf("Thread2 acquired lock\n");
    y = shared;
    printf("Thread2 read value of shared variable as %d\n", y);
    y++;
    printf("Local updation by thread2: %d\n", y);
    sleep(1);
    shared = y;
    printf("Value of shared variable updated by thread2 is %d\n", shared);
    pthread_mutex_unlock(&l);
    printf("Thread2 released the lock\n");
    return NULL;
}
