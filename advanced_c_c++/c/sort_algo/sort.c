// sort.c
#include "sort.h"
#include <stdio.h>
#include <stdlib.h>

// 内部辅助函数
static void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void printArray(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

// --- 1. 冒泡排序 ---
void bubbleSort(int arr[], int n) {
  int i, j;
  for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - 1 - i; j++) {
      if (arr[j] > arr[j + 1])
        swap(&arr[j], &arr[j + 1]);
    }
  }
}

// --- 2. 选择排序 ---
void selectionSort(int arr[], int n) {
  int i, j, min_idx;
  for (i = 0; i < n - 1; i++) {
    min_idx = i;
    for (j = i + 1; j < n; j++) {
      if (arr[min_idx] > arr[j])
        min_idx = j;
    }
    swap(&arr[min_idx], &arr[i]);
  }
}

// --- 3. 插入排序 ---
void insertionSort(int arr[], int n) {
  int i, j, key;
  for (i = 1; i < n; i++) {
    key = arr[i];
    for (j = i - 1; j >= 0 && arr[j] > key; j -= 1) {
      arr[j + 1] = arr[j];
    }
    arr[j + 1] = key;
  }
}

// --- 4. 希尔排序 ---
void shellSort(int arr[], int n) {
  for (int gap = n / 2; gap > 0; gap /= 2) {
    for (int i = gap; i < n; i++) {
      int temp = arr[i];
      int j;
      for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
        arr[j] = arr[j - gap];
      arr[j] = temp;
    }
  }
}

// --- 5. 归并排序 (含封装) ---
static void merge(int arr[], int l, int m, int r) {
  int n1 = m - l + 1, n2 = r - m;
  int L[n1], R[n2];
  for (int i = 0; i < n1; i++)
    L[i] = arr[l + i];
  for (int j = 0; j < n2; j++)
    R[j] = arr[m + 1 + j];
  int i = 0, j = 0, k = l;
  while (i < n1 && j < n2)
    arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
  while (i < n1)
    arr[k++] = L[i++];
  while (j < n2)
    arr[k++] = R[j++];
}
static void mergeSortRecursive(int arr[], int l, int r) {
  if (l < r) {
    int m = l + (r - l) / 2;
    mergeSortRecursive(arr, l, m);
    mergeSortRecursive(arr, m + 1, r);
    merge(arr, l, m, r);
  }
}
void mergeSort(int arr[], int n) { mergeSortRecursive(arr, 0, n - 1); }

// --- 6. 快速排序 (含封装) ---
static int partition(int arr[], int low, int high) {
  int pivot = arr[high];
  int i = (low - 1);
  for (int j = low; j < high; j++) {
    if (arr[j] < pivot) {
      i++;
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[i + 1], &arr[high]);
  return (i + 1);
}
static void quickSortRecursive(int arr[], int low, int high) {
  if (low < high) {
    int pi = partition(arr, low, high);
    quickSortRecursive(arr, low, pi - 1);
    quickSortRecursive(arr, pi + 1, high);
  }
}
void quickSort(int arr[], int n) { quickSortRecursive(arr, 0, n - 1); }

// --- 7. 堆排序 ---
static void heapify(int arr[], int n, int i) {
  int largest = i, l = 2 * i + 1, r = 2 * i + 2;
  if (l < n && arr[l] > arr[largest])
    largest = l;
  if (r < n && arr[r] > arr[largest])
    largest = r;
  if (largest != i) {
    swap(&arr[i], &arr[largest]);
    heapify(arr, n, largest);
  }
}
void heapSort(int arr[], int n) {
  for (int i = n / 2 - 1; i >= 0; i--)
    heapify(arr, n, i);
  for (int i = n - 1; i > 0; i--) {
    swap(&arr[0], &arr[i]);
    heapify(arr, i, 0);
  }
}

// --- 8. 计数排序 ---
void countingSort(int arr[], int n) {
  int max = arr[0];
  for (int i = 1; i < n; i++)
    if (arr[i] > max)
      max = arr[i];
  int *count = (int *)calloc(max + 1, sizeof(int));
  int *output = (int *)malloc(n * sizeof(int));
  for (int i = 0; i < n; i++)
    count[arr[i]]++;
  for (int i = 1; i <= max; i++)
    count[i] += count[i - 1];
  for (int i = n - 1; i >= 0; i--)
    output[--count[arr[i]]] = arr[i];
  for (int i = 0; i < n; i++)
    arr[i] = output[i];
  free(count);
  free(output);
}

// --- 9. 桶排序 (简化版: 0-99范围) ---
void bucketSort(int arr[], int n) {
  // 假设数据范围0-100，简单分10个桶
  int buckets[10][n + 1];
  int count[10] = {0};
  for (int i = 0; i < n; i++) {
    int idx = arr[i] / 10;
    if (idx > 9)
      idx = 9; // 越界保护
    buckets[idx][count[idx]++] = arr[i];
  }
  int k = 0;
  for (int i = 0; i < 10; i++) {
    // 桶内简单排序（插入）
    for (int j = 1; j < count[i]; j++) {
      int key = buckets[i][j], p = j - 1;
      while (p >= 0 && buckets[i][p] > key) {
        buckets[i][p + 1] = buckets[i][p];
        p--;
      }
      buckets[i][p + 1] = key;
    }
    for (int j = 0; j < count[i]; j++)
      arr[k++] = buckets[i][j];
  }
}

// --- 10. 基数排序 ---
static void countSortForRadix(int arr[], int n, int exp) {
  int output[n], count[10] = {0};
  for (int i = 0; i < n; i++)
    count[(arr[i] / exp) % 10]++;
  for (int i = 1; i < 10; i++)
    count[i] += count[i - 1];
  for (int i = n - 1; i >= 0; i--)
    output[--count[(arr[i] / exp) % 10]] = arr[i];
  for (int i = 0; i < n; i++)
    arr[i] = output[i];
}
void radixSort(int arr[], int n) {
  int max = arr[0];
  for (int i = 1; i < n; i++)
    if (arr[i] > max)
      max = arr[i];
  for (int exp = 1; max / exp > 0; exp *= 10)
    countSortForRadix(arr, n, exp);
}
