// /Users/clybel/OS/Algos/sjf.c
#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 100

// Structure to hold process information
struct Process {
    int process_id;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

// Function to compare processes based on burst time
int compare(const void *a, const void *b) {
    struct Process *p1 = (struct Process *)a;
    struct Process *p2 = (struct Process *)b;
    return p1->burst_time - p2->burst_time;
}

// Function to calculate waiting time
void calculate_waiting_time(struct Process proc[], int totalprocess) {
    proc[0].waiting_time = 0; // First process has no waiting time

    for (int i = 1; i < totalprocess; i++) {
        proc[i].waiting_time = proc[i - 1].waiting_time + proc[i - 1].burst_time;
    }
}

// Function to calculate turnaround time
void calculate_turnaround_time(struct Process proc[], int totalprocess) {
    for (int i = 0; i < totalprocess; i++) {
        proc[i].turnaround_time = proc[i].burst_time + proc[i].waiting_time;
    }
}

// Function to find Gantt Chart and display process details
void find_gantt_chart(struct Process proc[], int totalprocess) {
    float total_waiting_time = 0, total_turnaround_time = 0;

    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < totalprocess; i++) {
        total_waiting_time += proc[i].waiting_time;
        total_turnaround_time += proc[i].turnaround_time;

        printf("%d\t%d\t\t%d\t\t%d\n", 
               proc[i].process_id, proc[i].burst_time, 
               proc[i].waiting_time, proc[i].turnaround_time);
    }

    // Display the average waiting time and average turnaround time
    printf("Average waiting time: %.2f\n", total_waiting_time / totalprocess);
    printf("Average turnaround time: %.2f\n", total_turnaround_time / totalprocess);
}

// Driver code
int main() {
    int totalprocess;
    struct Process proc[MAX_PROCESSES];

    printf("SHORTEST JOB FIRST\n");
    printf("Enter the number of processes: ");
    scanf("%d", &totalprocess);
    printf("---\n");

    for (int i = 0; i < totalprocess; i++) {
        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &proc[i].burst_time);
        proc[i].process_id = i + 1; // Assign process ID
    }

    // Using qsort to sort processes by burst time
    qsort(proc, totalprocess, sizeof(struct Process), compare);
    
    // Calculate waiting time and turnaround time
    calculate_waiting_time(proc, totalprocess);
    calculate_turnaround_time(proc, totalprocess);
    
    // Calling function to find Gantt Chart and display results
    find_gantt_chart(proc, totalprocess);

    return 0;
}