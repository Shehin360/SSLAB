#include <stdio.h>

void roundRobin(int processes[], int n, int burstTime[], int arrivalTime[], int timeQuantum) {
    int waitingTime[n], turnAroundTime[n], remainingTime[n];
    int totalWaitingTime = 0, totalTurnAroundTime = 0;

    // Initialize remaining times with burst times
    for (int i = 0; i < n; i++)
        remainingTime[i] = burstTime[i];

    int time = 0; // Current time
    int completed = 0; // Track completed processes

    while (completed < n) {
        int done = 1;

        for (int i = 0; i < n; i++) {
            // Process only if it has arrived and still has remaining time
            if (arrivalTime[i] <= time && remainingTime[i] > 0) {
                done = 0; // There is a pending process
                if (remainingTime[i] > timeQuantum) {
                    time += timeQuantum;
                    remainingTime[i] -= timeQuantum;
                } else {
                    time += remainingTime[i];
                    waitingTime[i] = time - burstTime[i] - arrivalTime[i];
                    remainingTime[i] = 0;
                    completed++;
                }
            }
        }

        // If no process was ready in this round, advance the time
        if (done == 1) {
            time++;
        }
    }

    // Calculate turnaround time for each process
    for (int i = 0; i < n; i++)
        turnAroundTime[i] = burstTime[i] + waitingTime[i];

    // Calculate total waiting and turnaround times
    for (int i = 0; i < n; i++) {
        totalWaitingTime += waitingTime[i];
        totalTurnAroundTime += turnAroundTime[i];
    }

    // Display results
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i], arrivalTime[i], burstTime[i], waitingTime[i], turnAroundTime[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", (float)totalWaitingTime / n);
    printf("Average Turnaround Time = %.2f\n", (float)totalTurnAroundTime / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n], burstTime[n], arrivalTime[n], timeQuantum;

    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &arrivalTime[i]);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burstTime[i]);
    }

    printf("Enter time quantum: ");
    scanf("%d", &timeQuantum);

    roundRobin(processes, n, burstTime, arrivalTime, timeQuantum);

    return 0;
}
