#include <stdio.h>
#include <stdlib.h>

void bucketSort(float arr[], int n) {
    int i, j, k;
    int bucketCount = n;
    float buckets[n][n];
    int bucketSizes[n];

    for (i = 0; i < n; i++) bucketSizes[i] = 0;

    // Scatter into buckets
    for (i = 0; i < n; i++) {
        int idx = arr[i] * bucketCount;
        buckets[idx][bucketSizes[idx]++] = arr[i];
    }

    // Sort each bucket (Insertion Sort)
    for (i = 0; i < bucketCount; i++) {
        for (j = 1; j < bucketSizes[i]; j++) {
            float key = buckets[i][j];
            k = j-1;
            while (k >= 0 && buckets[i][k] > key) {
                buckets[i][k+1] = buckets[i][k];
                k--;
            }
            buckets[i][k+1] = key;
        }
    }

    // Gather back
    k = 0;
    for (i = 0; i < bucketCount; i++)
        for (j = 0; j < bucketSizes[i]; j++)
            arr[k++] = buckets[i][j];
}

