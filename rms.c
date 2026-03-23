#include <stdio.h>
#define MAX_TASKS 10
#define MAX_TIME 20
typedef struct {
    int id;
    int C;
    int P;
    int next_arrival;
    int remaining_time;
} Task;
int main() {
    int n, i, j, time;
    Task tasks[MAX_TASKS];
    int schedule[MAX_TIME];
    printf("Enter number of tasks: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("Enter execution time and period for Task %d: ", i + 1);
        scanf("%d %d", &tasks[i].C, &tasks[i].P);
        tasks[i].next_arrival = 0;
        tasks[i].remaining_time = 0;
    }
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (tasks[i].P > tasks[j].P) {
                Task temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;
            }
        }
    }
    for (time = 0; time < MAX_TIME; time++) {
        for (i = 0; i < n; i++) {
            if (time == tasks[i].next_arrival) {
                tasks[i].remaining_time = tasks[i].C;
                tasks[i].next_arrival += tasks[i].P;
            }
        }
        int current_task = -1;
        for (i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0) {
                current_task = i;
                break;
            }
        }
        if (current_task != -1) {
            schedule[time] = tasks[current_task].id;
            tasks[current_task].remaining_time--;
        } else {
            schedule[time] = 0;
        }
        for (i = 0; i < n; i++) {
            if (time >= tasks[i].next_arrival && tasks[i].remaining_time > 0) {
                printf("Deadline Missed by Task %d at time %d\n",
                       tasks[i].id, time);
            }
        }
    }
printf("\n\nGANTT CHART:\n\n");

printf(" ");
for (time = 0; time < MAX_TIME; time++) {
    printf("-------");
}
printf("\n|");
for (time = 0; time < MAX_TIME; time++) {
    if (schedule[time] == 0)
        printf(" Idle |");
    else
        printf(" T%-2d |", schedule[time]);
}
printf("\n ");
for (time = 0; time < MAX_TIME; time++) {
    printf("-------");
}
printf("\n");
for (time = 0; time <= MAX_TIME; time++) {
    printf("%-7d", time);
}

printf("\n");

float utilization = 0.0;

for (i = 0; i < n; i++) {
    utilization += (float)tasks[i].C / tasks[i].P;
}

printf("\nCPU Utilization = %.2f (%.2f%%)\n", utilization, utilization * 100);

    return 0;
}
