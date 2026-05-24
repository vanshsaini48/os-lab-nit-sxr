/*
 * Lab 5 - Question 2
 * Creates a single thread using pthread_create(). The thread prints
 * a counter five times, while the main program continues to execute
 * after the thread completes (via pthread_join()).
 */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int i, j;

void *thread_function(void *args) {
    (void)args;
    for (i = 0; i < 5; i++) {
        printf("Thread running: %d\n", i);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t a_thread;
    pthread_create(&a_thread, NULL, thread_function, NULL);
    pthread_join(a_thread, NULL);

    printf("Inside main program\n");
    for (j = 20; j < 25; j++) {
        printf("%d\n", j);
        sleep(1);
    }
    return 0;
}
