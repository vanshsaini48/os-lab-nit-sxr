/*
 * Lab 8 - Question 4
 * Optimal Page Replacement Algorithm.
 * On a page fault when all frames are occupied, the page that will
 * not be used for the longest period of time in the future is
 * replaced. Optimal is used as the lower bound for comparison with
 * other algorithms since it requires perfect knowledge of the future
 * reference string.
 */

#include <stdio.h>

int main() {
    int n, frames, ref[50], fr[10];
    int hit = 0, fault = 0;

    printf("Enter number of frames: ");
    if (scanf("%d", &frames) != 1) return 1;
    printf("Enter length of reference string: ");
    if (scanf("%d", &n) != 1) return 1;
    printf("Enter the reference string: ");
    for (int i = 0; i < n; i++)
        if (scanf("%d", &ref[i]) != 1) return 1;

    for (int i = 0; i < frames; i++) fr[i] = -1;   /* empty frames */

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++)
            if (fr[j] == ref[i]) { found = 1; hit++; break; }

        if (!found) {
            fault++;
            int empty = -1;
            for (int j = 0; j < frames; j++)
                if (fr[j] == -1) { empty = j; break; }

            if (empty != -1) {
                fr[empty] = ref[i];
            } else {
                /* Find the page used farthest in the future */
                int farthest = -1, replace_idx = 0;
                for (int j = 0; j < frames; j++) {
                    int k;
                    for (k = i + 1; k < n; k++)
                        if (fr[j] == ref[k]) break;
                    if (k > farthest) {
                        farthest = k;
                        replace_idx = j;
                    }
                }
                fr[replace_idx] = ref[i];
            }
        }

        printf("Step %2d (ref=%d): ", i + 1, ref[i]);
        for (int j = 0; j < frames; j++) {
            if (fr[j] == -1) printf("- ");
            else printf("%d ", fr[j]);
        }
        printf("  %s\n", found ? "HIT" : "FAULT");
    }

    printf("\nTotal Page Hits   = %d\n", hit);
    printf("Total Page Faults = %d\n", fault);
    printf("Page Fault Rate   = %.2f%%\n", (float)fault * 100 / n);
    return 0;
}
