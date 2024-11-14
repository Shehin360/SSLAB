#include <stdio.h>
#include <stdlib.h>

void main() {
    int i, j, n, totalHeadMovement = 0, RQ[100], move, initial, size, temp, index;

    // User inputs
    printf("Enter the number of requests: ");
    scanf("%d", &n);

    printf("Enter the request sequence: ");
    for(i = 0; i < n; i++) {
        scanf("%d", &RQ[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &initial);

    printf("Enter the total disk size: ");
    scanf("%d", &size);

    printf("Enter the head movement direction (1 for high, 0 for low): ");
    scanf("%d", &move);

    // Sorting the request array using Bubble Sort
    for(i = 0; i < n; i++) {
        for(j = 0; j < n - i - 1; j++) {
            if(RQ[j] > RQ[j + 1]) {
                temp = RQ[j];
                RQ[j] = RQ[j + 1];
                RQ[j + 1] = temp;
            }
        }
    }

    // Finding the index of the first request greater than the initial head position
    for(i = 0; i < n; i++) {
        if(initial < RQ[i]) {
            index = i;
            break;
        }
    }

    // Processing requests based on head movement direction
    if(move == 1) { // Move towards higher end of the disk
        // Service requests to the right of the initial position
        for(i = index; i < n; i++) {
            totalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }

        // Move to the end of the disk
        totalHeadMovement += abs(size - 1 - initial);
        initial = size - 1;

        // Service remaining requests to the left
        for(i = index - 1; i >= 0; i--) {
            totalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
    }
    else { // Move towards lower end of the disk
        // Service requests to the left of the initial position
        for(i = index - 1; i >= 0; i--) {
            totalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }

        // Move to the start of the disk
        totalHeadMovement += abs(initial - 0);
        initial = 0;

        // Service remaining requests to the right
        for(i = index; i < n; i++) {
            totalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
        }
    }

    // Output total head movement
    printf("Total head movement is %d\n", totalHeadMovement);
}
