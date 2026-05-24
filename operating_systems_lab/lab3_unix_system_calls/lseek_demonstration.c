/*
 * Lab 3 - Question 5
 * Uses the lseek() system call to reposition the file offset before reading.
 * Opens an existing file, moves the read pointer to a specific byte using
 * lseek(), and then reads and displays the remaining content from that
 * position. Also demonstrates SEEK_END to get the file size.
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int fd;
    char buf[100];
    off_t pos;

    /* First, create a sample file with known content */
    fd = open("sample.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) { perror("open (create)"); return 1; }
    write(fd, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 26);
    close(fd);

    /* Re-open the file for reading */
    fd = open("sample.txt", O_RDONLY);
    if (fd < 0) { perror("open"); return 1; }

    /* Move the offset to byte 10 from the start of the file */
    pos = lseek(fd, 10, SEEK_SET);
    printf("Offset after lseek = %ld\n", (long)pos);

    int n = read(fd, buf, 16);
    if (n < 0) { perror("read"); close(fd); return 1; }
    buf[n] = '\0';
    printf("Read after lseek: %s\n", buf);

    /* Demonstrate SEEK_END - find size of file */
    pos = lseek(fd, 0, SEEK_END);
    printf("File size (via SEEK_END) = %ld bytes\n", (long)pos);

    close(fd);
    return 0;
}
