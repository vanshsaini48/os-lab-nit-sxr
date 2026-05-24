/*
 * Lab 3 - Question 3
 * Uses the read() system call to read input from the keyboard (stdin)
 * into a buffer and echoes it back to the screen using write().
 */

#include <unistd.h>

int main() {
    char b[30];
    int n;
    n = read(0, b, 30);   /* read up to 30 bytes from stdin */
    write(1, b, n);       /* write the same bytes to stdout */
    return 0;
}
