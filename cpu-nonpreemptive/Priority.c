// /Users/clybel/OS/Algos/npp.c
#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 100

// Structure to hold process information
struct Process {
    int arrival_time;
    int burst_time;
    int priority;
    int process_id;
};

// Function to compare processes based on arrival time and priority
int compare(const void *a, const void *b) {
    struct Process *p1 = (struct Process *)a;
    struct Process *p2 = (struct Process *)b;
    if (p1->arrival_time == p2->arrival_time) {
        return p1->priority - p2->priority;
    }
    return p1->arrival_time - p2->arrival_time;
}

// Function to calculate waiting time
void get_wt_time(struct Process proc[], int totalprocess, int wt[]) {
    int service[MAX_PROCESSES] = {0};
    service[0] = 0;
    wt[0] = 0;

    for (int i = 1; i < totalprocess; i++) {
        service[i] = proc[i - 1].burst_time + service[i - 1];
        wt[i] = service[i] - proc[i].arrival_time;

        // If waiting time is negative, change it to zero
        if (wt[i] < 0) {
            wt[i] = 0;
        }
    }
}

// Function to calculate turnaround time
void get_tat_time(struct Process proc[], int totalprocess, int wt[], int tat[]) {
    for (int i = 0; i < totalprocess; i++) {
        tat[i] = proc[i].burst_time + wt[i];
    }
}

// Function to find Gantt Chart
void findgc(struct Process proc[], int totalprocess) {
    int wt[MAX_PROCESSES] = {0};
    int tat[MAX_PROCESSES] = {0};
    float wavg = 0, tavg = 0;

    // Function call to find waiting time array
    get_wt_time(proc, totalprocess, wt);
    
    // Function call to find turnaround time
    get_tat_time(proc, totalprocess, wt, tat);

    int stime[MAX_PROCESSES] = {0};
    int ctime[MAX_PROCESSES] = {0};
    stime[0] = 1;
    ctime[0] = stime[0] + tat[0];

    // Calculating starting and ending time
    for (int i = 1; i < totalprocess; i++) {
        stime[i] = ctime[i - 1];
        ctime[i] = stime[i] + tat[i] - wt[i];
    }

    printf("Process\tStart_time\tComplete_time\tTurn_Around_Time\tWaiting_Time\n");

    // Display the process details
    for (int i = 0; i < totalprocess; i++) {
        wavg += wt[i];
        tavg += tat[i];
        
        printf("%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", 
               proc[i].process_id, stime[i], ctime[i], tat[i], wt[i]);
    }

    // Display the average waiting time and average turnaround time
    printf("Average waiting time is : %.2f\n", wavg / totalprocess);
    printf("Average turnaround time : %.2f\n", tavg / totalprocess);
}

// Driver code
int main() {
    int totalprocess;
    struct Process proc[MAX_PROCESSES];

    printf("PRIORITY - NON PREEMPTIVE\n");
    printf("Enter the number of processes: ");
    scanf("%d", &totalprocess);
    printf("---\n");

    for (int i = 0; i < totalprocess; i++) {
        printf("Enter arrival time for P%d: ", i + 1);
        scanf("%d", &proc[i].arrival_time);
        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &proc[i].burst_time);
        printf("Enter priority for P%d: ", i + 1);
        scanf("%d", &proc[i].priority);
        proc[i].process_id = i + 1; // Assign process ID
    }

    // Using qsort to sort processes by arrival time and then by priority
    qsort(proc, totalprocess, sizeof(struct Process), compare);
    
    // Calling function findgc for finding Gantt Chart
    findgc(proc, totalprocess);

    return 0;
}