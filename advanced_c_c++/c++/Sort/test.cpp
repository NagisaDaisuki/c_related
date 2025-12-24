#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <algorithm>

// 普通的返回类型声明
void print_arr(int arr[], int len)
{
    std::cout << "The result of arr is: ";
    for(int i = 0; i < len; i++)
    {
        std::cout << arr[i] << " ";
    }
}

// C++ Version
template<typename T> // 整数或浮点数皆可使用，若要使用class时必须设定小于的运算子功能
auto merge_sort(T arr[], int len) -> void  
{
    T *a = arr;
    T *b = new T[len];
    for (int seg = 1; seg < len; seg += seg)
    {
        for (int start = 0; start < len; start += seg + seg)
        {
            int low = start,mid = std::min(start + seg, len), high = std::min(start + seg + seg, len);
            int k = low;
            int start1 = low, end1 = mid;
            int start2 = mid, end2 = high;
            while (start1 < end1 && start2 < end2)
                b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
            while (start1 < end1)
                b[k++] = a[start1++];
            while (start2 < end2)
                b[k++] = a[start2++];
        }
        T *temp = a;
        a = b;
        b = temp;
    }
    if (a != arr)
    {
        for(int i = 0; i < len; i++)
        {
            b[i] = a[i];
        }
        b = a;
    }
    delete[] b;
}

// 分治-治
template<typename T>
void merge_sort_conquer(T array[], int left, int mid, int right, T temp[])
{
    int i = left;
    int j = mid + 1;
    int index = 0;
    while (i <= mid && j <= right)
        temp[index++] = array[i] < array[j] ? array[i++] : array[j++];
    while (i <= mid)
        temp[index++] = array[i++];
    while (j <= right)
        temp[index++] = array[j++];

    index = 0;
    while (left <= right)
        array[index++] = temp[index++];
}


// 分治-分
template<typename T>
void merge_sort_divide(T array[], int left, int right,T temp[])
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        // left
        merge_sort_divide(array, left, mid, temp);
        // right
        merge_sort_divide(array, mid + 1, right, temp);
        // conquer
        merge_sort_conquer(array, left, mid, right, temp);   
    }
}


// 递归
template<typename T>
void mergeSort(T array[], int len)
{
    T *temp = new T[len];
    merge_sort_divide(array, 0, len - 1, temp);
    delete[] temp;
}

// 尾置返回类型(Trailing return type) C++11 , 需要在函数体前加上auto关键字
auto main() -> int {

    int arr[10] = {1,3,5,7,9,2,4,6,8,10};
    int len = sizeof(arr) / sizeof(arr[0]);
    mergeSort(arr,len);
    print_arr(arr,len);
    return 0;

}