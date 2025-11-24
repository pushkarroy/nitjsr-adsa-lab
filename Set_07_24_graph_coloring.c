#include <stdio.h>
#include <stdbool.h>

#define V 4   // Number of vertices in the graph

// Check if current color assignment is safe for vertex v
bool isSafe(int v, int graph[V][V], int color[], int c) {
	int i;
    for ( i = 0; i < V; i++) {
        if (graph[v][i] && color[i] == c) // adjacent has same color
            return false;
    }
    return true;
}

// Recursive utility to solve the coloring problem
bool graphColoringUtil(int graph[V][V], int m, int color[], int v) {
    if (v == V) // All vertices are assigned a color
        return true;
int c;
    for (c = 1; c <= m; c++) {
        if (isSafe(v, graph, color, c)) {
            color[v] = c;

            if (graphColoringUtil(graph, m, color, v + 1))
                return true;

            color[v] = 0; // Backtrack
        }
    }

    return false;
}

// Solve the m coloring problem
bool graphColoring(int graph[V][V], int m) {
    int color[V];
    int i;
    for (i = 0; i < V; i++)
        color[i] = 0;

    if (!graphColoringUtil(graph, m, color, 0)) {
        printf("Solution does not exist\n");
        return false;
    }

    // Print solution
    printf("Solution Exists: Assigned Colors:\n");
    for (i = 0; i < V; i++)
        printf("Vertex %d ---> Color %d\n", i, color[i]);

    return true;
}

// Demo
int main() {
    // Example graph (Adjacency Matrix)
    int graph[V][V] = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0}
    };

    int m = 3; // Number of colors
    graphColoring(graph, m);

    return 0;
}

