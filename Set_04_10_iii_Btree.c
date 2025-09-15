#include <stdio.h>
#include <stdlib.h>

#define T 3   // Minimum degree (change as needed)

struct BTreeNode {
    int keys[2*T - 1];
    struct BTreeNode* children[2*T];
    int n;              // number of keys
    int leaf;           // is leaf (1) or not (0)
};

// Create new B-tree node
struct BTreeNode* createNode(int leaf) {
    struct BTreeNode* node = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    node->leaf = leaf;
    node->n = 0;
    for (int i = 0; i < 2*T; i++) node->children[i] = NULL;
    return node;
}

// Create tree
struct BTreeNode* createTree() {
    return createNode(1); // root as leaf
}

// Search key
struct BTreeNode* searchItem(struct BTreeNode* x, int k) {
    int i = 0;
    while (i < x->n && k > x->keys[i]) i++;
    if (i < x->n && k == x->keys[i]) return x;
    if (x->leaf) return NULL;
    return searchItem(x->children[i], k);
}

// Split full child
void splitChild(struct BTreeNode* x, int i) {
    struct BTreeNode* y = x->children[i];
    struct BTreeNode* z = createNode(y->leaf);
    z->n = T - 1;

    for (int j = 0; j < T - 1; j++)
        z->keys[j] = y->keys[j+T];

    if (!y->leaf)
        for (int j = 0; j < T; j++)
            z->children[j] = y->children[j+T];

    y->n = T - 1;

    for (int j = x->n; j >= i+1; j--)
        x->children[j+1] = x->children[j];

    x->children[i+1] = z;

    for (int j = x->n-1; j >= i; j--)
        x->keys[j+1] = x->keys[j];

    x->keys[i] = y->keys[T-1];
    x->n++;
}

// Insert non-full
void insertNonFull(struct BTreeNode* x, int k) {
    int i = x->n - 1;
    if (x->leaf) {
        while (i >= 0 && k < x->keys[i]) {
            x->keys[i+1] = x->keys[i];
            i--;
        }
        x->keys[i+1] = k;
        x->n++;
    } else {
        while (i >= 0 && k < x->keys[i]) i--;
        i++;
        if (x->children[i]->n == 2*T - 1) {
            splitChild(x, i);
            if (k > x->keys[i]) i++;
        }
        insertNonFull(x->children[i], k);
    }
}

// Insert
void insertItem(struct BTreeNode** root, int k) {
    struct BTreeNode* r = *root;
    if (r->n == 2*T - 1) {
        struct BTreeNode* s = createNode(0);
        *root = s;
        s->children[0] = r;
        splitChild(s, 0);
        insertNonFull(s, k);
    } else {
        insertNonFull(r, k);
    }
}

// Get predecessor
int getPred(struct BTreeNode* x) {
    while (!x->leaf) x = x->children[x->n];
    return x->keys[x->n - 1];
}

// Get successor
int getSucc(struct BTreeNode* x) {
    while (!x->leaf) x = x->children[0];
    return x->keys[0];
}

// Merge children
void merge(struct BTreeNode* x, int idx) {
    struct BTreeNode *c1 = x->children[idx];
    struct BTreeNode *c2 = x->children[idx+1];

    c1->keys[T-1] = x->keys[idx];
    for (int i = 0; i < c2->n; i++)
        c1->keys[i+T] = c2->keys[i];
    if (!c1->leaf)
        for (int i = 0; i <= c2->n; i++)
            c1->children[i+T] = c2->children[i];

    for (int i = idx+1; i < x->n; i++)
        x->keys[i-1] = x->keys[i];
    for (int i = idx+2; i <= x->n; i++)
        x->children[i-1] = x->children[i];

    c1->n += c2->n + 1;
    x->n--;

    free(c2);
}

// Borrow from previous
void borrowFromPrev(struct BTreeNode* x, int idx) {
    struct BTreeNode* child = x->children[idx];
    struct BTreeNode* sibling = x->children[idx-1];

    for (int i = child->n-1; i >= 0; i--)
        child->keys[i+1] = child->keys[i];

    if (!child->leaf)
        for (int i = child->n; i >= 0; i--)
            child->children[i+1] = child->children[i];

    child->keys[0] = x->keys[idx-1];
    if (!child->leaf)
        child->children[0] = sibling->children[sibling->n];

    x->keys[idx-1] = sibling->keys[sibling->n - 1];
    child->n += 1;
    sibling->n -= 1;
}

