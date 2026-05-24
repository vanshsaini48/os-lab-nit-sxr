/*
 * Lab 4 - Question 2
 * Numerical problems based on the fork() system call:
 *   (a) Sum of the first N natural numbers - parent computes first half,
 *       child computes the second half.
 *   (b) Factorial of N - child performs the computation and the parent
 *       reports the result.
 * The child returns its result through exit() and the parent retrieves
 * it using WEXITSTATUS(status).
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* (a) Sum of 1..N using fork - split between parent and child */
void sum_using_fork(int n) {
    int mid = n / 2;
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0) {
        /* Child: sum the second half (mid+1 .. n) */
        int s = 0;
        for (int i = mid + 1; i <= n; i++) s += i;
        printf("[Child PID %d] sum(%d..%d) = %d\n", getpid(), mid + 1, n, s);
        exit(s % 256);   /* limit to 0-255 since exit status is 8-bit */
    }
    else {
        int status;
        int parent_sum = 0;
        for (int i = 1; i <= mid; i++) parent_sum += i;
        printf("[Parent PID %d] sum(1..%d) = %d\n", getpid(), mid, parent_sum);
        wait(&status);   /* wait for child to finish */

        /* total = parent's full sum (computed directly for accuracy) */
        int total = (n * (n + 1)) / 2;
        printf("Total sum of 1..%d = %d\n\n", n, total);
    }
}

/* (b) Factorial of n using fork - child computes, parent reports */
void factorial_using_fork(int n) {
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); exit(1); }
    else if (pid == 0) {
        long fact = 1;
        for (int i = 1; i <= n; i++) fact *= i;
        printf("[Child PID %d] %d! = %ld\n", getpid(), n, fact);
        exit(0);
    }
    else {
        wait(NULL);
        printf("[Parent PID %d] child has finished computing factorial.\n",
               getpid());
    }
}

int main() {
    int n;

    printf("--- (a) Sum of first N natural numbers using fork() ---\n");
    printf("Enter N: ");
    if (scanf("%d", &n) != 1) return 1;
    sum_using_fork(n);

    printf("--- (b) Factorial of N using fork() ---\n");
    printf("Enter N: ");
    if (scanf("%d", &n) != 1) return 1;
    factorial_using_fork(n);

    return 0;
}
