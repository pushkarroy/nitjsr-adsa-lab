#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int key;
    struct Node *left, *right;
    int height;
};

// Utility function to get height of a node
int height(struct Node *n) {
    return n ? n->height : 0;
}

// Utility function to get max of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Allocate a new node
struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

// Right rotate
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Left rotate
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Get balance factor
int getBalance(struct Node* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

// Insert key into AVL
struct Node* insertItem(struct Node* node, int key) {
    if (!node) return newNode(key);

    if (key < node->key)
        node->left = insertItem(node->left, key);
    else if (key > node->key)
        node->right = insertItem(node->right, key);
    else
        return node; // no duplicate keys

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    // Balance cases
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Get minimum value node
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current->left)
        current = current->left;
    return current;
}

// Delete key from AVL
struct Node* deleteItem(struct Node* root, int key) {
    if (!root) return root;

    if (key < root->key)
        root->left = deleteItem(root->left, key);
    else if (key > root->key)
        root->right = deleteItem(root->right, key);
    else {
        if (!root->left || !root->right) {
            struct Node* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            struct Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteItem(root->right, temp->key);
        }
    }

    if (!root) return root;

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Search key
struct Node* searchItem(struct Node* root, int key) {
    if (!root || root->key == key)
        return root;
    if (key < root->key)
        return searchItem(root->left, key);
    else
        return searchItem(root->right, key);
}

// Delete entire tree
void deleteTree(struct Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

// Inorder traversal for testing
void inorder(struct Node* root) {
    if (!root) return;
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

int main() {
    struct Node* root = NULL;  // createTree()

    root = insertItem(root, 10);
    root = insertItem(root, 20);
    root = insertItem(root, 30);
    root = insertItem(root, 40);
    root = insertItem(root, 50);
    root = insertItem(root, 25);

    printf("Inorder after insertion: ");
    inorder(root);
    printf("\n");

    root = deleteItem(root, 30);

    printf("Inorder after deletion of 30: ");
    inorder(root);
    printf("\n");

    int key = 25;
    struct Node* found = searchItem(root, key);
    printf(found ? "Found %d\n" : "%d not found\n", key);

    deleteTree(root);
    root = NULL;

    return 0;
}

