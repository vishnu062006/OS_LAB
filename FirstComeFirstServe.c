#include <stdio.h>
int main() {
    int n = 4;
    int pid[] = {1, 2, 3, 4};
    int at[]  = {0, 2, 4, 5};
    int bt[]  = {7, 4, 1, 4};
    int ct[4], tat[4], wt[4], rt[4];
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1]) {
                int tmp;
                tmp = at[j];  at[j] = at[j+1];  at[j+1] = tmp;
                tmp = bt[j];  bt[j] = bt[j+1];  bt[j+1] = tmp;
                tmp = pid[j]; pid[j] = pid[j+1]; pid[j+1] = tmp;
            }
        }
    }
    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < at[i])
            time = at[i];
        rt[i] = time - at[i];   
        time += bt[i];
        ct[i] = time;
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
        printf("%-5d %-5d %-5d %-5d %-5d %-5d %-5d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    printf("\nAverage TAT = %.2f", totalTAT / n);
    printf("\nAverage WT  = %.2f", totalWT / n);
    printf("\nAverage RT  = %.2f\n", totalRT / n);
    return 0;
}
