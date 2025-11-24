#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <math.h>

#define MAXN 20    // restrict to ~20 because of 2^n states
#define INF 1000000000

int n;
int dist[MAXN][MAXN];
int dp[1<<MAXN][MAXN];

// DP function for TSP
int tsp(int mask, int pos) {
    if (mask == (1<<n) - 1) {
        return dist[pos][0]; // return to starting city
    }
    if (dp[mask][pos] != -1) return dp[mask][pos];

    int ans = INF;
    int city;
    for ( city = 0; city < n; city++) {
        if ((mask & (1<<city)) == 0) { // if city not visited
            int newAns = dist[pos][city] + tsp(mask | (1<<city), city);
            if (newAns < ans) ans = newAns;
        }
    }
    return dp[mask][pos] = ans;
}

int main() {
    printf("Enter number of cities: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix of distances:\n");
    int i,j;
    for ( i=0; i<n; i++)
        for ( j=0; j<n; j++)
            scanf("%d", &dist[i][j]);

    // initialize dp
    for ( i=0; i<(1<<n); i++)
        for ( j=0; j<n; j++)
            dp[i][j] = -1;

    clock_t start = clock();
    int result = tsp(1, 0); // start from city 0 with mask=1
    clock_t end = clock();

    double time_taken = (double)(end - start)/CLOCKS_PER_SEC;

    printf("Minimum travelling cost = %d\n", result);
    printf("Execution time = %f seconds\n", time_taken);

    return 0;
}

