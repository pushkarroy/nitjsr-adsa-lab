#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 6  // Number of vertices (you can change this)

// Find the vertex with minimum distance value from the set of vertices not yet processed
int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index = -1;
int v,i;
    for ( v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// Print the solution
void printSolution(int dist[]) {
    printf("Vertex \t Distance from Source\n");
    int i;
    for (i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Dijkstra's algorithm
void dijkstra(int graph[V][V], int src) {
    int dist[V];      // dist[i] will hold the shortest distance from src to i
    bool sptSet[V];   // sptSet[i] will be true if vertex i is included in shortest path tree

    // Initialize all distances as INFINITE and sptSet[] as false
    int i;
    for ( i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[src] = 0; // Distance from source to itself is 0

    // Find shortest path for all vertices
    int count;
    for ( count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet); // Pick the minimum distance vertex not yet processed
        sptSet[u] = true;
int v;
        for ( v = 0; v < V; v++)
            // Update dist[v] if not in sptSet, there is an edge from u to v, and total weight is smaller
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // Print the constructed distance array
    printSolution(dist);
}

// Demo
int main() {
    // Example graph represented as an adjacency matrix
    int graph[V][V] = {
        {0, 4, 0, 0, 0, 0},
        {4, 0, 8, 0, 0, 0},
        {0, 8, 0, 7, 0, 4},
        {0, 0, 7, 0, 9, 14},
        {0, 0, 0, 9, 0, 10},
        {0, 0, 4, 14, 10, 0}
    };

    dijkstra(graph, 0); // Find shortest paths from source vertex 0
    return 0;
}

