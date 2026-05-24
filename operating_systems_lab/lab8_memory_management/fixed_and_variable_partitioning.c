/*
 * Lab 8 - Question 1
 * Simulates both Fixed Partitioning and Variable Partitioning
 * (using the First-Fit strategy) of memory. The user chooses the
 * strategy, enters partition / process sizes, and the final memory
 * layout along with utilization statistics is displayed.
 */

#include <stdio.h>
#define MAX 100

int main() {
    int totalMemory, choice;

    printf("===== Memory Partitioning =====\n");
    printf("1. Fixed Partitioning\n");
    printf("2. Variable Partitioning\n");
    printf("Enter your choice: ");
    if (scanf("%d", &choice) != 1) return 1;

    if (choice == 1) {
        printf("\n===== Fixed Partitioning =====\n");
        printf("Enter total memory size: ");
        if (scanf("%d", &totalMemory) != 1) return 1;

        int numPartitions;
        printf("Enter number of partitions: ");
        if (scanf("%d", &numPartitions) != 1) return 1;

        int partitionSize[MAX], allocated[MAX], process[MAX];
        for (int i = 0; i < numPartitions; i++) {
            printf("Enter size of partition %d: ", i + 1);
            if (scanf("%d", &partitionSize[i]) != 1) return 1;
            allocated[i] = 0;
            process[i] = -1;
        }

        int numProcesses;
        printf("Enter number of processes: ");
        if (scanf("%d", &numProcesses) != 1) return 1;

        printf("\nProcess\tSize\tAllocated to Partition\n");
        printf("----------------------------------------\n");
        for (int i = 0; i < numProcesses; i++) {
            int size;
            printf("Enter size of process %d: ", i + 1);
            if (scanf("%d", &size) != 1) return 1;

            int allocated_to = -1;
            for (int j = 0; j < numPartitions; j++)
                if (partitionSize[j] >= size && !allocated[j]) {
                    allocated[j] = 1;
                    process[j] = i + 1;
                    allocated_to = j + 1;
                    break;
                }
            if (allocated_to != -1)
                printf("%d\t%d\tPartition %d (Size: %d)\n",
                       i + 1, size, allocated_to,
                       partitionSize[allocated_to - 1]);
            else
                printf("%d\t%d\tNOT ALLOCATED\n", i + 1, size);
        }

        printf("\nPartition Status:\n");
        printf("Partition\tSize\tAllocated\tProcess\tWasted\n");
        printf("---------------------------------------------------\n");
        for (int i = 0; i < numPartitions; i++) {
            if (allocated[i])
                printf("%d\t\t%d\tYes\t\tP%d\t-\n",
                       i + 1, partitionSize[i], process[i]);
            else
                printf("%d\t\t%d\tNo\t\t-\t%d\n",
                       i + 1, partitionSize[i], partitionSize[i]);
        }
    }
    else if (choice == 2) {
        printf("\n===== Variable Partitioning (First-Fit) =====\n");
        printf("Enter total memory size: ");
        if (scanf("%d", &totalMemory) != 1) return 1;

        int startAddr[MAX];
        int numAllocations = 0, usedMemory = 0;

        int numProcesses;
        printf("Enter number of processes: ");
        if (scanf("%d", &numProcesses) != 1) return 1;

        printf("\nProcess\tSize\tStart\tEnd\tStatus\n");
        printf("------------------------------------------\n");

        for (int i = 0; i < numProcesses; i++) {
            int psize;
            printf("Enter size of process %d: ", i + 1);
            if (scanf("%d", &psize) != 1) return 1;

            if (usedMemory + psize <= totalMemory) {
                startAddr[numAllocations] = usedMemory;
                usedMemory += psize;
                printf("%d\t%d\t%d\t%d\tALLOCATED\n",
                       i + 1, psize, startAddr[numAllocations],
                       startAddr[numAllocations] + psize - 1);
                numAllocations++;
            } else {
                printf("%d\t%d\t-\t-\tNOT ALLOCATED\n", i + 1, psize);
            }
        }

        printf("\nMemory Statistics:\n");
        printf("Total Memory : %d\n", totalMemory);
        printf("Used Memory  : %d\n", usedMemory);
        printf("Free Memory  : %d\n", totalMemory - usedMemory);
        printf("Utilization  : %.2f%%\n",
               (usedMemory * 100.0) / totalMemory);
    }
    else printf("Invalid choice!\n");

    return 0;
}
