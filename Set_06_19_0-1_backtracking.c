#include <stdio.h>

int n;                 // number of items
int W;                 // knapsack capacity
int weights[100], values[100];
int maxProfit = 0;     // best solution found so far

// Utility function to find max
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Backtracking function
void knapsackBacktrack(int i, int currWeight, int currValue) {
    // Base case: all items considered
    if (i == n) {
        if (currValue > maxProfit)
            maxProfit = currValue;
        return;
    }

    // Option 1: Exclude item i
    knapsackBacktrack(i + 1, currWeight, currValue);

    // Option 2: Include item i (if it fits)
    if (currWeight + weights[i] <= W) {
        knapsackBacktrack(i + 1, currWeight + weights[i],
                          currValue + values[i]);
    }
}

int main() {
    // Example: 3 items
    n = 3;
    W = 50;
    int wt[] = {10, 20, 30};
    int val[] = {60, 100, 120};
int i;
    for ( i = 0; i < n; i++) {
        weights[i] = wt[i];
        values[i] = val[i];
    }

    knapsackBacktrack(0, 0, 0);

    printf("Maximum value in Knapsack = %d\n", maxProfit);

    return 0;
}

