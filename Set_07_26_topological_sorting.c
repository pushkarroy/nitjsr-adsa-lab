#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int graph[MAX][MAX];   // adjacency matrix
int visited[MAX];
int stack[MAX];
int top = -1;
int n;  // number of vertices

// Push onto stack
void push(int v) {
    stack[++top] = v;
}

// DFS for topological sort
void dfs(int v) {
    visited[v] = 1;
    int i;
    for ( i = 0; i < n; i++) {
        if (graph[v][i] && !visited[i]) {
            dfs(i);
        }
    }
    push(v);  // push after visiting all neighbors
}

// Perform topological sort
void topologicalSort() {
	int i;
    for (i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    printf("Topological Order: ");
    while (top != -1) {
        printf("%d ", stack[top--]);
    }
    printf("\n");
}

int main() {
    int e;
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &e);

    // initialize graph
    int i,j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            graph[i][j] = 0;

    printf("Enter edges (u v) meaning u -> v:\n");
    for ( i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;  // directed edge
    }

    topologicalSort();

    return 0;
}

