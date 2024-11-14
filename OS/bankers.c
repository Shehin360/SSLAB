#include <stdio.h>

int main() {
    int n, m, i, j, k, y, ind = 0;
    
    // Declare matrices and arrays
    int alloc[20][20], max[20][20], avail[50];
    int finish[20], safesequence[20], work[50], need[20][20];

    // Input number of processes and resources
    printf("Enter the number of Processes: ");
    scanf("%d", &n);
    printf("Enter the number of Resources: ");
    scanf("%d", &m);

    // Input the Allocation Matrix
    printf("Enter the Allocation Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Input the Max Matrix
    printf("Enter the Max Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input the Available Resources
    printf("Enter the Available Resources:\n");
    for (i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    // Calculate the Need Matrix (Need = Max - Allocation)
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Display the Need Matrix
    printf("NEED Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // Initialize the Work and Finish arrays
    for (i = 0; i < m; i++) {
        work[i] = avail[i];  // Set work array to available resources
    }

    for (i = 0; i < n; i++) {
        finish[i] = 0;  // Set all processes as not finished
    }

    // Banker's Algorithm: Check for safe sequence
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {  // Check if the process i is not finished
                int flag = 0;  // Flag to check if process i can be executed

                // Check if process i can be executed (Need <= Work)
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        flag = 1;  // Process can't execute yet
                        break;
                    }
                }

                // If process i can be executed, add it to the safe sequence
                if (flag == 0) {
                    safesequence[ind++] = i;  // Add process i to safe sequence

                    // Add allocated resources of process i to work array
                    for (y = 0; y < m; y++) {
                        work[y] += alloc[i][y];
                    }

                    finish[i] = 1;  // Mark process i as finished
                }
            }
        }
    }

    // Output the Safe Sequence
    printf("\nFollowing is the SAFE Sequence:\n");
    for (i = 0; i < n; i++) {
        printf("P%d ", safesequence[i]);
    }
    printf("\n");

    return 0;
}
