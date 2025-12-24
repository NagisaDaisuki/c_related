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
void selection_sort(T vOrA, int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        int minIndex = i; 
        for(int j = i + 1; j < n; j++)
        {
            if(vOrA[minIndex] > vOrA[j])
            {
                minIndex = j;
            }
        }
        std::swap(vOrA[minIndex],vOrA[i]);
    }
}

template<typename T>
void selection_sort_r(T vOrA, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int maxIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if(vOrA[maxIndex] < vOrA[j])
            {
                maxIndex = j;
            }
        }
        std::swap(vOrA[maxIndex], vOrA[i]);
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
    selection_sort_r(arr1,arr_size);
    print(arr1,arr_size);
    
    // 获取程序结束的时间
    auto end = std::chrono::high_resolution_clock::now();
    // 计算运行时间
    std::chrono::duration<double> elapsed_time = end - start;
    std::cout << "\n代码运行时间" << elapsed_time.count() << "秒" << std::endl;

    return 0;
}
