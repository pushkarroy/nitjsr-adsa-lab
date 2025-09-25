#include <stdio.h>
#include <limits.h>

#define V 4          // Number of vertices
#define INF 99999    // A large value representing infinity

// Function to print the solution matrix
void printSolution(int dist[V][V]) {
	int i,j;
    printf("Shortest distances between every pair of vertices:\n");
    for ( i = 0; i < V; i++) {
        for ( j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf("%7d", dist[i][j]);
        }
        printf("\n");
    }
}

// Floyd–Warshall algorithm
void floydWarshall(int graph[V][V]) {
    int dist[V][V];
int i,j,k;
    // Step 1: Initialize the solution matrix same as input graph
    for ( i = 0; i < V; i++)
        for ( j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    // Step 2: Add all vertices one by one to the set of intermediate vertices
    for ( k = 0; k < V; k++) {
        // Pick all vertices as source one by one
        for ( i = 0; i < V; i++) {
            // Pick all vertices as destination for the above source
            for ( j = 0; j < V; j++) {
                // If vertex k is on the shortest path from i to j, then update
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    // Print the shortest distance matrix
    printSolution(dist);
}

// Driver code
int main() {
    // Example graph (directed)
    int graph[V][V] = {
        {0,   5,  INF, 10},
        {INF, 0,   3, INF},
        {INF, INF, 0,   1},
        {INF, INF, INF, 0}
    };

    floydWarshall(graph);
    return 0;
}