// Borrow from next
void borrowFromNext(struct BTreeNode* x, int idx) {
    struct BTreeNode* child = x->children[idx];
    struct BTreeNode* sibling = x->children[idx+1];

    child->keys[child->n] = x->keys[idx];
    if (!child->leaf)
        child->children[child->n+1] = sibling->children[0];

    x->keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->n; i++)
        sibling->keys[i-1] = sibling->keys[i];
    if (!sibling->leaf)
        for (int i = 1; i <= sibling->n; i++)
            sibling->children[i-1] = sibling->children[i];

    child->n += 1;
    sibling->n -= 1;
}

// Fill child
void fill(struct BTreeNode* x, int idx) {
    if (idx != 0 && x->children[idx-1]->n >= T)
        borrowFromPrev(x, idx);
    else if (idx != x->n && x->children[idx+1]->n >= T)
        borrowFromNext(x, idx);
    else {
        if (idx != x->n) merge(x, idx);
        else merge(x, idx-1);
    }
}

// Delete from node
void deleteFromNode(struct BTreeNode* x, int k);

void deleteItem(struct BTreeNode** root, int k) {
    if (*root == NULL) return;
    deleteFromNode(*root, k);
    if ((*root)->n == 0) {
        struct BTreeNode* tmp = *root;
        if ((*root)->leaf) *root = NULL;
        else *root = (*root)->children[0];
        free(tmp);
    }
}

void deleteFromNode(struct BTreeNode* x, int k) {
    int idx = 0;
    while (idx < x->n && x->keys[idx] < k) idx++;

    if (idx < x->n && x->keys[idx] == k) {
        if (x->leaf) {
            for (int i = idx+1; i < x->n; i++)
                x->keys[i-1] = x->keys[i];
            x->n--;
        } else {
            if (x->children[idx]->n >= T) {
                int pred = getPred(x->children[idx]);
                x->keys[idx] = pred;
                deleteFromNode(x->children[idx], pred);
            } else if (x->children[idx+1]->n >= T) {
                int succ = getSucc(x->children[idx+1]);
                x->keys[idx] = succ;
                deleteFromNode(x->children[idx+1], succ);
            } else {
                merge(x, idx);
                deleteFromNode(x->children[idx], k);
            }
        }
    } else {
        if (x->leaf) return;
        int flag = (idx == x->n);
        if (x->children[idx]->n < T) fill(x, idx);
        if (flag && idx > x->n)
            deleteFromNode(x->children[idx-1], k);
        else
            deleteFromNode(x->children[idx], k);
    }
}

// Delete tree (free memory)
void deleteTree(struct BTreeNode* root) {
    if (root == NULL) return;
    if (!root->leaf)
        for (int i = 0; i <= root->n; i++)
            deleteTree(root->children[i]);
    free(root);
}

// Traversal for debugging
void traverse(struct BTreeNode* root) {
    if (root == NULL) return;
    for (int i = 0; i < root->n; i++) {
        if (!root->leaf) traverse(root->children[i]);
        printf("%d ", root->keys[i]);
    }
    if (!root->leaf) traverse(root->children[root->n]);
}

int main() {
    struct BTreeNode* root = createTree();

    insertItem(&root, 10);
    insertItem(&root, 20);
    insertItem(&root, 5);
    insertItem(&root, 6);
    insertItem(&root, 12);
    insertItem(&root, 30);
    insertItem(&root, 7);
    insertItem(&root, 17);

    printf("B-Tree traversal: ");
    traverse(root);
    printf("\n");

    deleteItem(&root, 6);
    printf("After deleting 6: ");
    traverse(root);
    printf("\n");

    struct BTreeNode* found = searchItem(root, 17);
    printf(found ? "Found 17\n" : "17 not found\n");

    deleteTree(root);
    return 0;
}

