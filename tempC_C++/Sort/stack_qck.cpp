#include <iostream>
#include <stack>

// 使用栈来模拟递归调用
void swap(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[low];
    int left = low;
    int right = high;
    
    while (left < right)
    {
        while (left < right && pivot < arr[high]) --high;
        arr[low] = arr[high];
        while (left < right && arr[low] < pivot) ++low;
        arr[high] = arr[low];
    }
    arr[low] = pivot;
    return low;
}

void qckSort_Iterative(int arr[], int low, int high)
{
    if (low >= high) return;

    std::stack<int> stack;
    stack.push(low);
    stack.push(high);
    
    while (!stack.empty())
    {
        high = stack.top(); stack.pop();
        low = stack.top(); stack.pop();
        
        int p = partition(arr, low, high);
        
        if (p - 1 > low)
        {
            stack.push(low);
            stack.push(p - 1);
        }

        if (p + 1 < high)
        {
            stack.push(p + 1);
            stack.push(high);
        }
    }
}

void prt_arr(int arr[], int size)
{
    for(int i = 0; i < size; i++)
    {
        if(i != size - 1)
            std::cout << arr[i] << " ";
        else 
            std::cout << arr[i] << ".";
    }
    std::cout << std::endl;
}

int main()
{
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    qckSort_Iterative(arr,0,n - 1);
    prt_arr(arr,n);
    return 0;
}
