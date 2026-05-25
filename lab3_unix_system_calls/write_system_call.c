/*
 * Lab 3 - Question 1
 * Demonstrates the write() system call with different byte counts.
 * Observes how write() interprets the count parameter.
 *
 * Note: Asking write() to write more bytes than the string holds is
 * intentional here to illustrate that write() trusts the byte count
 * provided. The compiler's static analysis warning is suppressed
 * because this over-read behaviour IS the point of the exercise.
 */

#include <unistd.h>
#include <string.h>

int main() {
    /* Build the buffer at runtime so the compiler cannot statically
     * deduce its exact size for the literal arguments. */
    char msg[16];
    memset(msg, 0, sizeof(msg));
    memcpy(msg, "Hello", 5);

    write(1, msg, 5);    /* writes exactly 5 bytes -> "Hello" */
    write(1, msg, 10);   /* tries to write 10 bytes -> may show garbage */
    write(1, msg, 2);    /* writes only the first 2 bytes -> "He" */
    write(1, "\n", 1);   /* newline for clean output */
    return 0;
}
