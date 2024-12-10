#include <stdio.h>
#include <stdlib.h>

void FIFO(int pages[], int n, int frames){
    int frame[frames];
    int index = 0, pageFaults = 0, pageHits = 0;
    int i, j, k, replacedPage;

    for(i = 0; i < frames; i++){
        frame[i] = -1;
    }

    printf("\nPage\tMemory State\t\tAction\n");
    for(i = 0; i < n; i++){
        int hit = 0;

        // check for a page hit
        for(j = 0; j < frames; j++){
            if(frame[j] == pages[i]){
                hit = 1;
                pageHits++;
                
                printf("%d\t", pages[i]);
                for(k = 0; k < frames; k++){
                    if(frame[k] != -1){
                        printf("%d ", frame[k]);
                    }else{
                        printf("- ");
                    }
                }
                printf("\t\tHit\n");
                break;
            }
        }

        // handle page fault
        if(!hit){
            replacedPage = frame[index]; // store replaced page
            frame[index] = pages[i];    // replace page
            index = (index + 1) % frames; // FIFO logic
            pageFaults++;

            printf("%d\t", pages[i]);
            for(k = 0; k < frames; k++){
                if(frame[k] != -1){
                    printf("%d ", frame[k]);
                }else{
                    printf("- ");
                }
            }
            printf("\t\tFault (Replaced %d)\n", replacedPage == -1 ? -1 : replacedPage);
        }
    }

    float faultPercentage = (float)pageFaults / n * 100;
    float hitPercentage = (float)pageHits / n * 100;

    printf("\nPerformance Metrics\n");
    printf("Total Page Hits: %d\n", pageHits);
    printf("Total Page Faults: %d\n", pageFaults);
    printf("Page Hit Percentage: %.2f%%\n", hitPercentage);
    printf("Page Fault Percentage: %.2f%%\n", faultPercentage);
}

int main(){
	printf("First-In-First-Out (FIFO)\n\n");

    int n, frames, i;
    
    printf("Enter number of pages: ");
    scanf("%d", &n);
    
    int pages[n];
    
    printf("Enter the page sequence: ");
    for(i = 0; i < n; i++){
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    FIFO(pages, n, frames);
    
    /* 
    Sample input for testing:
		- Number of pages: 12
		- Page sequence: 7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3
		- Number of frames: 3
	*/
    
    return 0;
}

