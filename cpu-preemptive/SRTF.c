#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

struct Process {
    int id; // Process ID
    int burstTime; // Burst Time
    int arrivalTime; // Arrival Time
};

// Function to calculate waiting time for all processes
void calculateWaitingTime(struct Process processes[], int count, int waitingTime[]) {
    int remainingTime[count];

    // Initialize remaining time with burst time
    for (int i = 0; i < count; i++)
        remainingTime[i] = processes[i].burstTime;

    int completed = 0, currentTime = 0, minRemainingTime = INT_MAX;
    int shortestIndex = 0, finishTime;
    int foundProcess = 0;

    // Process until all processes are completed
    while (completed != count) {
        // Find the process with the minimum remaining time
        for (int j = 0; j < count; j++) {
            if ((processes[j].arrivalTime <= currentTime) &&
                (remainingTime[j] < minRemainingTime) && remainingTime[j] > 0) {
                minRemainingTime = remainingTime[j];
                shortestIndex = j;
                foundProcess = 1;
            }
        }

        if (foundProcess == 0) {
            currentTime++;
            continue;
        }

        // Reduce remaining time by one
        remainingTime[shortestIndex]--;

        // Update minimum remaining time
        minRemainingTime = remainingTime[shortestIndex];
        if (minRemainingTime == 0)
            minRemainingTime = INT_MAX;

        // If a process is completely executed
        if (remainingTime[shortestIndex] == 0) {
            completed++;
            foundProcess = 0;

            // Calculate finish time and waiting time
            finishTime = currentTime + 1;
            waitingTime[shortestIndex] = finishTime - processes[shortestIndex].burstTime - processes[shortestIndex].arrivalTime;

            if (waitingTime[shortestIndex] < 0)
                waitingTime[shortestIndex] = 0;
        }
        // Increment time
        currentTime++;
    }
}

// Function to calculate turnaround time
void calculateTurnAroundTime(struct Process processes[], int count, int waitingTime[], int turnAroundTime[]) {
    for (int i = 0; i < count; i++)
        turnAroundTime[i] = processes[i].burstTime + waitingTime[i];
}

// Function to calculate and display average times
void calculateAverageTime(struct Process processes[], int count) {
    int waitingTime[count], turnAroundTime[count], totalWaitingTime = 0, totalTurnAroundTime = 0;

    calculateWaitingTime(processes, count, waitingTime);
    calculateTurnAroundTime(processes, count, waitingTime, turnAroundTime);

    // Display process details
    printf("ID\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < count; i++) {
        totalWaitingTime += waitingTime[i];
        totalTurnAroundTime += turnAroundTime[i];
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].burstTime, waitingTime[i], turnAroundTime[i]);
    }

    printf("\nAverage waiting time = %.2f", (float)totalWaitingTime / count);
    printf("\nAverage turnaround time = %.2f\n", (float)totalTurnAroundTime / count);
}

// Driver code
int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process* processes = (struct Process*)malloc(n * sizeof(struct Process));

    for (int i = 0; i < n; i++) {
        printf("Enter details for process %d:\n", i + 1);
        printf("Process ID: ");
        scanf("%d", &processes[i].id);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burstTime);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrivalTime);
    }

    calculateAverageTime(processes, n);
    free(processes); // Free allocated memory
    return 0;
}