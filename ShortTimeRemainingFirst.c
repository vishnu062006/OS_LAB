#include <stdio.h>
int main(){
    int n=4;
    int pid[]={1,2,3,4};
    int at[]={0,2,4,5};
    int bt[]={7,4,1,4};
    int ct[4],tat[4],wt[4],rt[4];
    int remaining[4],firstRun[4];
    for(int i=0;i<n;i++){
        remaining[i]=bt[i];
        firstRun[i]=0;
    }
    int time=0,completed=0;
    while(completed<n){
        int idx=-1;
        int minRT=9999;
        for(int i=0;i<n;i++){
            if(at[i]<=time&&remaining[i]>0){
                if(remaining[i]<minRT){
                    minRT=remaining[i];
                    idx=i;
                }
                else if(remaining[i]==minRT&&at[i]<at[idx])
                    idx=i;
            }
        }
        if(idx==-1){
            time++;
            continue;
        }
        if(!firstRun[idx]){
            rt[idx]=time-at[idx];
            firstRun[idx]=1;
        }
        remaining[idx]--;
        time++;
        if(remaining[idx]==0){
            ct[idx]=time;
            completed++;
        }
    }
    float totalTAT=0,totalWT=0,totalRT=0;
    for(int i=0;i<n;i++){
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];
        totalTAT+=tat[i];
        totalWT+=wt[i];
        totalRT+=rt[i];
    }
    printf("\n%-5s %-5s %-5s %-5s %-5s %-5s %-5s\n","PID","AT","BT","CT","TAT","WT","RT");
    for(int i=0;i<n;i++)
        printf("%-5d %-5d %-5d %-5d %-5d %-5d %-5d\n",pid[i],at[i],bt[i],ct[i],tat[i],wt[i],rt[i]);
    printf("\nAverage TAT = %.2f",totalTAT/n);
    printf("\nAverage WT = %.2f",totalWT/n);
    printf("\nAverage RT = %.2f\n",totalRT/n);
    return 0;
}