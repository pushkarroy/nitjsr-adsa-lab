#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 3  // Max keys in a node
#define MIN (MAX/2)

typedef struct BPlusNode {
    int keys[MAX + 1], count;
    struct BPlusNode *child[MAX + 2];
    bool leaf;
} BPlusNode;

BPlusNode* root = NULL;

// Utility: Create a new node
BPlusNode* createNode(bool leaf) {
    BPlusNode* node = (BPlusNode*)malloc(sizeof(BPlusNode));
    node->count = 0;
    node->leaf = leaf;
    for (int i = 0; i < MAX+2; i++)
        node->child[i] = NULL;
    return node;
}

// Split the child y of node x at index i
void splitChild(BPlusNode* x, int i) {
    BPlusNode* y = x->child[i];
    BPlusNode* z = createNode(y->leaf);

    z->count = MIN;
    for (int j = 0; j < MIN; j++)
        z->keys[j] = y->keys[j+MIN+1];

    if (!y->leaf) {
        for (int j = 0; j <= MIN; j++)
            z->child[j] = y->child[j+MIN+1];
    }

    y->count = MIN;

    for (int j = x->count; j >= i+1; j--)
        x->child[j+1] = x->child[j];

    x->child[i+1] = z;

    for (int j = x->count-1; j >= i; j--)
        x->keys[j+1] = x->keys[j];

    x->keys[i] = y->keys[MIN];
    x->count++;
}

// Insert into a non-full node
void insertNonFull(BPlusNode* x, int k) {
    int i = x->count - 1;
    if (x->leaf) {
        while (i >= 0 && k < x->keys[i]) {
            x->keys[i+1] = x->keys[i];
            i--;
        }
        x->keys[i+1] = k;
        x->count++;
    } else {
        while (i >= 0 && k < x->keys[i])
            i--;
        i++;
        if (x->child[i]->count == MAX) {
            splitChild(x, i);
            if (k > x->keys[i]) i++;
        }
        insertNonFull(x->child[i], k);
    }
}

// Public insertItem()
void insertItem(int k) {
    if (root == NULL) {
        root = createNode(true);
        root->keys[0] = k;
        root->count = 1;
        return;
    }
    if (root->count == MAX) {
        BPlusNode* s = createNode(false);
        s->child[0] = root;
        splitChild(s, 0);
        int i = 0;
        if (k > s->keys[0]) i++;
        insertNonFull(s->child[i], k);
        root = s;
    } else {
        insertNonFull(root, k);
    }
}

// Search
bool searchItem(BPlusNode* x, int k) {
    int i = 0;
    while (i < x->count && k > x->keys[i]) i++;
    if (i < x->count && k == x->keys[i]) return true;
    if (x->leaf) return false;
    return searchItem(x->child[i], k);
}

// Delete (simplified: only from leaf for demonstration)
bool deleteItem(BPlusNode* x, int k) {
    if (!x) return false;
    int i = 0;
    while (i < x->count && k > x->keys[i]) i++;
    if (i < x->count && k == x->keys[i]) {
        if (x->leaf) {
            for (int j = i; j < x->count-1; j++)
                x->keys[j] = x->keys[j+1];
            x->count--;
            return true;
        } else {
            printf("Deletion from internal nodes is not implemented here.\n");
            return false;
        }
    } else if (!x->leaf) {
        return deleteItem(x->child[i], k);
    }
    return false;
}

// Delete entire tree
void deleteTree(BPlusNode* x) {
    if (!x) return;
    if (!x->leaf)
        for (int i = 0; i <= x->count; i++)
            deleteTree(x->child[i]);
    free(x);
}

// Print tree (for testing)
void printTree(BPlusNode* x, int level) {
    if (!x) return;
    for (int i = 0; i < level; i++) printf("  ");
    for (int i = 0; i < x->count; i++) printf("%d ", x->keys[i]);
    printf("\n");
    if (!x->leaf)
        for (int i = 0; i <= x->count; i++)
            printTree(x->child[i], level+1);
}

// Demo
int main() {
    int keys[] = {10, 20, 5, 6, 12, 30, 7, 17};
    for (int i = 0; i < 8; i++) insertItem(keys[i]);

    printf("B+ Tree Structure:\n");
    printTree(root, 0);

    printf("\nSearch 6: %s\n", searchItem(root, 6) ? "Found" : "Not Found");
    printf("Delete 6: %s\n", deleteItem(root, 6) ? "Deleted" : "Not Found");

    printf("\nAfter deletion:\n");
    printTree(root, 0);

    deleteTree(root);
    root = NULL;
    return 0;
}

