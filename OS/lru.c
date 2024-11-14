#include <stdio.h>

// Main function
void main()
{
    int index, j, k, referenceStringLength, numberOfFrames, referenceString[25], pageFaults = 0, frameMemory[10], lastUsedTime[10] = {0};
    
    // Prompt the user to enter the reference string length
    printf("Enter the reference string length: ");
    scanf("%d", &referenceStringLength);

    // Prompt the user to enter the reference string (sequence of page requests)
    printf("Enter the reference string: ");
    for (index = 0; index < referenceStringLength; index++) {
        scanf("%d", &referenceString[index]);
    }

    // Prompt the user to enter the number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &numberOfFrames);

    // Initialize the frame memory to -1, indicating that all frames are empty initially
    for (index = 0; index < numberOfFrames; index++) {
        frameMemory[index] = -1;
    }

    // Display the page replacement process
    printf("The page replacement process is:\n");

    // Loop through the reference string to process each page request
    for(index = 0; index < referenceStringLength; index++) {

        // Check if the current page is already in one of the frames
        for(k = 0; k < numberOfFrames; k++) {
            if(frameMemory[k] == referenceString[index]) {
                // Update the last used time for this frame
                lastUsedTime[k] = index + 1;
                break;  // Exit the loop as the page is already in a frame
            }
        }

        // If the page is not found in any frame, a page fault occurs
        if(k == numberOfFrames) {
            int minTime = lastUsedTime[0], minIndex = 0;

            // Find the frame with the least recent usage (i.e., the one that hasn't been used for the longest time)
            for(j = 1; j < numberOfFrames; j++) {
                if(lastUsedTime[j] < minTime) {
                    minTime = lastUsedTime[j];
                    minIndex = j;
                }
            }

            // Replace the least recently used page with the current page
            frameMemory[minIndex] = referenceString[index];
            
            // Update the last used time for the replaced page
            lastUsedTime[minIndex] = index + 1;
            
            // Increment the page fault counter
            pageFaults++;
        }

        // Print the current state of the frames after each page request
        for (j = 0; j < numberOfFrames; j++) {
            printf("%d\t", frameMemory[j]);
        }
        printf("\n");
    }

    // Display the total number of page faults
    printf("The total number of page faults using LRU are: %d", pageFaults);
}
