#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Graph using adjacency list
struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    int V;
    struct Node* adj[MAX];
};

// Create a new node
struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Add edge (directed)
void addEdge(struct Graph* g, int u, int v) {
    struct Node* newNode = createNode(v);
    newNode->next = g->adj[u];
    g->adj[u] = newNode;
}

// DFS variables
int timeCounter = 0;
int color[MAX];    // 0=WHITE, 1=GRAY, 2=BLACK
int discover[MAX], finish[MAX];

// DFS visit
void DFS_Visit(struct Graph* g, int u) {
    color[u] = 1; // GRAY
    discover[u] = ++timeCounter;

    struct Node* temp = g->adj[u];
    while (temp) {
        int v = temp->vertex;

        if (color[v] == 0) {
            printf("Tree Edge: %d -> %d\n", u, v);
            DFS_Visit(g, v);
        } 
        else if (color[v] == 1) {
            printf("Back Edge: %d -> %d\n", u, v);
        } 
        else if (color[v] == 2) {
            if (discover[u] < discover[v])
                printf("Forward Edge: %d -> %d\n", u, v);
            else
                printf("Cross Edge: %d -> %d\n", u, v);
        }

        temp = temp->next;
    }

    color[u] = 2; // BLACK
    finish[u] = ++timeCounter;
}

// DFS driver
void DFS(struct Graph* g) {
    for (int i = 0; i < g->V; i++) {
        color[i] = 0;
        discover[i] = 0;
        finish[i] = 0;
    }
    timeCounter = 0;

    for (int i = 0; i < g->V; i++) {
        if (color[i] == 0)
            DFS_Visit(g, i);
    }
}

int main() {
    struct Graph g;
    g.V = 6;

    for (int i = 0; i < g.V; i++)
        g.adj[i] = NULL;

    // Example directed graph
    addEdge(&g, 0, 1);
    addEdge(&g, 0, 2);
    addEdge(&g, 1, 3);
    addEdge(&g, 2, 3);
    addEdge(&g, 3, 4);
    addEdge(&g, 4, 1);
    addEdge(&g, 4, 5);

    DFS(&g);

    return 0;
}

