#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

/*
 *  快速排序，又称为分区交换排序(partition-exchange sort),简称[快排]
 *  
 *  快速排序的工作原理是通过分治的方式来将一个数组排序
 *  快速排序是一种不稳定的排序算法
 *  快速排序的最优时间复杂度和平均时间复杂度为O(nlogn),最坏时间复杂度为O(n2)
 *
 *  快速排序分为三个过程:
 *      1. 将数列划分为两部分(要求保证相对大小关系)
 *      2. 递归到两个子序列中分别进行快速排序
 *      3. 不用合并，因为此时数列已经完全有序
 *  * */

// 打印数组 使用尾后返回值类型C++11
template <typename T> 
auto prt_arr(T arr[],int len) -> void
{
    std::cout << "The result of 这个数组is: " << std::endl;
    /*for(T e : arr)
    {
        if(e != arr[len - 1])
            std::cout << e << " ";
        else 
            std::cout << e << ".";
    }*/ 

    
    for(int i = 0; i < len;i++)
    {
        if(i != len - 1)
            std::cout << arr[i] << " ";
        else 
            std::cout << arr[i] << ".";
    }
    
}


//              非递归实现
struct Range{
    int start, end;
    Range(int s = 0, int e = 0) { start = s, end = e; } 
};

template <typename T>
void quick_sort(T arr[], const int len)
{
    if (len <= 0) return; // 不满足排序条件的数组
    Range r[len]; // 创建一个Range类型的数组，个数为排序元素个数
    int p = 0;
    r[p++] = Range(0, len - 1);
    while (p)
    {
        Range range = r[--p];
        if (range.start >= range.end)
    }
}


/*              递归实现                                */
template <typename T>
int Partition(T A[], int low, int high)
{
    int pivot = A[low];
    while (low < high)
    {
        while (low < high && pivot <= A[high]) --high;
        A[low] = A[high];
        while (low < high && A[low] <= pivot) ++low;
        A[high] = A[low];
    }
    A[low] = pivot;
    return low;
}

template <typename T>
void QuickSort(T A[], int low, int high)
{
    if (low < high)
    {
        int pivot = Partition(A, low, high);
        QuickSort(A, low, pivot - 1);
        QuickSort(A, pivot + 1, high);
    }
}

template <typename T>
void QuickSort(T A[], int len)
{
    QuickSort(A, 0, len - 1);
}

int main(int argc, char *argv[])
{
    int arr[10] = {5,7,9,6,1,8,10,4,2,3};
    int len = sizeof(arr) / sizeof(arr[0]);
    QuickSort(arr,len);
    prt_arr(arr,len);
    return 0;
}
