#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// ---------- Graph Structure ----------
struct Graph {
    int V;
    int adj[MAX][MAX]; // adjacency matrix for simplicity
};

// Add edge (directed)
void addEdge(struct Graph* g, int u, int v) {
    g->adj[u][v] = 1;
}

// ---------- Utility arrays ----------
int timeCounter;

// ---------- 1. Strongly Connected Components (Tarjan’s Algorithm) ----------
int disc[MAX], low[MAX], stackMember[MAX], st[MAX], top = -1;

void SCCUtil(struct Graph* g, int u) {
    disc[u] = low[u] = ++timeCounter;
    st[++top] = u;
    stackMember[u] = 1;
int v;
    for ( v = 0; v < g->V; v++) {
        if (g->adj[u][v]) {
            if (disc[v] == -1) {
                SCCUtil(g, v);
                low[u] = (low[u] < low[v]) ? low[u] : low[v];
            } else if (stackMember[v]) {
                low[u] = (low[u] < disc[v]) ? low[u] : disc[v];
            }
        }
    }

    if (low[u] == disc[u]) {
        printf("SCC: ");
        while (st[top] != u) {
            printf("%d ", st[top]);
            stackMember[st[top--]] = 0;
        }
        printf("%d\n", st[top]);
        stackMember[st[top--]] = 0;
    }
}

void findSCCs(struct Graph* g) {
	int i;
    for ( i = 0; i < g->V; i++) {
        disc[i] = -1;
        low[i] = -1;
        stackMember[i] = 0;
    }
    timeCounter = 0;

    for (i = 0; i < g->V; i++)
        if (disc[i] == -1)
            SCCUtil(g, i);
}

// ---------- 2. Articulation Points & Bridges ----------
int apDisc[MAX], apLow[MAX], apParent[MAX];
int articulation[MAX];

void APUtil(struct Graph* g, int u) {
    int children = 0;
    apDisc[u] = apLow[u] = ++timeCounter;
int v;
    for (v = 0; v < g->V; v++) {
        if (!g->adj[u][v] && !g->adj[v][u]) continue; // for undirected connectivity

        if (apDisc[v] == -1) {
            children++;
            apParent[v] = u;
            APUtil(g, v);

            apLow[u] = (apLow[u] < apLow[v]) ? apLow[u] : apLow[v];

            // Articulation point
            if (apParent[u] == -1 && children > 1)
                articulation[u] = 1;
            if (apParent[u] != -1 && apLow[v] >= apDisc[u])
                articulation[u] = 1;

            // Bridge
            if (apLow[v] > apDisc[u])
                printf("Bridge: %d -- %d\n", u, v);

        } else if (v != apParent[u]) {
            apLow[u] = (apLow[u] < apDisc[v]) ? apLow[u] : apDisc[v];
        }
    }
}

void findAPandBridges(struct Graph* g) {
	int i;
    for ( i = 0; i < g->V; i++) {
        apDisc[i] = -1;
        apLow[i] = -1;
        apParent[i] = -1;
        articulation[i] = 0;
    }
    timeCounter = 0;

    for ( i = 0; i < g->V; i++)
        if (apDisc[i] == -1)
            APUtil(g, i);

    printf("Articulation Points: ");
    for ( i = 0; i < g->V; i++)
        if (articulation[i]) printf("%d ", i);
    printf("\n");
}

// ---------- 3. Biconnected Components ----------
int bccDisc[MAX], bccLow[MAX], bccParent[MAX];
struct Edge { int u, v; } edgeStack[MAX];
int edgeTop = -1;

void pushEdge(int u, int v) {
    edgeStack[++edgeTop].u = u;
    edgeStack[edgeTop].v = v;
}

void popEdges(int u, int v) {
    printf("Biconnected Component: ");
    while (edgeTop >= 0) {
        struct Edge e = edgeStack[edgeTop--];
        printf("(%d-%d) ", e.u, e.v);
        if (e.u == u && e.v == v) break;
    }
    printf("\n");
}

void BCCUtil(struct Graph* g, int u) {
    int children = 0;
    bccDisc[u] = bccLow[u] = ++timeCounter;
int v;
    for (v = 0; v < g->V; v++) {
        if (!g->adj[u][v] && !g->adj[v][u]) continue;

        if (bccDisc[v] == -1) {
            children++;
            bccParent[v] = u;
            pushEdge(u, v);
            BCCUtil(g, v);

            bccLow[u] = (bccLow[u] < bccLow[v]) ? bccLow[u] : bccLow[v];

            if ((bccParent[u] == -1 && children > 1) ||
                (bccParent[u] != -1 && bccLow[v] >= bccDisc[u])) {
                popEdges(u, v);
            }
        } else if (v != bccParent[u] && bccDisc[v] < bccDisc[u]) {
            bccLow[u] = (bccLow[u] < bccDisc[v]) ? bccLow[u] : bccDisc[v];
            pushEdge(u, v);
        }
    }
}

void findBCCs(struct Graph* g) {
	int i;
    for ( i = 0; i < g->V; i++) {
        bccDisc[i] = -1;
        bccLow[i] = -1;
        bccParent[i] = -1;
    }
    timeCounter = 0;
    edgeTop = -1;

    for ( i = 0; i < g->V; i++) {
        if (bccDisc[i] == -1) {
            BCCUtil(g, i);
            if (edgeTop != -1) {
                popEdges(edgeStack[edgeTop].u, edgeStack[edgeTop].v);
            }
        }
    }
}

// ---------- Main ----------
int main() {
    struct Graph g;
    g.V = 5;
    memset(g.adj, 0, sizeof(g.adj));

    // Example graph (mixed use for testing)
    addEdge(&g, 0, 1);
    addEdge(&g, 1, 2);
    addEdge(&g, 2, 0);
    addEdge(&g, 1, 3);
    addEdge(&g, 3, 4);

    printf("Finding Strongly Connected Components:\n");
    findSCCs(&g);

    printf("\nFinding Articulation Points and Bridges:\n");
    findAPandBridges(&g);

    printf("\nFinding Biconnected Components:\n");
    findBCCs(&g);

    return 0;
}

