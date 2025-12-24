#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>

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
void _sort(T vOrA, int n)
{

}

int main()
{
    std::vector<int> vec1 = {1,3,5,7,9,2,4,6,8,10};
    int arr1[10] = {1,3,5,7,9,2,4,6,8,10};
    //uint8_t vec_size = vec1.size();
    uint8_t arr_size = sizeof(arr1) / sizeof(arr1[0]);
    _sort(arr1,arr_size);
    print(arr1,arr_size);
    
    return 0;
}
