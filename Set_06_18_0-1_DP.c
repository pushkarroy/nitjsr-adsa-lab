#include <stdio.h>

// Function to return max of two numbers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Solves the 0/1 Knapsack problem using DP
int knapSack(int W, int wt[], int val[], int n) {
    int dp[n + 1][W + 1];

    // Build table dp[][] in bottom-up manner
    int i,w;
    for ( i = 0; i <= n; i++) {
        for ( w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (wt[i - 1] <= w)
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]],
                               dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    return dp[n][W]; // Maximum profit
}

int main() {
    int val[] = {60, 100, 120};   // values
    int wt[] = {10, 20, 30};      // weights
    int W = 50;                   // Capacity
    int n = sizeof(val) / sizeof(val[0]);

    printf("Maximum value in Knapsack = %d\n", knapSack(W, wt, val, n));
    return 0;
}

