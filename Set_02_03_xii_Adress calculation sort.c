#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

void addressCalculationSort(int arr[], int n) {
    int bucket[SIZE][n];
    int bucketCount[SIZE] = {0};

    // Scatter into buckets
    for (int i = 0; i < n; i++) {
        int idx = arr[i] % SIZE;
        bucket[idx][bucketCount[idx]++] = arr[i];
    }

    // Sort each bucket (insertion sort)
    for (int b = 0; b < SIZE; b++) {
        for (int i = 1; i < bucketCount[b]; i++) {
            int key = bucket[b][i];
            int j = i-1;
            while (j >= 0 && bucket[b][j] > key) {
                bucket[b][j+1] = bucket[b][j];
                j--;
            }
            bucket[b][j+1] = key;
        }
    }

    // Gather back
    int k = 0;
    for (int b = 0; b < SIZE; b++)
        for (int i = 0; i < bucketCount[b]; i++)
            arr[k++] = bucket[b][i];
}

