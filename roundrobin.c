#include <stdio.h>

struct Process {
    int pid, at, bt, rt, ct, tat, wt, iQ;
};

int main() {
    int n = 4;
    int tq = 3;

    struct Process p[4] = {{1,0,7},{2,2,4},{3,4,1},{4,5,4}};

    int queue[100], f = 0, r = 0;
    int t = 0, completed = 0;

    // Initialize remaining time and inQueue flag
    for (int i = 0; i < n; i++) {
        p[i].rt = p[i].bt;
        p[i].iQ = 0;
    }

    // Add processes that arrive at t=0
    for (int i = 0; i < n; i++) {
        if (p[i].at <= t) {
            queue[r++] = i;
            p[i].iQ = 1;
        }
    }

    printf("\nGantt Chart:\n%d ", t);

    while (completed < n) {

        if (f == r) {  // CPU idle
            t++;
            for (int i = 0; i < n; i++) {
                if (!p[i].iQ && p[i].rt > 0 && p[i].at <= t) {
                    queue[r++] = i;
                    p[i].iQ = 1;
                }
            }
            continue;
        }

        printf("\nReady Queue: ");
        for (int i = f; i < r; i++) {
            printf("P%d ", p[queue[i]].pid);
        }

        int idx = queue[f++];

        if (p[idx].rt > tq) {
            printf("| P%d ", p[idx].pid);
            t += tq;
            p[idx].rt -= tq;

            for (int i = 0; i < n; i++) {
                if (!p[i].iQ && p[i].rt > 0 && p[i].at <= t) {
                    queue[r++] = i;
                    p[i].iQ = 1;
                }
            }
            queue[r++] = idx;
            printf("%d ", t);
        } else {
            printf("| P%d ", p[idx].pid);
            t += p[idx].rt;
            p[idx].rt = 0;
            p[idx].ct = t;
            completed++;

            for (int i = 0; i < n; i++) {
                if (!p[i].iQ && p[i].rt > 0 && p[i].at <= t) {
                    queue[r++] = i;
                    p[i].iQ = 1;
                }
            }
            printf("%d ", t);
        }
    }

    // Calculate TAT and WT
    float totalTAT = 0, totalWT = 0;
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        totalTAT += p[i].tat;
        totalWT += p[i].wt;
    }

    // Print process table
    printf("\n\nProcess Table:\n");
    printf("%-5s %-5s %-5s %-5s %-5s %-5s\n","PID","AT","BT","CT","TAT","WT");
    printf("--------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-5d %-5d %-5d %-5d %-5d %-5d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage TAT = %.2f", totalTAT / n);
    printf("\nAverage WT  = %.2f\n", totalWT / n);

    return 0;
}
