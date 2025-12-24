#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>

template<typename T>
void print(T vOrA, int n)

    std::cout << "the sort of the result is: ";
    for (int i = 0; i < n; i++)
    {
        std::cout << vOrA[i] << " ";   
    }
}

template<typename T>
void bubble_sort(T vOrA, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if(vOrA[j] > vOrA[j + 1])
            {
                std::swap(vOrA[j], vOrA[j + 1]);
            }
        }
    }
}

int main(int argc, char** argv)
{
    std::cout << argv[0] << " running." << std::endl;
    int num = static_cast<int>(*argv[1]); 
    std::cout << "the num used entered is " << num << std::endl; 
    std::vector<int> vec1 = {1,3,5,7,9,2,4,6,8,10};
    int arr1[10] = {1,3,5,7,9,2,4,6,8,10};
    //uint8_t vec_size = vec1.size();
    uint8_t arr_size = sizeof(arr1) / sizeof(arr1[0]);
    bubble_sort(vec1,vec1.size());
    bubble_sort(arr1,arr_size);
    //bool judge = (num > 1);
#if 1
print(vec1,vec1.size());
#else
print(arr1,arr_size);
#endif
    return 0;
}
