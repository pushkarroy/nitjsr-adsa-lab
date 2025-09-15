#include <stdio.h>
#include <stdlib.h>

enum Color { RED, BLACK };

struct Node {
    int key;
    enum Color color;
    struct Node *left, *right, *parent;
};

struct Node *NIL; // Sentinel NIL node

// Utility: Create new node
struct Node* newNode(int key) {
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    n->key = key;
    n->color = RED;
    n->left = n->right = n->parent = NIL;
    return n;
}

// Left rotate
void leftRotate(struct Node **root, struct Node *x) {
    struct Node *y = x->right;
    x->right = y->left;
    if (y->left != NIL) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NIL) *root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// Right rotate
void rightRotate(struct Node **root, struct Node *x) {
    struct Node *y = x->left;
    x->left = y->right;
    if (y->right != NIL) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NIL) *root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
}

// Fix after insertion
void insertFixup(struct Node **root, struct Node *z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            struct Node *y = z->parent->parent->right;
            if (y->color == RED) { // Case 1
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) { // Case 2
                    z = z->parent;
                    leftRotate(root, z);
                }
                // Case 3
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        } else {
            struct Node *y = z->parent->parent->left;
            if (y->color == RED) { 
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

// Insert
void insertItem(struct Node **root, int key) {
    struct Node *z = newNode(key);
    struct Node *y = NIL;
    struct Node *x = *root;

    while (x != NIL) {
        y = x;
        if (z->key < x->key) x = x->left;
        else if (z->key > x->key) x = x->right;
        else { free(z); return; } // ignore duplicates
    }

    z->parent = y;
    if (y == NIL) *root = z;
    else if (z->key < y->key) y->left = z;
    else y->right = z;

    insertFixup(root, z);
}

// Transplant
void transplant(struct Node **root, struct Node *u, struct Node *v) {
    if (u->parent == NIL) *root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
}

// Minimum node
struct Node* treeMin(struct Node *x) {
    while (x->left != NIL) x = x->left;
    return x;
}

// Fix after deletion
void deleteFixup(struct Node **root, struct Node *x) {
    while (x != *root && x->color == BLACK) {
        if (x == x->parent->left) {
            struct Node *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(root, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(root, x->parent);
                x = *root;
            }
        } else {
            struct Node *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(root, x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(root, x->parent);
                x = *root;
            }
        }
    }
    x->color = BLACK;
}

// Delete
void deleteItem(struct Node **root, int key) {
    struct Node *z = *root;
    while (z != NIL && z->key != key)
        z = (key < z->key) ? z->left : z->right;
    if (z == NIL) return;

    struct Node *y = z;
    struct Node *x;
    enum Color yOriginal = y->color;

    if (z->left == NIL) {
        x = z->right;
        transplant(root, z, z->right);
    } else if (z->right == NIL) {
        x = z->left;
        transplant(root, z, z->left);
    } else {
        y = treeMin(z->right);
        yOriginal = y->color;
        x = y->right;
        if (y->parent == z) x->parent = y;
        else {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    free(z);
    if (yOriginal == BLACK) deleteFixup(root, x);
}

// Search
struct Node* searchItem(struct Node* root, int key) {
    while (root != NIL && root->key != key)
        root = (key < root->key) ? root->left : root->right;
    return root;
}

// Delete all nodes
void deleteTree(struct Node* root) {
    if (root == NIL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

// Inorder print
void inorder(struct Node *root) {
    if (root == NIL) return;
    inorder(root->left);
    printf("%d(%s) ", root->key, root->color == RED ? "R" : "B");
    inorder(root->right);
}

int main() {
    // Init NIL sentinel
    NIL = (struct Node*)malloc(sizeof(struct Node));
    NIL->color = BLACK;
    NIL->left = NIL->right = NIL->parent = NIL;

    struct Node *root = NIL; // createTree()

    insertItem(&root, 10);
    insertItem(&root, 20);
    insertItem(&root, 30);
    insertItem(&root, 15);
    insertItem(&root, 25);

    printf("Inorder after insertions: ");
    inorder(root);
    printf("\n");

    deleteItem(&root, 20);
    printf("Inorder after deleting 20: ");
    inorder(root);
    printf("\n");

    int key = 25;
    struct Node* found = searchItem(root, key);
    printf(found != NIL ? "Found %d\n" : "%d not found\n", key);

    deleteTree(root);
    free(NIL);
    return 0;
}

