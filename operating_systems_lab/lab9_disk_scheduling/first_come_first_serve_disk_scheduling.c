/*
 * Lab 9 - Question 1
 * First-Come-First-Serve (FCFS) disk scheduling algorithm.
 * The disk head services the requests in the exact order they
 * arrive in the queue. Computes and displays the total seek count
 * and head movement sequence.
 */

#include <stdio.h>
#include <stdlib.h>

void fcfs(int head, int *queue, int n) {
    int seek_count = 0;
    int current_head = head;

    printf("Head movement sequence: %d", current_head);
    for (int i = 0; i < n; i++) {
        seek_count += abs(queue[i] - current_head);
        printf(" -> %d", queue[i]);
        current_head = queue[i];
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

    printf("\n--- FCFS Disk Scheduling ---\n");
    fcfs(head, queue, n);

    free(queue);
    return 0;
}
