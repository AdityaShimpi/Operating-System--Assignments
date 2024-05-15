#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
bool finished[MAX_PROCESSES];

// Function to check if the system is in a safe state
bool isSafe() {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES];
    for (int i = 0; i < MAX_RESOURCES; i++)
        work[i] = available[i];
    for (int i = 0; i < MAX_PROCESSES; i++)
        finish[i] = false;

    int num_finished = 0;
    while (num_finished < MAX_PROCESSES) {
        bool found = false;
        for (int i = 0; i < MAX_PROCESSES; i++) {
            if (!finish[i]) {
                bool can_process = true;
                for (int j = 0; j < MAX_RESOURCES; j++) {
                    if (need[i][j] > work[j]) {
                        can_process = false;
                        break;
                    }
                }
                if (can_process) {
                    for (int j = 0; j < MAX_RESOURCES; j++)
                        work[j] += allocation[i][j];
                    finish[i] = true;
                    found = true;
                    num_finished++;
                }
            }
        }
        if (!found)
            return false; // No process found that can be executed, system is in an unsafe state
    }
    return true; // System is in a safe state
}

// Function to find the safe sequence
void findSafeSequence() {
    int safeSequence[MAX_PROCESSES];
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES];
    for (int i = 0; i < MAX_RESOURCES; i++)
        work[i] = available[i];
    for (int i = 0; i < MAX_PROCESSES; i++)
        finish[i] = false;

    int num_finished = 0;
    while (num_finished < MAX_PROCESSES) {
        bool found = false;
        for (int i = 0; i < MAX_PROCESSES; i++) {
            if (!finish[i]) {
                bool can_process = true;
                for (int j = 0; j < MAX_RESOURCES; j++) {
                    if (need[i][j] > work[j]) {
                        can_process = false;
                        break;
                    }
                }
                if (can_process) {
                    for (int j = 0; j < MAX_RESOURCES; j++)
                        work[j] += allocation[i][j];
                    safeSequence[num_finished] = i;
                    finish[i] = true;
                    found = true;
                    num_finished++;
                }
            }
        }
        if (!found) {
            printf("System is in an unsafe state.\n");
            return;
        }
    }
    printf("Safe sequence: ");
    for (int i = 0; i < MAX_PROCESSES; i++)
        printf("%d ", safeSequence[i]);
    printf("\n");
}

// Function to allocate resources to a process
void allocateResources(int process, int resources[]) {
    for (int i = 0; i < MAX_RESOURCES; i++) {
        available[i] -= resources[i];
        allocation[process][i] += resources[i];
        need[process][i] -= resources[i];
    }
}

// Function to release resources held by a process
void releaseResources(int process, int resources[]) {
    for (int i = 0; i < MAX_RESOURCES; i++) {
        available[i] += resources[i];
        allocation[process][i] -= resources[i];
        need[process][i] += resources[i];
    }
}

int main() {
    // Initialize available resources
    printf("Enter the available resources: ");
    for (int i = 0; i < MAX_RESOURCES; i++)
        scanf("%d", &available[i]);

    // Initialize maximum resources for each process
    printf("Enter the maximum resources for each process:\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < MAX_RESOURCES; j++)
            scanf("%d", &maximum[i][j]);
    }

    // Initialize allocation and need matrices
    for (int i = 0; i < MAX_PROCESSES; i++) {
        for (int j = 0; j < MAX_RESOURCES; j++) {
            allocation[i][j] = 0;
            need[i][j] = maximum[i][j];
        }
    }

    // Perform resource allocation
    allocateResources(0, (int[]){0, 1, 0});
    allocateResources(1, (int[]){2, 0, 0});
    allocateResources(2, (int[]){3, 0, 2});
    allocateResources(3, (int[]){2, 1, 1});
    allocateResources(4, (int[]){0, 0, 2});

    // Check if system is in a safe state and find safe sequence
    if (isSafe())
        findSafeSequence();
    else
        printf("System is in an unsafe state.\n");

    return 0;
}
