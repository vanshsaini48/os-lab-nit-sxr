/*
 * Lab 9 - Question 2
 * Shortest Seek Time First (SSTF) disk scheduling algorithm.
 * The request closest (in terms of cylinder number) to the current
 * head position is serviced next.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void sstf(int head, int *queue, int n) {
    int seek_count = 0, current_head = head;
    int *visited = (int *)calloc(n, sizeof(int));
    if (!visited) { perror("calloc"); return; }

    printf("Head movement sequence: %d", current_head);

    for (int i = 0; i < n; i++) {
        int min_distance = INT_MAX, min_index = -1;
        for (int j = 0; j < n; j++)
            if (!visited[j]) {
                int distance = abs(queue[j] - current_head);
                if (distance < min_distance) {
                    min_distance = distance;
                    min_index = j;
                }
            }
        visited[min_index] = 1;
        seek_count += min_distance;
        current_head = queue[min_index];
        printf(" -> %d", current_head);
    }

    printf("\nTotal seek count: %d\n", seek_count);
    free(visited);
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

    printf("\n--- SSTF Disk Scheduling ---\n");
    sstf(head, queue, n);

    free(queue);
    return 0;
}
