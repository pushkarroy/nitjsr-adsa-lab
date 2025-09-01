#include <stdio.h>
#include <string.h>

// Function to get maximum value
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

// Counting Sort
void countingSort(int arr[], int n) {
    int max = getMax(arr, n);
    int count[max + 1];
    int output[n];

    // Initialize count array
    memset(count, 0, sizeof(count));

    // Store count of each element
    for (int i = 0; i < n; i++)
        count[arr[i]]++;

    // Change count[i] so that count[i] contains
    // the actual position of this element in output[]
    for (int i = 1; i <= max; i++)
        count[i] += count[i - 1];

    // Build the output array (stable sort)
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // Copy sorted array back to arr
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

// Print array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Driver Code
int main() {
    int arr[] = {4, 2, 2, 8, 3, 3, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    printArray(arr, n);

    countingSort(arr, n);

    printf("Sorted array: ");
    printArray(arr, n);

    return 0;
}

