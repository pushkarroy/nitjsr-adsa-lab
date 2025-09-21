#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 6  // Number of vertices (can be changed)

// Function to find the vertex with minimum key value not yet included in MST
int minKey(int key[], bool mstSet[]) {
    int min = INT_MAX, min_index = -1;
int v;
    for ( v = 0; v < V; v++)
        if (!mstSet[v] && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

// Print the constructed MST stored in parent[]
void printMST(int parent[], int graph[V][V]) {
    printf("Edge \tWeight\n");
    int i;
    for ( i = 1; i < V; i++)
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
}

// Function to construct and print MST using Prim's algorithm
void primMST(int graph[V][V]) {
    int parent[V];   // Array to store constructed MST
    int key[V];      // Key values used to pick minimum weight edge
    bool mstSet[V];  // To represent set of vertices included in MST

    // Initialize all keys as INFINITE
    int i;
    for ( i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[0] = 0;      // Start from the first vertex
    parent[0] = -1;  // First node is the root of MST
int count;
    for ( count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet);  // Pick the minimum key vertex
        mstSet[u] = true;
int v;
        for ( v = 0; v < V; v++)
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
    }

    printMST(parent, graph);
}

int main() {
    int graph[V][V] = {
        {0, 4, 0, 0, 0, 0}, 
        {4, 0, 8, 0, 0, 0},
        {0, 8, 0, 7, 0, 4},
        {0, 0, 7, 0, 9, 14},
        {0, 0, 0, 9, 0, 10},
        {0, 0, 4, 14, 10, 0}
    };

    primMST(graph);
    return 0;
}

