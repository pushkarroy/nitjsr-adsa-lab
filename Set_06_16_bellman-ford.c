#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Bellman-Ford Algorithm
void BellmanFord(struct Edge edges[], int V, int E, int src) {
    int dist[V];

    // Step 1: Initialize distances from src to all other vertices as INFINITE
    int i;
    for ( i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;

    // Step 2: Relax all edges |V| - 1 times
    
    for ( i = 1; i <= V - 1; i++) {
    	int j;
        for (j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    // Step 3: Check for negative-weight cycles
    int j;
    for ( j = 0; j < E; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int weight = edges[j].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            printf("Graph contains negative weight cycle!\n");
            return;
        }
    }

    // Print the shortest distances
    printf("Vertex \t Distance from Source\n");
    ;
    for (i = 0; i < V; i++) {
        if (dist[i] == INT_MAX)
            printf("%d \t\t INF\n", i);
        else
            printf("%d \t\t %d\n", i, dist[i]);
    }
}

// Driver code
int main() {
    int V = 5;  // Number of vertices
    int E = 8;  // Number of edges
    struct Edge edges[] = {
        {0, 1, -1},
        {0, 2, 4},
        {1, 2, 3},
        {1, 3, 2},
        {1, 4, 2},
        {3, 2, 5},
        {3, 1, 1},
        {4, 3, -3}
    };

    BellmanFord(edges, V, E, 0);

    return 0;
}

