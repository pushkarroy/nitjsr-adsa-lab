#include <stdio.h>

void radixExchangeSort(int arr[], int left, int right, int bit) {
    if (left >= right || bit < 0) return;

    int i = left, j = right;
    while (i <= j) {
        while (i <= j && ((arr[i] >> bit) & 1) == 0) i++;
        while (i <= j && ((arr[j] >> bit) & 1) == 1) j--;
        if (i < j) {
            int temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
        }
    }
    radixExchangeSort(arr, left, j, bit-1);
    radixExchangeSort(arr, i, right, bit-1);
}

