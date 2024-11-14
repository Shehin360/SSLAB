#include <stdio.h>
#include <stdlib.h>

void main() {
    int i, j, n, totalHeadMovement = 0, RQ[100], move, initial, size, temp, index;
    
    // Read input for number of requests
    printf("Enter the number of requests: ");
    scanf("%d", &n);
    
    // Read the request sequence
    printf("Enter the request sequence: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &RQ[i]);
    }
    
    // Read initial head position, total disk size, and direction of movement
    printf("Enter the initial head position: ");
    scanf("%d", &initial);
    printf("Enter the total disk size: ");
    scanf("%d", &size);
    printf("Enter the head movement direction for high 1 and for low 0: ");
    scanf("%d", &move);
    
    // Sort the request queue in ascending order
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (RQ[j] > RQ[j + 1]) {
                temp = RQ[j];
                RQ[j] = RQ[j + 1];
                RQ[j + 1] = temp;
            }
        }
    }
    
    // Find the index of the first request greater than the initial head position
    for (i = 0; i < n; i++) {
        if (initial < RQ[i]) {
            index = i;
            break;
        }
    }
    
    // C-SCAN Disk Scheduling Logic
    if (move == 1) {  // Move towards higher tracks (right)
        // Serve all requests from the initial position to the end
        for (i = index; i < n; i++) {
            totalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }

        // Move to the end of the disk (size - 1)
        totalHeadMovement += abs(size - 1 - initial);
        initial = 0;
        
        // Move to the beginning of the disk (0)
        totalHeadMovement += abs(size - 1 - initial);

        // Serve all requests from the start to the initial index
        for (i = 0; i < index; i++) {
            totalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
    } 
    else {  // Move towards lower tracks (left)
        // Serve all requests from the initial position to the beginning
        for (i = index - 1; i >= 0; i--) {
            totalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }

        // Move to the beginning of the disk (0)
        totalHeadMovement += abs(initial - 0);
        initial = size - 1;

        // Jump to the end of the disk (size - 1)
        totalHeadMovement += abs(initial - 0);

        // Serve all requests from the end to the initial index
        for (i = n - 1; i >= index; i--) {
            totalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
    }
    
    // Output the total head movement
    printf("Total head movement is %d\n", totalHeadMovement);
}
