#include <stdio.h>
#include <stdbool.h>

#define MAX 100

int graph[MAX][MAX];
int n, e;

bool isBipartite(int src) {
    int color[MAX];
    int i;
    for (i = 0; i < n; i++) color[i] = -1;

    color[src] = 0;
    int queue[MAX], front = 0, rear = 0;
    queue[rear++] = src;

    while (front < rear) {
        int u = queue[front++];
int v;
        for ( v = 0; v < n; v++) {
            if (graph[u][v] && color[v] == -1) {
                color[v] = 1 - color[u];
                queue[rear++] = v;
            } else if (graph[u][v] && color[v] == color[u]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    printf("Enter number of vertices (n) and edges (e): ");
    scanf("%d %d", &n, &e);
int i;
    for (i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = graph[v][u] = 1;
    }

    if (isBipartite(0))
        printf("Graph is Bipartite\n");
    else
        printf("Graph is NOT Bipartite\n");

    return 0;
}

