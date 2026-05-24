/*
 * Lab 9 - Question 6
 * Circular LOOK (C-LOOK) disk scheduling algorithm.
 * Similar to C-SCAN, but instead of going to the end of the disk,
 * the head only goes as far as the last request in the current
 * direction, then jumps directly to the lowest request and continues.
 */

#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void clook(int head, int *queue, int n) {
    int seek_count = 0, current_head = head;
    qsort(queue, n, sizeof(int), compare);

    int left[n], right[n];
    int left_count = 0, right_count = 0;

    for (int i = 0; i < n; i++)
        if (queue[i] < head) left[left_count++] = queue[i];
        else right[right_count++] = queue[i];

    printf("Head movement sequence: %d", current_head);

    for (int i = 0; i < right_count; i++) {
        seek_count += abs(right[i] - current_head);
        current_head = right[i];
        printf(" -> %d", current_head);
    }

    if (left_count > 0) {
        /* Jump to lowest request */
        seek_count += abs(left[0] - current_head);
        current_head = left[0];
        printf(" -> %d", current_head);

        for (int i = 1; i < left_count; i++) {
            seek_count += abs(left[i] - current_head);
            current_head = left[i];
            printf(" -> %d", current_head);
        }
    }

    printf("\nTotal seek count: %d\n", seek_count);
}

int main() {
    int n, head;
    printf("Enter the number of requests: ");
    if (scanf("%d", &n) != 1) return 1;

    int *queue = (int *)malloc(n * sizeof(int));
    if (!queue) { perror("malloc"); return 1; }

    printf("Enter the requests (disk positions):\n");
    for (int i = 0; i < n; i++)
        if (scanf("%d", &queue[i]) != 1) { free(queue); return 1; }

    printf("Enter the current head position: ");
    if (scanf("%d", &head) != 1) { free(queue); return 1; }

    printf("\n--- C-LOOK Disk Scheduling ---\n");
    clook(head, queue, n);

    free(queue);
    return 0;
}
