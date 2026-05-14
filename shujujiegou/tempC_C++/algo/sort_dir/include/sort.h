#ifndef SORT_H
#define SORT_H

// SWAP macro
#define SWAP(S1, S2, TYPE)                                                     \
  do {                                                                         \
    TYPE __TEMP = *(TYPE *)(S1);                                               \
    *(TYPE *)(S1) = *(TYPE *)(S2);                                             \
    *(TYPE *)(S2) = __TEMP;                                                    \
  } while (0)

/**
 * @brief Sorts an array of integers using the bubble sort algorithm.
 *
 * @param arr The array to be sorted.
 * @param n The number of elements in the array.
 */
void bubble_sort(int arr[], int n);
void insertion_sort(int arr[], int n);
void selection_sort(int arr[], int n);
void shell_sort(int arr[], int n);
void merge_sort(int arr[], int n);
void quick_sort(int arr[], int n);
void counting_sort(int arr[], int n);
void heap_sort(int arr[], int n);
void radix_sort(int arr[], int n);
void bucket_sort(int arr[], int n);
#endif // SORT_H
