#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Stack structure for nodes
struct Stack {
    int top;
    int capacity;
    struct Node** array;
};

// Create a stack
struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (struct Node**)malloc(capacity * sizeof(struct Node*));
    return stack;
}

// Stack helper functions
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, struct Node* node) {
    stack->array[++stack->top] = node;
}

struct Node* pop(struct Stack* stack) {
    if (isEmpty(stack)) return NULL;
    return stack->array[stack->top--];
}

// Preorder traversal without recursion
void preorderIterative(struct Node* root) {
    if (root == NULL) return;

    // Stack size = number of nodes (worst case)
    struct Stack* stack = createStack(100); 

    push(stack, root);

    while (!isEmpty(stack)) {
        struct Node* curr = pop(stack);
        printf("%d ", curr->data);

        // Push right first so left is processed first
        if (curr->right) push(stack, curr->right);
        if (curr->left)  push(stack, curr->left);
    }
    free(stack->array);
    free(stack);
}

// Driver code
int main() {

    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    printf("Preorder Traversal: ");
    preorderIterative(root);

    return 0;
}

