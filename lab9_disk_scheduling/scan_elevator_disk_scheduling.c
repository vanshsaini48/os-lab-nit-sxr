/*
 * Lab 9 - Question 3
 * SCAN (Elevator) disk scheduling algorithm.
 * The head moves towards one end of the disk, services all requests
 * on the way, reaches the end, and then reverses direction.
 */

#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void scan(int head, int *queue, int n, int disk_size) {
    int seek_count = 0, current_head = head;
    qsort(queue, n, sizeof(int), compare);

    int left[n], right[n];
    int left_count = 0, right_count = 0;

    for (int i = 0; i < n; i++)
        if (queue[i] < head) left[left_count++] = queue[i];
        else right[right_count++] = queue[i];

    printf("Head movement sequence: %d", current_head);

    /* Move right first, towards higher cylinder numbers */
    for (int i = 0; i < right_count; i++) {
        seek_count += abs(right[i] - current_head);
        current_head = right[i];
        printf(" -> %d", current_head);
    }

    /* Go to the end of the disk */
    seek_count += abs(disk_size - 1 - current_head);
    current_head = disk_size - 1;
    printf(" -> %d", current_head);

    /* Reverse direction - service left requests */
    for (int i = left_count - 1; i >= 0; i--) {
        seek_count += abs(left[i] - current_head);
        current_head = left[i];
        printf(" -> %d", current_head);
    }

    printf("\nTotal seek count: %d\n", seek_count);
}

int main() {
    int n, head, disk_size;
    printf("Enter the number of requests: ");
    if (scanf("%d", &n) != 1) return 1;

    int *queue = (int *)malloc(n * sizeof(int));
    if (!queue) { perror("malloc"); return 1; }

    printf("Enter the requests (disk positions):\n");
    for (int i = 0; i < n; i++)
        if (scanf("%d", &queue[i]) != 1) { free(queue); return 1; }

    printf("Enter the current head position: ");
    if (scanf("%d", &head) != 1) { free(queue); return 1; }
    printf("Enter the disk size: ");
    if (scanf("%d", &disk_size) != 1) { free(queue); return 1; }

    printf("\n--- SCAN Disk Scheduling ---\n");
    scan(head, queue, n, disk_size);

    free(queue);
    return 0;
}
