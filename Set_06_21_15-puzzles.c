#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 4   // 4x4 Puzzle

// Directions for blank tile (up, down, left, right)
int row[] = { 1, 0, -1, 0 };
int col[] = { 0, -1, 0, 1 };

// Target (Goal) state
int final_state[N][N] = {
    {1,  2,  3,  4},
    {5,  6,  7,  8},
    {9,  10, 11, 12},
    {13, 14, 15, 0}
};

// Structure for puzzle node
typedef struct Node {
    int mat[N][N];   // Puzzle configuration
    int x, y;        // Blank tile coordinates
    int g, h, f;     // g=level, h=heuristic, f=g+h
    struct Node* parent;
} Node;

// Utility: create a new node
Node* newNode(int mat[N][N], int x, int y, int newX, int newY, int g, Node* parent) {
    Node* node = (Node*)malloc(sizeof(Node));

    // Copy data
    int i,j;
    for ( i = 0; i < N; i++)
        for ( j = 0; j < N; j++)
            node->mat[i][j] = mat[i][j];

    // Swap blank tile
    int temp = node->mat[x][y];
    node->mat[x][y] = node->mat[newX][newY];
    node->mat[newX][newY] = temp;

    node->x = newX;
    node->y = newY;
    node->g = g;
    node->parent = parent;
    return node;
}

// Heuristic: Manhattan Distance
int calculateH(int mat[N][N]) {
    int h = 0;int i,j;
    for ( i = 0; i < N; i++) {
        for ( j = 0; j < N; j++) {
            if (mat[i][j] != 0) {
                int targetX = (mat[i][j] - 1) / N;
                int targetY = (mat[i][j] - 1) % N;
                h += abs(i - targetX) + abs(j - targetY);
            }
        }
    }
    return h;
}

// Print puzzle state
void printMatrix(int mat[N][N]) {
	int i,j;
    for ( i = 0; i < N; i++) {
        for ( j = 0; j < N; j++) {
            if (mat[i][j] == 0) printf("   ");
            else printf("%2d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Min-Heap (Priority Queue) implementation
typedef struct {
    Node* arr[10000];
    int size;
} PriorityQueue;

void push(PriorityQueue* pq, Node* node) {
    pq->arr[pq->size++] = node;
    int i = pq->size - 1;
    while (i > 0 && pq->arr[i]->f < pq->arr[(i - 1) / 2]->f) {
        Node* temp = pq->arr[i];
        pq->arr[i] = pq->arr[(i - 1) / 2];
        pq->arr[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

Node* pop(PriorityQueue* pq) {
    if (pq->size <= 0) return NULL;
    Node* root = pq->arr[0];
    pq->arr[0] = pq->arr[--pq->size];
    int i = 0;

    while (2 * i + 1 < pq->size) {
        int smallest = i;
        int left = 2 * i + 1, right = 2 * i + 2;

        if (left < pq->size && pq->arr[left]->f < pq->arr[smallest]->f)
            smallest = left;
        if (right < pq->size && pq->arr[right]->f < pq->arr[smallest]->f)
            smallest = right;

        if (smallest != i) {
            Node* temp = pq->arr[i];
            pq->arr[i] = pq->arr[smallest];
            pq->arr[smallest] = temp;
            i = smallest;
        } else break;
    }
    return root;
}

// Check if puzzle reached final state
int isFinal(int mat[N][N]) {
	int i,j;
    for ( i = 0; i < N; i++)
        for ( j = 0; j < N; j++)
            if (mat[i][j] != final_state[i][j])
                return 0;
    return 1;
}

// Print path from root to solution
void printPath(Node* root) {
    if (root == NULL) return;
    printPath(root->parent);
    printMatrix(root->mat);
}

// Solve the 15-puzzle using Branch and Bound
void solve(int initial[N][N], int x, int y) {
    PriorityQueue pq;
    pq.size = 0;

    Node* root = newNode(initial, x, y, x, y, 0, NULL);
    root->h = calculateH(initial);
    root->f = root->g + root->h;
    push(&pq, root);

    while (pq.size > 0) {
        Node* min = pop(&pq);

        if (isFinal(min->mat)) {
            printf("Solution found!\n");
            printPath(min);
            return;
        }
int i;
        for (i = 0; i < 4; i++) {
            int newX = min->x + row[i];
            int newY = min->y + col[i];

            if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
                Node* child = newNode(min->mat, min->x, min->y, newX, newY, min->g + 1, min);
                child->h = calculateH(child->mat);
                child->f = child->g + child->h;
                push(&pq, child);
            }
        }
    }
    printf("No solution exists!\n");
}

// Driver program
int main() {
    int initial[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 0, 8},
        {9, 10, 7, 12},
        {13, 14, 11, 15}
    };

    // Blank tile coordinates
    int x = 1, y = 2;

    solve(initial, x, y);

    return 0;
}

