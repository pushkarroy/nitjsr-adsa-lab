#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int n; // number of vertices
int graph[MAX][MAX];
int visited[MAX];
int stack[MAX];
int stackPos;
int minCycle = MAX, maxCycle = -1;

void dfs(int start, int u) {
    visited[u] = 1;
    stack[stackPos++] = u;

    for (int v = 0; v < n; v++) {
        if (graph[u][v]) {
            if (!visited[v]) {
                dfs(start, v);
            } else {
                // if v is in the current stack, then we found a cycle
                for (int i = 0; i < stackPos; i++) {
                    if (stack[i] == v) {
                        int cycleLen = stackPos - i;
                        if (cycleLen > 1) {
                            if (cycleLen < minCycle) minCycle = cycleLen;
                            if (cycleLen > maxCycle) maxCycle = cycleLen;
                        }
                        break;
                    }
                }
            }
        }
    }

    visited[u] = 0;
    stackPos--;
}

int main() {
    int e;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &e);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    printf("Enter edges (u v):\n");
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = 1; // directed
        // For undirected, also add: graph[v][u] = 1;
    }

    for (int i = 0; i < n; i++) {
        stackPos = 0;
        dfs(i, i);
    }

    if (maxCycle == -1)
        printf("No cycles found.\n");
    else {
        printf("Smallest cycle length = %d\n", minCycle);
        printf("Largest cycle length = %d\n", maxCycle);
    }

    return 0;
}

