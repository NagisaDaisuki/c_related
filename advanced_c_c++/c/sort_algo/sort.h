#ifndef _SORT_H
#define _SORT_H

/*
 * auxiliary function
 * */
void printArray(int arr[], int size);
void choose(int arr[], int size);
/*
 * unify interface: all sort function packaged to void func(int arr[], int n)
 * format.
 * */

/*
 * Complexity: O(n * n)
 */
void bubbleSort(int arr[], int n);
void selectionSort(int arr[], int n);
void insertionSort(int arr[], int n);
/*
 * Complexity: fastest: O(nlogn) slowest: O(n * n)
 */
void shellSort(int arr[], int n);
void mergeSort(int arr[], int n);
void quickSort(int arr[], int n);
void heapSort(int arr[], int n);

/*
 * incompareable sort
 * Complexity: O(n + k), k means number of digits.
 */
void countingSort(int arr[], int n);
void bucketSort(int arr[], int n);
/*
 * incompareable sort
 * Complexity: O(n * k), k means number of digits.
 */
void radixSort(int arr[], int n);

#endif
