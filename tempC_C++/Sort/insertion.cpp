#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>
#include <chrono>

template<typename T>
void print(T vOrA, int n)
{
    std::cout << "the sort of the result is: ";
    for (int i = 0; i < n; i++)
    {
        std::cout << vOrA[i] << " ";
    }
}

template<typename T>
void insertion_sort(T vOrA, int n)
{
    for(int i = 1; i < n; i++)
    {
        int key = vOrA[i];
        int j = i - 1;
        while(j >= 0 && vOrA[j] > key)
        {
            vOrA[j + 1] = vOrA[j;
            j = j - 1;
        }
        vOrA[j + 1] = key; // 因为出while循环后j == -1
    }
}

template<typename T>
void insertion_sort_t(T arr, int n)
{
    for(int i = 1; i < n;i++)
    {
        int key = arr[i];
        int j = i - 1;
        for(;j >= 0 && arr[j] > key;j = j - 1)
        {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = key;
    }
}

int main()
{
    // 获取程序开始的时间
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<int> vec1 = {1,3,5,7,9,2,4,6,8,10};
    int arr1[10] = {1,3,5,7,9,2,4,6,8,10};
    //uint8_t vec_size = vec1.size();
    uint8_t arr_size = sizeof(arr1) / sizeof(arr1[0]);
    insertion_sort_t(arr1,arr_size);
    print(arr1,arr_size);
    
    // 获取程序结束的时间
    auto end = std::chrono::high_resolution_clock::now();
    
    // 计算运行时间
    std::chrono::duration<double> elapsed_time = end - start;

    std::cout << "代码运行时间: " << elapsed_time.count() << "秒" << std::endl;

    return 0;
}
