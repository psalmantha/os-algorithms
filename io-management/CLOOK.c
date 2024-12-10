#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int head_position;
    int total_head_movement;
    int disk_size;
} DiskArm;

void CLOOK(DiskArm *disk, int requests[], int n, int served_order[]){
    int i, j, temp;
    int sorted_requests[n];

    for(i = 0; i < n; i++){
        sorted_requests[i] = requests[i];
    }

    for(i = 0; i < n; i++){
        for(j = 0; j < n - 1 - i; j++){
            if(sorted_requests[j] > sorted_requests[j + 1]){
                temp = sorted_requests[j];
                sorted_requests[j] = sorted_requests[j + 1];
                sorted_requests[j + 1] = temp;
            }
        }
    }

    int start_index = 0;
    for(i = 0; i < n; i++){
        if(sorted_requests[i] >= disk->head_position){
            start_index = i;
            break;
        }
    }

    int index = 0;

    printf("\nServing Tracks (Moving Right)...\n");
    for(i = start_index; i < n; i++){
        printf("Head at %d -> Moving to %d (Distance: %d)\n", disk->head_position, sorted_requests[i], abs(disk->head_position - sorted_requests[i]));
        served_order[index++] = sorted_requests[i];
        disk->total_head_movement += abs(disk->head_position - sorted_requests[i]);
        disk->head_position = sorted_requests[i];
    }

    printf("\nJumping Back to Start of Left Unserved Requests...\n");
    for(i = 0; i < start_index; i++){
        printf("Head at %d -> Moving to %d (Distance: %d)\n", disk->head_position, sorted_requests[i], abs(disk->head_position - sorted_requests[i]));
        served_order[index++] = sorted_requests[i];
        disk->total_head_movement += abs(disk->head_position - sorted_requests[i]);
        disk->head_position = sorted_requests[i];
    }
}

void displayOrder(int served_order[], int n){
    int i;

    printf("\nOrder of track requests served: ");
    for(i = 0; i < n; i++){
        printf("%d ", served_order[i]);
    }
    printf("\n");
}

int main(){
    printf("Circular Look (CLOOK)\n\n");

    int disk_size, n, initial_position, i;

    printf("Enter the total number of tracks on the disk: ");
    scanf("%d", &disk_size);

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int requests[n], served_order[n];

    printf("Enter the track requests: ");
    for(i = 0; i < n; i++){
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial position of the disk arm: ");
    scanf("%d", &initial_position);

    DiskArm disk;
    disk.head_position = initial_position;
    disk.total_head_movement = 0;
    disk.disk_size = disk_size;

    CLOOK(&disk, requests, n, served_order);

    displayOrder(served_order, n);

    printf("\nTotal head movement: %d\n", disk.total_head_movement);

    return 0;
}

