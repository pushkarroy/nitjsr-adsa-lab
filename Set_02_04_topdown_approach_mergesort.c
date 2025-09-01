//Implement merge sort without using recursion. You may use a stack data structure in order to keep track
//of dividing and conquering the task. This will be a top-down approach of solving the problem.

#include <stdio.h>
#include <stdlib.h>

// A structure to represent subarray bounds
typedef struct {
    int left, right;
} StackNode;

// Function to merge two halves
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

// Iterative Merge Sort using explicit stack
void mergeSortIterative(int arr[], int n) {
    StackNode *stack = (StackNode*)malloc(n * sizeof(StackNode));
    int top = -1;

    // Push initial range (0..n-1)
    stack[++top] = (StackNode){0, n - 1};

    // Array to mark processed merges
    int *processed = (int*)calloc(n, sizeof(int));

    while (top >= 0) {
        StackNode node = stack[top--];
        int l = node.left, r = node.right;

        if (l >= r) continue;

        int m = (l + r) / 2;

        if (!processed[l]) {
            // First time seeing this range, push again after children
            stack[++top] = (StackNode){l, r};   // push parent again
            stack[++top] = (StackNode){m + 1, r}; // right child
            stack[++top] = (StackNode){l, m};     // left child
            processed[l] = 1;
        } else {
            // Already divided, now merge
            merge(arr, l, m, r);
        }
    }

    free(stack);
    free(processed);
}

// Utility function to print array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Driver code
int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    printArray(arr, n);

    mergeSortIterative(arr, n);

    printf("Sorted array:\n");
    printArray(arr, n);

    return 0;
}

