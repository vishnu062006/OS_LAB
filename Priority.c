#include <stdio.h>

int main()
{
    int n = 4;
    int pid[] = {1,2,3,4};
    int at[] = {0,2,4,5};
    int bt[] = {7,4,1,4};
    int priority[] = {3,1,4,2};

    int ct[4], tat[4], wt[4], rt[4];
    int remaining[4], done[4], firstRun[4];

    int choice;
    printf("Priority Scheduling\n");
    printf("1. Non Preemptive\n");
    printf("2. Preemptive\n");
    printf("Enter choice: ");
    scanf("%d",&choice);

    int time = 0, completed = 0;

    for(int i=0;i<n;i++)
    {
        remaining[i] = bt[i];
        done[i] = 0;
        firstRun[i] = 0;
    }

    switch(choice)
    {
        case 1:
        while(completed < n)
        {
            int idx = -1;
            int minPriority = 9999;

            for(int i=0;i<n;i++)
            {
                if(!done[i] && at[i] <= time)
                {
                    if(priority[i] < minPriority)
                    {
                        minPriority = priority[i];
                        idx = i;
                    }
                    else if(priority[i]==minPriority && at[i]<at[idx])
                        idx = i;
                }
            }

            if(idx == -1)
            {
                time++;
                continue;
            }

            rt[idx] = time - at[idx];
            time += bt[idx];

            ct[idx] = time;
            done[idx] = 1;
            completed++;
        }

        printf("\nPriority Scheduling (Non Preemptive)\n");
        break;

        case 2:
        while(completed < n)
        {
            int idx = -1;
            int minPriority = 9999;

            for(int i=0;i<n;i++)
            {
                if(at[i] <= time && remaining[i] > 0)
                {
                    if(priority[i] < minPriority)
                    {
                        minPriority = priority[i];
                        idx = i;
                    }
                    else if(priority[i]==minPriority && at[i]<at[idx])
                        idx = i;
                }
            }

            if(idx == -1)
            {
                time++;
                continue;
            }

            if(!firstRun[idx])
            {
                rt[idx] = time - at[idx];
                firstRun[idx] = 1;
            }

            remaining[idx]--;
            time++;

            if(remaining[idx] == 0)
            {
                ct[idx] = time;
                completed++;
            }
        }

        printf("\nPriority Scheduling (Preemptive)\n");
        break;

        default:
        printf("Invalid Choice\n");
        return 0;
    }

    float totalTAT=0, totalWT=0, totalRT=0;

    for(int i=0;i<n;i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        totalTAT += tat[i];
        totalWT += wt[i];
        totalRT += rt[i];
    }

    printf("\n%-5s %-5s %-5s %-5s %-5s %-5s %-5s %-5s\n",
           "PID","AT","BT","PRI","CT","TAT","WT","RT");

    for(int i=0;i<n;i++)
        printf("%-5d %-5d %-5d %-5d %-5d %-5d %-5d %-5d\n",
               pid[i],at[i],bt[i],priority[i],ct[i],tat[i],wt[i],rt[i]);

    printf("\nAverage TAT = %.2f", totalTAT/n);
    printf("\nAverage WT = %.2f", totalWT/n);
    printf("\nAverage RT = %.2f\n", totalRT/n);

    return 0;
}