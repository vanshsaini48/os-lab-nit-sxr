/*
 * Lab 8 - Question 7
 * Last-In-First-Out (LIFO) Page Replacement Algorithm.
 * The most recently loaded page is replaced first when a page fault
 * occurs and all frames are full. Frames behave like a stack - the
 * top (last added) entry is popped on replacement.
 */

#include <stdio.h>

int main() {
    int n, frames, ref[50], fr[10];
    int top = -1, hit = 0, fault = 0;

    printf("Enter number of frames: ");
    if (scanf("%d", &frames) != 1) return 1;
    printf("Enter length of reference string: ");
    if (scanf("%d", &n) != 1) return 1;
    printf("Enter the reference string: ");
    for (int i = 0; i < n; i++)
        if (scanf("%d", &ref[i]) != 1) return 1;

    for (int i = 0; i < frames; i++) fr[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j <= top; j++) {
            if (fr[j] == ref[i]) { found = 1; hit++; break; }
        }

        if (!found) {
            fault++;
            if (top < frames - 1) {
                /* empty slot available - push onto the stack */
                top++;
                fr[top] = ref[i];
            } else {
                /* stack full - replace the top (most recently loaded page) */
                fr[top] = ref[i];
            }
        }

        printf("Step %2d (ref=%d): ", i + 1, ref[i]);
        for (int j = 0; j < frames; j++) {
            if (j > top) printf("- ");
            else printf("%d ", fr[j]);
        }
        printf("  %s\n", found ? "HIT" : "FAULT");
    }

    printf("\nTotal Page Hits   = %d\n", hit);
    printf("Total Page Faults = %d\n", fault);
    printf("Page Fault Rate   = %.2f%%\n", (float)fault * 100 / n);
    return 0;
}
