/*
 * Lab 7 - Question 4
 * Round Robin CPU scheduling with arrival time. Each process is
 * allocated the CPU for a fixed time quantum in a circular order
 * based on its arrival time.
 */

#include <stdio.h>
#define MAX 30

struct Process {
    int pid, arrival, burst, remaining, completion, wt, tat;
};

int main() {
    int i, n, completed = 0, tq, time = 0;
    float awt = 0, atat = 0;
    struct Process proc[MAX];

    printf("Enter the number of processes: ");
    if (scanf("%d", &n) != 1) return 1;
    printf("Enter time quantum: ");
    if (scanf("%d", &tq) != 1) return 1;

    for (i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time of process %d: ", i + 1);
        if (scanf("%d", &proc[i].arrival) != 1) return 1;
        printf("Enter burst time of process %d: ", i + 1);
        if (scanf("%d", &proc[i].burst) != 1) return 1;
        proc[i].remaining = proc[i].burst;
        proc[i].completion = 0;
    }

    printf("\nProcess\tArrival\tBurst\tWaiting\tTAT\n");

    while (completed < n) {
        int executed = 0;
        for (i = 0; i < n; i++) {
            if (proc[i].remaining > 0 && proc[i].arrival <= time) {
                executed = 1;
                if (proc[i].remaining <= tq) {
                    time += proc[i].remaining;
                    proc[i].completion = time;
                    proc[i].tat = proc[i].completion - proc[i].arrival;
                    proc[i].wt = proc[i].tat - proc[i].burst;
                    proc[i].remaining = 0;
                    completed++;
                    printf("%d\t%d\t%d\t%d\t%d\n",
                           proc[i].pid, proc[i].arrival, proc[i].burst,
                           proc[i].wt, proc[i].tat);
                } else {
                    time += tq;
                    proc[i].remaining -= tq;
                }
            }
        }
        if (executed == 0) {
            int minArrival = 999999;
            for (i = 0; i < n; i++)
                if (proc[i].remaining > 0 && proc[i].arrival > time &&
                    proc[i].arrival < minArrival)
                    minArrival = proc[i].arrival;
            if (minArrival != 999999) time = minArrival;
        }
    }

    for (i = 0; i < n; i++) {
        awt += proc[i].wt;
        atat += proc[i].tat;
    }
    printf("\nAverage Waiting Time    = %.2f\n", awt / n);
    printf("Average Turnaround Time = %.2f\n", atat / n);
    return 0;
}
