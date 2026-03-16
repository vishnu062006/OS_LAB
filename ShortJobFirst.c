#include <stdio.h>
int main() {
    int n = 4;
    int pid[] = {1, 2, 3, 4};
    int at[]  = {0, 2, 4, 5};
    int bt[]  = {7, 4, 1, 4};
    int ct[4], tat[4], wt[4], rt[4];
    int done[4];
    for (int i = 0; i < n; i++) done[i] = 0;
    int time = 0, completed = 0;
    while (completed < n) {
        int idx = -1;
        int minBT = 99999;
        for (int i = 0; i < n; i++) {
            if (!done[i] && at[i] <= time) {
                if (bt[i] < minBT) {
                    minBT = bt[i];
                    idx = i;
                }
                else if (bt[i] == minBT && at[i] < at[idx]) {
                    idx = i;
                }
            }
        }
        if (idx == -1) {
            time++;
            continue;
        }
        rt[idx]  = time - at[idx];   
        time    += bt[idx];          
        ct[idx]  = time;             
        done[idx] = 1;
        completed++;
    }
    float totalTAT = 0, totalWT = 0, totalRT = 0;
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i]  = tat[i] - bt[i];
        totalTAT += tat[i];
        totalWT  += wt[i];
        totalRT  += rt[i];
    }
    printf("%-5s %-5s %-5s %-5s %-5s %-5s %-5s\n", "PID", "AT", "BT", "CT", "TAT", "WT", "RT");
    for (int i = 0; i < n; i++)
        printf("%-5d %-5d %-5d %-5d %-5d %-5d %-5d\n",
               pid[i], at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    printf("\nAverage TAT = %.2f", totalTAT / n);
    printf("\nAverage WT  = %.2f", totalWT / n);
    printf("\nAverage RT  = %.2f\n", totalRT / n);

    return 0;
}
