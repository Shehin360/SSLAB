#include <stdio.h>

// Main function starts here
void main()
{
    // Declare variables with full names
    int index, frameIndex, referenceIndex, referenceStringLength, numberOfFrames;
    int referenceString[25], pageFaultCount = 0, frameContents[10], pageFrequency[10] = {0};
    
    // Variable to store if the page is used (initially set to 0 for all frames)
    int isFrameUsed[10] = {0};

    // Prompt user to input the length of the reference string
    printf("Enter the reference string length: ");
    scanf("%d", &referenceStringLength);

    // Prompt user to input the reference string
    printf("Enter the reference string: ");
    for (index = 0; index < referenceStringLength; index++)
    {
        scanf("%d", &referenceString[index]);
    }

    // Prompt user to input the number of frames available for page replacement
    printf("Enter the number of frames: ");
    scanf("%d", &numberOfFrames);

    // Initialize the frames with -1 (empty state)
    for (index = 0; index < numberOfFrames; index++)
    {
        frameContents[index] = -1;
    }

    // Print header for page replacement process display
    printf("The page replacement process is:\n");

    // Iterate through each page in the reference string
    for (referenceIndex = 0; referenceIndex < referenceStringLength; referenceIndex++)
    {
        // Variable to track if the page is already present in any frame
        int pageIndexInFrame = -1;

        // Check if the current page is already in one of the frames
        for (frameIndex = 0; frameIndex < numberOfFrames; frameIndex++)
        {
            if (frameContents[frameIndex] == referenceString[referenceIndex])
            {
                pageIndexInFrame = frameIndex; // Page found in the frame
                pageFrequency[pageIndexInFrame]++; // Increment frequency of the page
                break; // No need to check further frames
            }
        }

        // If the page was not found in any frame (page fault)
        if (pageIndexInFrame == -1)
        {
            // Find the frame with the least frequently used page
            int minFrequency = pageFrequency[0]; // Start by assuming the first frame has the least frequency
            int minFrequencyFrameIndex = 0;

            // Iterate through all frames to find the least frequent page
            for (frameIndex = 1; frameIndex < numberOfFrames; frameIndex++)
            {
                if (pageFrequency[frameIndex] < minFrequency)
                {
                    minFrequency = pageFrequency[frameIndex];
                    minFrequencyFrameIndex = frameIndex; // Update the index of the least frequent frame
                }
            }

            // Replace the least frequent page with the new page
            frameContents[minFrequencyFrameIndex] = referenceString[referenceIndex];
            pageFrequency[minFrequencyFrameIndex] = 1; // Set the frequency of the new page to 1
            pageFaultCount++; // Increment page fault count
        }
        else
        {
            // If the page was found, simply increment its frequency
            pageFrequency[pageIndexInFrame]++;
        }

        // Print the contents of the frames after this page replacement
        for (frameIndex = 0; frameIndex < numberOfFrames; frameIndex++)
        {
            printf("%d\t", frameContents[frameIndex]);
        }
        printf("\n");
    }

    // Output the total number of page faults
    printf("The total number of page faults using LFU are: %d\n", pageFaultCount);
}
