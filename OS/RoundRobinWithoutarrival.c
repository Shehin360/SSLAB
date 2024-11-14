#include <stdio.h>

void roundRobin(int processes[], int n, int burstTime[], int timeQuantum) {
    int waitingTime[n], turnAroundTime[n], remainingTime[n];
    int totalWaitingTime = 0, totalTurnAroundTime = 0;

    // Initialize remaining times with burst times
    for (int i = 0; i < n; i++)
        remainingTime[i] = burstTime[i];

    int time = 0; // Current time3
    
    while (1) {
        int done = 1;

        for (int i = 0; i < n; i++) {
            if (remainingTime[i] > 0) {
                done = 0; // At least one process is still remaining

                if (remainingTime[i] > timeQuantum) {
                    time += timeQuantum;
                    remainingTime[i] -= timeQuantum;
                } else {
                    time += remainingTime[i];
                    waitingTime[i] = time - burstTime[i];
                    remainingTime[i] = 0;
                }
            }
        }

        if (done == 1) // If all processes are done
            break;
    }

    // Calculate turnaround time
    for (int i = 0; i < n; i++)
        turnAroundTime[i] = burstTime[i] + waitingTime[i];

    // Calculate total waiting time and turnaround time
    for (int i = 0; i < n; i++) {
        totalWaitingTime += waitingTime[i];
        totalTurnAroundTime += turnAroundTime[i];
    }

    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", i + 1, burstTime[i], waitingTime[i], turnAroundTime[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turnaround Time = %.2f\n", (float)totalTurnAroundTime / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n];
    int burstTime[n];
    int timeQuantum;

    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burstTime[i]);
    }

    printf("Enter time quantum: ");
    scanf("%d", &timeQuantum);

    roundRobin(processes, n, burstTime, timeQuantum);

    return 0;
}
