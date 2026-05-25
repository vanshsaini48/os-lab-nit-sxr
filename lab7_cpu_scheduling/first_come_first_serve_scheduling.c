/*
 * Lab 7 - Question 1
 * First-Come-First-Serve (FCFS) CPU scheduling algorithm with distinct
 * arrival times. Processes are ordered by arrival time and CPU idle
 * time is handled correctly.
 */

#include <stdio.h>
#define MAX 30

struct Process {
    int pid, arrival, burst, wt, tat;
};

int main() {
    int i, j, n;
    float awt = 0, atat = 0;
    struct Process proc[MAX], temp;

    printf("Enter the number of processes: ");
    if (scanf("%d", &n) != 1) return 1;

    for (i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time of process %d: ", i + 1);
        if (scanf("%d", &proc[i].arrival) != 1) return 1;
        printf("Enter burst time of process %d: ", i + 1);
        if (scanf("%d", &proc[i].burst) != 1) return 1;
    }

    /* Sort processes by arrival time (bubble sort) */
    for (i = 0; i < n; i++)
        for (j = i + 1; j < n; j++)
            if (proc[i].arrival > proc[j].arrival) {
                temp = proc[i]; proc[i] = proc[j]; proc[j] = temp;
            }

    int completion = 0;
    for (i = 0; i < n; i++) {
        if (completion < proc[i].arrival)
            completion = proc[i].arrival;   /* CPU idle - advance to next arrival */
        completion += proc[i].burst;
        proc[i].tat = completion - proc[i].arrival;
        proc[i].wt = proc[i].tat - proc[i].burst;
    }

    printf("\nProcess\tArrival\tBurst\tWaiting\tTAT\n");
    for (i = 0; i < n; i++) {
        awt += proc[i].wt;
        atat += proc[i].tat;
        printf("%d\t%d\t%d\t%d\t%d\n",
               proc[i].pid, proc[i].arrival, proc[i].burst,
               proc[i].wt, proc[i].tat);
    }

    printf("\nAverage Waiting Time    = %.2f\n", awt / n);
    printf("Average Turnaround Time = %.2f\n", atat / n);
    return 0;
}
