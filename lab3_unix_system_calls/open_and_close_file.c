/*
 * Lab 3 - Question 4
 * Uses the open() and close() system calls to create/open a file,
 * write a few bytes into it using write(), and then close the file
 * descriptor.
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    int fd;
    char *msg = "Operating Systems Lab - open() and close() demo.\n";

    /* O_CREAT creates the file if it doesn't exist; 0644 sets permissions */
    fd = open("demo.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open failed");
        return 1;
    }
    printf("File opened successfully. fd = %d\n", fd);

    write(fd, msg, strlen(msg));
    printf("Bytes written to file.\n");

    if (close(fd) == 0)
        printf("File closed successfully.\n");
    else
        perror("close failed");

    return 0;
}
