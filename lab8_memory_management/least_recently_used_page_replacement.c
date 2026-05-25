/*
 * Lab 8 - Question 3
 * Least Recently Used (LRU) page replacement algorithm.
 * The page that has not been used for the longest period of time
 * is the victim when a replacement is needed.
 */

#include <stdio.h>
#define MAX 100

int main() {
    int frames, pages, pageFaults = 0, pageHits = 0;
    int pageSequence[MAX], frameArray[MAX], recentlyUsed[MAX];

    printf("Enter number of frames: ");
    if (scanf("%d", &frames) != 1) return 1;
    printf("Enter number of pages: ");
    if (scanf("%d", &pages) != 1) return 1;
    printf("Enter page sequence: ");
    for (int i = 0; i < pages; i++)
        if (scanf("%d", &pageSequence[i]) != 1) return 1;

    for (int i = 0; i < frames; i++) {
        frameArray[i] = -1;
        recentlyUsed[i] = -1;
    }

    printf("\nLRU Page Replacement:\n");
    printf("Page\tFrames\t\t\tStatus\n");
    printf("-----------------------------------------\n");

    int frameCount = 0;
    for (int i = 0; i < pages; i++) {
        int page = pageSequence[i], found = -1;

        for (int j = 0; j < frames; j++)
            if (frameArray[j] == page) {
                found = j;
                pageHits++;
                recentlyUsed[j] = i;
                break;
            }

        if (found == -1) {
            pageFaults++;
            if (frameCount < frames) {
                frameArray[frameCount] = page;
                recentlyUsed[frameCount] = i;
                frameCount++;
            } else {
                int minTime = recentlyUsed[0], minIndex = 0;
                for (int j = 1; j < frames; j++)
                    if (recentlyUsed[j] < minTime) {
                        minTime = recentlyUsed[j];
                        minIndex = j;
                    }
                frameArray[minIndex] = page;
                recentlyUsed[minIndex] = i;
            }
        }

        printf("%d\t", page);
        for (int j = 0; j < frames; j++)
            if (frameArray[j] != -1) printf("%d ", frameArray[j]);
            else printf("- ");
        printf("\t%s\n", found != -1 ? "HIT" : "MISS");
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
    printf("Total Page Hits  : %d\n", pageHits);
    printf("Page Fault Rate  : %.2f%%\n", (pageFaults * 100.0) / pages);
    return 0;
}
