//Implement the coin changing problem using the greedy method.

#include <stdio.h>

// Function to find minimum number of coins using Greedy
void coinChange(int coins[], int n, int amount) {
    printf("Coins used to make amount %d:\n", amount);
int i;
    for ( i = 0; i < n; i++) {
        while (amount >= coins[i]) {
            amount -= coins[i];
            printf("%d ", coins[i]);
        }
    }

    printf("\n");
}
// Demo
int main() {
    // Example coin system (like Indian Rupees)
    int coins[] = {100, 50, 20, 10, 5, 2, 1};
    int n = sizeof(coins) / sizeof(coins[0]);

    int amount = 93;
    coinChange(coins, n, amount);

    return 0;
}

