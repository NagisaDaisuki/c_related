#include <stdio.h>
#include <stdlib.h>

// Function to sort arr[] of size n using bucket sort
void bucketSort(int arr[], int n) {
    // 1) Create n empty buckets
    int max_val = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    // Create a bucket array of pointers to arrays
    int** buckets = (int**)malloc(sizeof(int*) * 10);
    int* bucket_sizes = (int*)calloc(10, sizeof(int));

    for (int i = 0; i < 10; i++) {
        buckets[i] = (int*)malloc(sizeof(int) * n);
    }

    // 2) Put array elements in different buckets
    for (int i = 0; i < n; i++) {
        int bucket_index = 10 * arr[i] / (max_val + 1);
        buckets[bucket_index][bucket_sizes[bucket_index]++] = arr[i];
    }

    // 3) Sort individual buckets
    for (int i = 0; i < 10; i++) {
        if (bucket_sizes[i] > 1) {
            // Using insertion sort to sort individual buckets
            for (int j = 1; j < bucket_sizes[i]; j++) {
                int key = buckets[i][j];
                int k = j - 1;
                while (k >= 0 && buckets[i][k] > key) {
                    buckets[i][k + 1] = buckets[i][k];
                    k = k - 1;
                }
                buckets[i][k + 1] = key;
            }
        }
    }

    // 4) Concatenate all buckets into arr[]
    int index = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < bucket_sizes[i]; j++) {
            arr[index++] = buckets[i][j];
        }
    }

    // Free memory
    for (int i = 0; i < 10; i++) {
        free(buckets[i]);
    }
    free(buckets);
    free(bucket_sizes);
}

void printArray(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    bucketSort(arr, n);
    printf("Sorted array: \n");
    printArray(arr, n);
    return 0;
}
