#include <iostream>
#include <limits> // For std::numeric_limits
#include <vector>
#include <algorithm> // For std::sort
#include<climits>
using namespace std;

struct Process {
    int pid; // Process ID
    int bt; // Burst Time
    int art; // Arrival Time
};

void findWaitingTime(vector<Process>& proc, int n, vector<int>& wt) {
    vector<int> rt(n);
    for (int i = 0; i < n; i++)
        rt[i] = proc[i].bt;

    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    bool check = false;

    while (complete != n) {
        for (int j = 0; j < n; j++) {
            if ((proc[j].art <= t) && (rt[j] < minm) && rt[j] > 0) {
                minm = rt[j];
                shortest = j;
                check = true;
            }
        }

        if (check == false) {
            t++;
            continue;
        }

        rt[shortest]--;

        minm = rt[shortest];
        if (minm == 0)
            minm = INT_MAX;

        if (rt[shortest] == 0) {
            complete++;
            check = false;
            finish_time = t + 1;
            wt[shortest] = finish_time - proc[shortest].bt - proc[shortest].art;
            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
        t++;
    }
}

void findTurnAroundTime(vector<Process>& proc, int n, vector<int>& wt, vector<int>& tat) {
    for (int i = 0; i < n; i++)
        tat[i] = proc[i].bt + wt[i];
}

void findavgTime(vector<Process>& proc, int n) {
    vector<int> wt(n), tat(n);
    findWaitingTime(proc, n, wt);
    findTurnAroundTime(proc, n, wt, tat);

    cout << " P\t\t"
        << "BT\t\t"
        << "WT\t\t"
        << "TAT\t\t\n";

    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        cout << " " << proc[i].pid << "\t\t"
            << proc[i].bt << "\t\t " << wt[i]
            << "\t\t " << tat[i] << endl;
    }

    cout << "\nAverage waiting time = " << (float)total_wt / (float)n;
    cout << "\nAverage turn around time = " << (float)total_tat / (float)n;
}

bool compareArrivalTime(const Process& a, const Process& b) {
    return a.art < b.art;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    vector<Process> proc(n);
    for (int i = 0; i < n; ++i) {
        cout << "Enter details for process " << i + 1 << endl;
        cout << "Process ID: ";
        cin >> proc[i].pid;
        cout << "Burst Time: ";
        cin >> proc[i].bt;
        cout << "Arrival Time: ";
        cin >> proc[i].art;
    }

    // Sort processes based on arrival time
    sort(proc.begin(), proc.end(), compareArrivalTime);

    findavgTime(proc, n);

    return 0;
}

