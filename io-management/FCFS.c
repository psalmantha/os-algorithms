#include <stdio.h>

typedef struct {
    char processID;
    int arrivalTime;
    int burstTime;
    int ioTime; // I/O time
    int waitingTime;
    int completionTime;
    int turnaroundTime;    
} Process;

// Calculates completion time, turnaround time, and waiting time
void calculate(Process *p, int processNum) {
    int i = 0;
    
    // Calculate for the first process
    p[0].completionTime = p[0].arrivalTime + p[0].burstTime + p[0].ioTime;
    p[0].turnaroundTime = p[0].completionTime - p[0].arrivalTime;
    p[0].waitingTime = p[0].turnaroundTime - p[0].burstTime;

    for (i = 1; i < processNum; i++) {
        // If process arrives after the previous process has completed
        if (p[i].arrivalTime > p[i - 1].completionTime) {
            p[i].completionTime = p[i].arrivalTime + p[i].burstTime + p[i].ioTime;
        } else {
            p[i].completionTime = p[i - 1].completionTime + p[i].burstTime + p[i].ioTime;
        }

        p[i].turnaroundTime = p[i].completionTime - p[i].arrivalTime;
        p[i].waitingTime = p[i].turnaroundTime - p[i].burstTime;
    }
}

// Computes average waiting time
void avgWaitingTime(Process *p, int processNum) {
    int i;
    float sum = 0, avgWT = 0;
    
    printf("\nThe average waiting time is:\n(");
    
    for (i = 0; i < processNum; i++) {
        printf("%d", p[i].waitingTime);
        if (i < processNum - 1) {
            printf(" + ");
        }
        sum += p[i].waitingTime;
    }
    avgWT = sum / processNum;
    printf(") / %d = %.1f ms\n", processNum, avgWT);
}

void avgTurnaroundTime(Process *p, int processNum) {
    int i;
    float sum = 0, avgTAT = 0;

    printf("\nThe average turnaround time is:\n(");

    for (i = 0; i < processNum; i++) {
        printf("%d", p[i].turnaroundTime);
        if (i < processNum - 1) {
            printf(" + ");
        }
        sum += p[i].turnaroundTime;
    }

    avgTAT = sum / processNum;
    printf(") / %d = %.1f ms\n", processNum, avgTAT);
}

void print(Process *p, int processNum) {
    int i;
    printf("\nProcess |  AT  |  BT  |  I/O |  CT  | TAT  |  WT\n");
    for (i = 0; i < processNum; i++) {
        printf("   %c    |  %-3d |  %-3d |  %-3d |  %-3d |  %-3d |  %-3d\n", 
               p[i].processID, p[i].arrivalTime, p[i].burstTime,
               p[i].ioTime, p[i].completionTime, p[i].turnaroundTime, p[i].waitingTime);
    }
    
    avgWaitingTime(p, processNum);
    avgTurnaroundTime(p, processNum);
}

int main() {
    printf("First Come First Serve (FCFS) CPU Scheduling Algorithm with I/O Management\n\n");
    
    int i, processNum;
    
    printf("Enter number of processes: ");
    scanf("%d", &processNum);
        
    Process p[processNum];
    
    printf("\n");
    for (i = 0; i < processNum; i++) {
        p[i].processID = 65 + i; // Assign process ID (A, B, C, ...)
        printf("Enter arrival time, burst time, and I/O time for Process %c: ", p[i].processID);
        scanf("%d %d %d", &p[i].arrivalTime, &p[i].burstTime, &p[i].ioTime); 
    }
    
    calculate(p, processNum);
    print(p, processNum);
  
    return 0;
}