#include <stdio.h>
#include <stdbool.h>

#define MAX 20

int graph[MAX][MAX];
int path[MAX];
int n;

bool isSafe(int v, int pos) {
    if (graph[path[pos - 1]][v] == 0)
        return false;
        int i;
    for ( i = 0; i < pos; i++)
        if (path[i] == v)
            return false;
    return true;
}

bool hamiltonianUtil(int pos) {
    if (pos == n) {
        if (graph[path[pos - 1]][path[0]] == 1)
            return true;
        return false;
    }
int v;
    for ( v = 1; v < n; v++) {
        if (isSafe(v, pos)) {
            path[pos] = v;
            if (hamiltonianUtil(pos + 1))
                return true;
            path[pos] = -1;
        }
    }
    return false;
}

bool hamiltonianCycle() {
	int i;
    for ( i = 0; i < n; i++)
        path[i] = -1;

    path[0] = 0;
    if (hamiltonianUtil(1) == false) {
        printf("No Hamiltonian Cycle found\n");
        return false;
    }

    printf("Hamiltonian Cycle exists: ");
    for ( i = 0; i < n; i++)
        printf("%d ", path[i]);
    printf("%d\n", path[0]);
    return true;
}

int main() {
    int e;
    printf("Enter number of vertices (n) and edges (e): ");
    scanf("%d %d", &n, &e);
int i;
    for ( i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = graph[v][u] = 1;
    }

    hamiltonianCycle();
    return 0;
}

