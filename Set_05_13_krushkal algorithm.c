#include <stdio.h>
#include <stdlib.h>

#define V 6  // Number of vertices
#define E 9  // Number of edges

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Structure to represent a subset for Union-Find
struct Subset {
    int parent;
    int rank;
};

// Find set of an element i (uses path compression)
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Union of two sets x and y (by rank)
void Union(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Comparison function for qsort to sort edges by weight
int compareEdges(const void* a, const void* b) {
    struct Edge* e1 = (struct Edge*)a;
    struct Edge* e2 = (struct Edge*)b;
    return e1->weight - e2->weight;
}

// Function to construct MST using Kruskal's algorithm
void KruskalMST(struct Edge edges[]) {
    struct Edge result[V - 1];  // MST will have V-1 edges
    int e = 0;                  // Index for result[]
    int i = 0;                  // Index for sorted edges

    // Step 1: Sort all the edges in increasing order of weight
    qsort(edges, E, sizeof(edges[0]), compareEdges);

    // Allocate memory for creating V subsets
    struct Subset* subsets = (struct Subset*)malloc(V * sizeof(struct Subset));

    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Step 2: Pick the smallest edge. If it doesn't cause a cycle, include it.
    while (e < V - 1 && i < E) {
        struct Edge next_edge = edges[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // If including this edge does not cause cycle, include it in result
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
        // Else discard the edge
    }

    printf("Edges in the constructed MST:\n");
    int totalWeight = 0;
    for (i = 0; i < e; i++) {
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
        totalWeight += result[i].weight;
    }
    printf("Total Weight of MST: %d\n", totalWeight);

    free(subsets);
}

int main() {
    struct Edge edges[E] = {
        {0, 1, 4}, {0, 2, 4}, {1, 2, 2},
        {1, 0, 4}, {2, 0, 4}, {2, 3, 3},
        {2, 5, 2}, {2, 4, 4}, {3, 4, 3}
    };

    KruskalMST(edges);
    return 0;
}

