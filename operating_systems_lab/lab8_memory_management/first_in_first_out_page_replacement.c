/*
 * Lab 8 - Question 2
 * First-In-First-Out (FIFO) page replacement algorithm.
 * Accepts the number of frames, the reference string, and displays
 * the frame status, page hits, page faults, and the page fault rate.
 */

#include <stdio.h>
#define MAX 100

int main() {
    int frames, pages, pageFaults = 0, pageHits = 0;
    int pageSequence[MAX], frameArray[MAX];

    printf("Enter number of frames: ");
    if (scanf("%d", &frames) != 1) return 1;
    printf("Enter number of pages: ");
    if (scanf("%d", &pages) != 1) return 1;
    printf("Enter page sequence: ");
    for (int i = 0; i < pages; i++)
        if (scanf("%d", &pageSequence[i]) != 1) return 1;

    for (int i = 0; i < frames; i++) frameArray[i] = -1;

    printf("\nFIFO Page Replacement:\n");
    printf("Page\tFrames\t\t\tStatus\n");
    printf("-----------------------------------------\n");

    int nextSlot = 0;
    for (int i = 0; i < pages; i++) {
        int page = pageSequence[i], found = 0;
        for (int j = 0; j < frames; j++)
            if (frameArray[j] == page) { found = 1; pageHits++; break; }

        if (!found) {
            pageFaults++;
            frameArray[nextSlot] = page;
            nextSlot = (nextSlot + 1) % frames;
        }

        printf("%d\t", page);
        for (int j = 0; j < frames; j++)
            if (frameArray[j] != -1) printf("%d ", frameArray[j]);
            else printf("- ");
        printf("\t%s\n", found ? "HIT" : "MISS");
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
    printf("Total Page Hits  : %d\n", pageHits);
    printf("Page Fault Rate  : %.2f%%\n", (pageFaults * 100.0) / pages);
    return 0;
}
