#include <stdio.h>
#include <stdlib.h>

void LFU(int pages[], int n, int frames){
    int frame[frames], freq[frames];
    int pageFaults = 0, pageHits = 0;
    int i, j, k, minIndex, replacedPage;

    for(i=0; i<frames; i++){
        frame[i] = -1; // initialize frames as empty
        freq[i] = 0;   // initialize frequencies
    }

    printf("\nPage\tMemory State\t\tAction\n");
    for(i=0; i<n; i++){
        int hit = 0;

        for(j=0; j<frames; j++){
            if(frame[j] == pages[i]){
                hit = 1;
                freq[j]++;
                pageHits++;
                break;
            }
        }

        if(!hit){
            pageFaults++;
            replacedPage = -1;

            for(j=0; j<frames; j++){
                if(frame[j] == -1){
                    frame[j] = pages[i];
                    freq[j] = 1;
                    break;
                }else if(j == frames - 1){
                    minIndex = 0;
                    for(k=1; k<frames; k++){
                        if(freq[k] < freq[minIndex]){
                            minIndex = k;
                        }
                    }
                    replacedPage = frame[minIndex];
                    frame[minIndex] = pages[i];
                    freq[minIndex] = 1;
                }
            }

            printf("%d\t", pages[i]);
            for(j=0; j<frames; j++){
                if(frame[j] != -1){
                    printf("%d ", frame[j]);
                }else{
                    printf("- ");
                }
            }
            printf("\t\tFault (Replaced %d)\n", replacedPage);
        }else{
            printf("%d\t", pages[i]);
            
            for(j=0; j<frames; j++){
                if(frame[j] != -1){
                    printf("%d ", frame[j]);
                }else{
                    printf("- ");
                }
            }
            printf("\t\tHit\n");
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
	printf("Least Frequently Used (LFU)\n\n");

    int n, frames, i;
    
    printf("Enter number of pages: ");
    scanf("%d", &n);
    
    int pages[n];
    
    printf("Enter the page sequence: ");
    for(i=0; i<n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    LFU(pages, n, frames);
    
    /* 
    Sample input for testing:
		- Number of pages: 12
		- Page sequence: 7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3
		- Number of frames: 3
	*/
    
    return 0;
}

