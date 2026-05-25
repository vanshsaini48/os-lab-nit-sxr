/*
 * Lab 3 - Question 2
 * Uses the write() system call and captures its return value.
 * The return value represents the number of bytes actually written.
 */

#include <stdio.h>
#include <unistd.h>

int main() {
    int n;
    n = write(1, "Hello", 5);   /* write "Hello" and capture byte count */
    printf("\nBytes written = %d\n", n);
    return 0;
}
