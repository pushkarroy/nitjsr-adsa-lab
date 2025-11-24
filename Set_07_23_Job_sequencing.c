// Write a function to implement the job sequencing with deadline problem in which each job has integer
//deadline and unit processing time.

#include <stdio.h>
#include <stdlib.h>

// Structure to represent a job
struct Job {
    char id;     // Job ID
    int deadline;
    int profit;
};

// Comparison function for sorting jobs by profit (descending order)
int compare(const void* a, const void* b) {
    struct Job* job1 = (struct Job*)a;
    struct Job* job2 = (struct Job*)b;
    return job2->profit - job1->profit;
}

// Function to find maximum deadline
int findMaxDeadline(struct Job jobs[], int n) {
    int max = jobs[0].deadline;
    int i;
    for ( i = 1; i < n; i++)
        if (jobs[i].deadline > max)
            max = jobs[i].deadline;
    return max;
}

// Function to schedule jobs for maximum profit
void jobSequencing(struct Job jobs[], int n) {
    // Sort jobs in decreasing order of profit
    qsort(jobs, n, sizeof(struct Job), compare);

    int maxDeadline = findMaxDeadline(jobs, n);

    // Create slot array to store result (initialize as empty)
    int slot[maxDeadline + 1];
    char result[maxDeadline + 1];
int i;
    for ( i = 0; i <= maxDeadline; i++) {
        slot[i] = 0; // 0 = empty
        result[i] = '-';
    }

    int totalProfit = 0;

    // Iterate through all jobs
    int j;
    for (i = 0; i < n; i++) {
        // Find a free slot for this job (starting from its deadline)
        for ( j = jobs[i].deadline; j > 0; j--) {
            if (slot[j] == 0) {
                slot[j] = 1;
                result[j] = jobs[i].id;
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }

    // Print scheduled jobs
    printf("Scheduled Jobs: ");
    for (i = 1; i <= maxDeadline; i++) {
        if (result[i] != '-')
            printf("%c ", result[i]);
    }
    printf("\nTotal Profit: %d\n", totalProfit);
}

// Demo
int main() {
    struct Job jobs[] = {
        {'a', 2, 100},
        {'b', 1, 19},
        {'c', 2, 27},
        {'d', 1, 25},
        {'e', 3, 15}
    };

    int n = sizeof(jobs) / sizeof(jobs[0]);
    jobSequencing(jobs, n);

    return 0;
}

