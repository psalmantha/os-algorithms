#include <stdio.h>
#include <stdlib.h>

struct Process {
    int processID, 
    burstTime, 
    arrivalTime, 
    priority, 
    outTime, 
    inTime, 
    responseTime;
};

void insert(struct Process heap[], struct Process value, int* heapSize, int* currentTime) {
    int i = (*heapSize)++;
    heap[i] = value;
    if (heap[i].inTime == -1) heap[i].inTime = *currentTime;

    while (i > 0 && heap[(i - 1) / 2].priority > heap[i].priority) {
        struct Process temp = heap[(i - 1) / 2];
        heap[(i - 1) / 2] = heap[i];
        heap[i] = temp;
        i = (i - 1) / 2;
    }
}

void order(struct Process heap[], int* heapSize, int start) {
    int smallest = start, left = 2 * start + 1, right = 2 * start + 2;
    if (left < *heapSize && heap[left].priority < heap[smallest].priority) smallest = left;
    if (right < *heapSize && heap[right].priority < heap[smallest].priority) smallest = right;

    if (smallest != start) {
        struct Process temp = heap[smallest];
        heap[smallest] = heap[start];
        heap[start] = temp;
        order(heap, heapSize, smallest);
    }
}

struct Process extractMin(struct Process heap[], int* heapSize, int* currentTime) {
    struct Process min = heap[0];
    if (min.responseTime == -1) min.responseTime = *currentTime - min.arrivalTime;
    heap[0] = heap[--(*heapSize)];
    order(heap, heapSize, 0);
    return min;
}

void scheduling(struct Process heap[], struct Process array[], int n, int* heapSize, int* currentTime) {
    if (*heapSize == 0) return;

    struct Process min = extractMin(heap, heapSize, currentTime);
    min.outTime = ++(*currentTime);
    min.burstTime--;

    if (min.burstTime > 0) {
        insert(heap, min, heapSize, currentTime);
    } else {
        for (int i = 0; i < n; i++) {
            if (array[i].processID == min.processID) {
                array[i] = min;
                break;
            }
        }
    }
}

void priorityScheduling(struct Process array[], int n) {
    int heapSize = 0, currentTime = array[0].arrivalTime;
    struct Process heap[4 * n];

    for (int i = 0; i < n; i++) {
        array[i].responseTime = -1;
    }

    while (1) {
        for (int i = 0; i < n; i++) {
            if (array[i].arrivalTime == currentTime) {
                insert(heap, array[i], &heapSize, &currentTime);
            }
        }
        scheduling(heap, array, n, &heapSize, &currentTime);
        if (heapSize == 0 && currentTime >= array[n - 1].arrivalTime) break;
        currentTime++;
    }

    float totalWaitingTime = 0, totalResponseTime = 0;
    for (int i = 0; i < n; i++) {
        totalWaitingTime += (array[i].outTime - array[i].arrivalTime - (array[i].burstTime + 1));
        totalResponseTime += array[i].responseTime;
    }
    printf("Average waiting time = %f\n", totalWaitingTime / n);
    printf("Average response time = %f\n", totalResponseTime / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process* a = (struct Process*)malloc(n * sizeof(struct Process));

    for (int i = 0; i < n; i++) {
        printf("Enter details for process %d:\n", i + 1);
        printf("Process ID: ");
        scanf("%d", &a[i].processID);
        printf("Burst Time: ");
        scanf("%d", &a[i].burstTime);
        printf("Arrival Time: ");
        scanf("%d", &a[i].arrivalTime);
        printf("Priority: ");
        scanf("%d", &a[i].priority);
        a[i].outTime = 0;
        a[i].inTime = -1;
        a[i].responseTime = -1;
    }

    priorityScheduling(a, n);
    free(a);
    return 0;
}