/*
 * Lab 5 - Question 3
 * Two threads read, modify, and write back the same shared global
 * variable. Observes the race condition that occurs when multiple
 * threads access the shared variable without synchronization.
 */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *fun1(void *arg);
void *fun2(void *arg);

int shared = 1;   /* shared variable */

int main() {
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, fun1, NULL);
    pthread_create(&thread2, NULL, fun2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("\nFinal value of shared = %d\n", shared);
    return 0;
}

void *fun1(void *arg) {
    (void)arg;
    int x;
    x = shared;
    printf("T1 read = %d\n", x);
    x++;
    printf("T1 local = %d\n", x);
    sleep(1);   /* pre-empt to thread 2 */
    shared = x;
    printf("T1 wrote shared = %d\n", shared);
    return NULL;
}

void *fun2(void *arg) {
    (void)arg;
    int y;
    y = shared;
    printf("T2 read = %d\n", y);
    sleep(1);
    shared = y;
    printf("T2 wrote shared = %d\n", shared);
    return NULL;
}
