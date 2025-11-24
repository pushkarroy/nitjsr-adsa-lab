#include <stdio.h>
#include <stdbool.h>

#define MAX 20

int graph[MAX][MAX];
int n, e, m;
int clique[MAX];

bool isClique(int size) {
	int i,j;
    for ( i = 0; i < size; i++) {
        for (j = i + 1; j < size; j++) {
            if (graph[clique[i]][clique[j]] == 0)
                return false;
        }
    }
    return true;
}

bool findClique(int start, int size, int depth) {
    if (depth == m) return isClique(m);
int i;
    for (i = start; i < n; i++) {
        clique[depth] = i;
        if (findClique(i + 1, size, depth + 1))
            return true;
    }
    return false;
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

    printf("Enter clique size m: ");
    scanf("%d", &m);

    if (findClique(0, n, 0))
        printf("Graph contains a clique of size %d\n", m);
    else
        printf("Graph does NOT contain a clique of size %d\n", m);

    return 0;
}

