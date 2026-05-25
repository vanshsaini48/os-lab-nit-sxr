/*
 * Lab 6 - Question 2
 * Implements Peterson's algorithm for two-process mutual exclusion.
 * Uses a turn flag and an array flag[2] to ensure that only one
 * process enters its critical section at a time and to avoid starvation.
 */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int turn;
int flag[2] = {0, 0};
int shared = 0;

void *process0(void *arg) {
    (void)arg;
    for (int i = 0; i < 5; i++) {
        flag[0] = 1;                       /* P0 wants to enter */
        turn = 1;                          /* give priority to P1 */
        while (flag[1] && turn == 1);      /* busy wait */

        /* ---- Critical Section ---- */
        shared++;
        printf("Thread0 in CS, shared = %d\n", shared);
        /* -------------------------- */

        flag[0] = 0;                       /* leave CS */
        sleep(1);
    }
    return NULL;
}

void *process1(void *arg) {
    (void)arg;
    for (int i = 0; i < 5; i++) {
        flag[1] = 1;
        turn = 0;
        while (flag[0] && turn == 0);

        /* ---- Critical Section ---- */
        shared++;
        printf("Thread1 in CS, shared = %d\n", shared);
        /* -------------------------- */

        flag[1] = 0;
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t t0, t1;
    pthread_create(&t0, NULL, process0, NULL);
    pthread_create(&t1, NULL, process1, NULL);

    pthread_join(t0, NULL);
    pthread_join(t1, NULL);

    printf("Final value of shared = %d\n", shared);
    return 0;
}
