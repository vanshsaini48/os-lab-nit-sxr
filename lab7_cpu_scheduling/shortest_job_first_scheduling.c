/*
 * Lab 7 - Question 2
 * Shortest-Job-First (non-preemptive) CPU scheduling with arrival time.
 * Among processes available at the current time, the one with the
 * smallest burst time is selected.
 */

#include <stdio.h>
#define MAX 30

struct Process {
    int pid, arrival, burst, wt, tat, completed;
};

int main() {
    int i, n, completed = 0;
    float awt = 0, atat = 0;
    struct Process proc[MAX];

    printf("Enter the number of processes: ");
    if (scanf("%d", &n) != 1) return 1;

    for (i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        proc[i].completed = 0;
        printf("Enter arrival time of process %d: ", i + 1);
        if (scanf("%d", &proc[i].arrival) != 1) return 1;
        printf("Enter burst time of process %d: ", i + 1);
        if (scanf("%d", &proc[i].burst) != 1) return 1;
    }

    int time = 0;
    printf("\nProcess\tArrival\tBurst\tWaiting\tTAT\n");

    while (completed < n) {
        int minBurst = 999, minIdx = -1;
        for (i = 0; i < n; i++)
            if (proc[i].completed == 0 &&
                proc[i].arrival <= time &&
                proc[i].burst < minBurst) {
                minBurst = proc[i].burst;
                minIdx = i;
            }

        if (minIdx == -1) {
            /* No process available - advance time to next arrival */
            int nextArrival = 999999;
            for (i = 0; i < n; i++)
                if (proc[i].completed == 0 && proc[i].arrival > time &&
                    proc[i].arrival < nextArrival)
                    nextArrival = proc[i].arrival;
            if (nextArrival != 999999) time = nextArrival;
            continue;
        }

        time += proc[minIdx].burst;
        proc[minIdx].tat = time - proc[minIdx].arrival;
        proc[minIdx].wt = proc[minIdx].tat - proc[minIdx].burst;
        proc[minIdx].completed = 1;
        completed++;

        printf("%d\t%d\t%d\t%d\t%d\n",
               proc[minIdx].pid, proc[minIdx].arrival, proc[minIdx].burst,
               proc[minIdx].wt, proc[minIdx].tat);
    }

    for (i = 0; i < n; i++) {
        awt += proc[i].wt;
        atat += proc[i].tat;
    }
    printf("\nAverage Waiting Time    = %.2f\n", awt / n);
    printf("Average Turnaround Time = %.2f\n", atat / n);
    return 0;
}
