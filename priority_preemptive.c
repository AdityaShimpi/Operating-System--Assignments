
#include <stdio.h>

#define MIN -9999

struct proc {
    int no, at, bt, rt, ct, wt, tat, pri, temp;
};

struct proc read(int i) {
    struct proc p;
    printf("\nProcess No: %d\n", i);
    p.no = i;
    printf("Enter Arrival Time: ");
    scanf("%d", &p.at);
    printf("Enter Burst Time: ");
    scanf("%d", &p.bt);
    p.rt = p.bt;
    printf("Enter Priority: ");
    scanf("%d", &p.pri);
    p.temp = p.pri;
    return p;
}

void main() {
    int i, n, c, remaining, max_val, max_index;
    struct proc p[10], temp;
    float avgtat = 0, avgwt = 0;
    int gantt_chart[1000]; // Assuming 1000 is the maximum time units
    int gantt_chart_index = 0;

    printf("<--Highest Priority First Scheduling Algorithm (Preemptive)-->\n");
    printf("Enter Number of Processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
        p[i] = read(i + 1);

    remaining = n;
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(p[j].at > p[j + 1].at) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    max_val = p[0].temp, max_index = 0;
    for(int j = 0; j < n && p[j].at <= p[0].at; j++) {
        if(p[j].temp > max_val) {
            max_val = p[j].temp;
            max_index = j;
        }
    }

    i = max_index;
    c = p[i].ct = p[i].at + 1;
    gantt_chart[gantt_chart_index++] = p[i].no;
    p[i].rt--;

    if(p[i].rt == 0) {
        p[i].temp = MIN;
        remaining--;
    }

    while(remaining > 0) {
        max_val = p[0].temp, max_index = 0;
        for(int j = 0; j < n && p[j].at <= c; j++) {
            if(p[j].temp > max_val) {
                max_val = p[j].temp;
                max_index = j;
            }
        }
        i = max_index;
        p[i].ct = c = c + 1;
        gantt_chart[gantt_chart_index++] = p[i].no;
        p[i].rt--;

        if(p[i].rt == 0) {
            p[i].temp = MIN;
            remaining--;
        }
    }

    printf("\nProcessNo\tAT\tBT\tPri\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        avgtat += p[i].tat;
        p[i].wt = p[i].tat - p[i].bt;
        avgwt += p[i].wt;
        printf("P%d\t\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].no, p[i].at, p[i].bt, p[i].pri, p[i].ct, p[i].tat, p[i].wt);
    }

    avgtat /= n;
    avgwt /= n;
    printf("\nAverage TurnAroundTime = %f\nAverage WaitingTime = %f", avgtat, avgwt);

    // Print Gantt Chart
    printf("\n\nGantt Chart:\n|");
    for(int i = 0; i < gantt_chart_index; i++) {
        printf(" P%d |", gantt_chart[i]);
    }
    printf("\n0");
    for(int i = 1; i <= gantt_chart_index; i++) {
        printf("   %d", i);
    }
}

