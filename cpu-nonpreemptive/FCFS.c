#include <stdio.h>

typedef struct {
    char processID;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int completionTime;
    int turnaroundTime;    
} fcfs;

// calculates completion time, turnaround time, and waiting time
void calculate(fcfs *f, int processNum) {
	int i = 0;
	
    f[0].completionTime = f[0].arrivalTime + f[0].burstTime;
    f[0].turnaroundTime = f[0].completionTime - f[0].arrivalTime;
    f[0].waitingTime = f[0].turnaroundTime - f[0].burstTime;

    for (i = 1; i < processNum; i++) {
        // if process arrives after the previous process has completed, the time is considered from the previous completion time
        if(f[i].arrivalTime > f[i - 1].completionTime){
            f[i].completionTime = f[i].arrivalTime + f[i].burstTime;
        }else{
            f[i].completionTime = f[i - 1].completionTime + f[i].burstTime;
        }

        f[i].turnaroundTime = f[i].completionTime - f[i].arrivalTime;
        f[i].waitingTime = f[i].turnaroundTime - f[i].burstTime;
    }
}

// computes average waiting time
void avgWaitingTime(fcfs *f, int processNum){
    int i;
	float sum = 0, avgWT = 0;
    
    printf("\nThe average waiting time is\n(");
    
    for(i=0;i<processNum;i++){
    	printf("%d", f[i].waitingTime);
    	if(i<processNum-1){
    		printf(" + ");
		}
    	sum += f[i].waitingTime;
	}
	avgWT = sum/processNum;
	printf(") / %d = %d / %d = %.1f ms\n", processNum, sum, processNum, avgWT);
	
	return;
}

void avgTurnaroundTime(fcfs *f, int processNum) {
    int i;
    float sum = 0, avgTAT = 0;

    printf("\nThe average turnaround time is\n(");

    for (i = 0; i < processNum; i++) {
        printf("%d", f[i].turnaroundTime);
        if (i < processNum - 1) {
            printf(" + ");
        }
        sum += f[i].turnaroundTime;
    }

    avgTAT = sum / processNum;
    printf(") / %d = %.1f ms\n", processNum, avgTAT);
}

void print(fcfs *f, int processNum){
	int i;
	printf("\nProcess |  AT  |  BT  |  CT  | TAT  |  WT\n");
    for(i = 0; i < processNum; i++) {
        printf("   %c    |  %-3d |  %-3d |  %-3d |  %-3d |  %-3d\n", 
               f[i].processID, f[i].arrivalTime, f[i].burstTime,
               f[i].completionTime, f[i].turnaroundTime, f[i].waitingTime);
    }
    
    
	avgWaitingTime(f, processNum);
	avgTurnaroundTime(f, processNum);
}

int main() {
    printf("First Come First Serve (FCFS) CPU Scheduling Algorithm\n\n");
    
    int i, processNum;
    
    printf("Enter number of processes: ");
    scanf("%d", &processNum);
        
    fcfs f[processNum];
    
    printf("\n");
    for(i = 0; i < processNum; i++) {
        f[i].processID = 65 + i; 
        printf("Enter arrival time and burst time for Process %c: ", f[i].processID);
        scanf("%d %d", &f[i].arrivalTime, &f[i].burstTime); 
    }
    
    calculate(f, processNum);
	print(f, processNum);
  
	
    return 0;
}

