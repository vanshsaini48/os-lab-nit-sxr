/*
 * Lab 4 - Question 1
 * Creates a child process using the fork() system call. Prints the
 * PID of the parent and child, demonstrates the difference between
 * them, and uses wait() so that the parent waits for the child to complete.
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t q;
    q = fork();
    wait(NULL);

    if (q < 0) {
        printf("NO PROCESS IS CREATED\n");
    }
    else if (q == 0) {
        printf("CHILD CREATED SUCCESSFULLY\n");
        printf("Child PID  : %d\n", getpid());
        printf("Parent PID : %d\n", getppid());
    }
    else {
        printf("Parent PID         : %d\n", getpid());
        printf("Returned child PID : %d\n", q);
    }
    printf("ABC\n");
    return 0;
}
