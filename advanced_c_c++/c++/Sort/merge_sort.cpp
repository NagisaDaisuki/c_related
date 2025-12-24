#include <iostream>
#include <cstdio>
#include <cstdlib>




/*
    迭代法
    原理如下(假设序列共有n个元素)：
        1.将序列每相邻的两个数字进行归并操作，形成ceil(n/2)个序列，
        排序后每个序列包含两/一个元素
        2.若此时序列数不是一个则将上述序列再次归并，形成ceil(n/4)个序列，每个序列包含四/三个元素
        3.重复步骤二，直到所有元素排序完毕，即序列数为1
*/

int min(int x, int y)
{
    return x < y ? x : y;
}

void print_arr(int *arr, int len)
{
    int i = 0;
    printf("The results of arr is: \n");
    while(i < len)
    {
        if(i == len - 1)
            printf("%d.",arr[i]);
        else 
            printf("%d ",arr[i]);
        i++;
    }
}

void merge_sort(int arr[], int len)
{
    int *a = arr;
    int *b = (int*)malloc(len * sizeof(int));
    int seg, start;
    for (seg = 1; seg < len;seg += seg)
    {
        for (start = 0; start < len; start += seg * 2)
        {
            int low = start, mid = min(start + seg, len), high = min(start + seg * 2, len);
            int k = low;
            int start1 = low, end1 = mid;
            int start2 = mid, end2 = high;
            while(start1 < end1 && start2 < end2)
                b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
            while(start1 < end1)
                b[k++] = a[start1++];
            while(start2 < end2)
                b[k++] = a[start2++];
        }
        int *temp = a;
        a = b;
        b = temp;
    }
    if(a != arr)
    {
        int i;
        for(i = 0; i < len; i++)
            b[i] = a[i];
        b = a;
    }
    free(b);
}

/*
    递归法
    1. 申请空间，使其大小为两个已排序序列之和，该空间用来存放合并后的序列
    2. 设定两个指针，最初位置分别为两个已经排序序列的起始位置
    3. 比较两个指针所指向的元素，选择相对小的元素放入到合并空间，并移动指到下一个位置
    4. 重复步骤3直到*某一指针到达序列尾*
    5. 将另一序列剩下的所有元素直接复制到合并序列尾
*/

// 分治-治
void merge_Sort_conquer(int *array, int left, int mid, int right, int *temp)
{
    // [left, mid] 和 [mid + 1, right]两个有序数组
    int i = left;
    int j = mid + 1;
    int index = 0;
    while (i <= mid && j <= right)
    {
        if(array[i] < array[j])
            temp[index++] = array[i++];
        else 
            temp[index++] = array[j++];
    }
    // 剩余元素直接放入temp
    while(i <= mid)
    {
        temp[index++] = array[i++];
    }
    while(j <= right)
    {
        temp[index++] = array[j++];
    }

    // 放回原数组
    index = 0;
    while (left <= right)
        array[left++] = temp[index++];
}


// 分治-分
void merge_sort_divide(int *array, int left, int right, int *temp)
{
    if(left < right)
    {
        int mid = left + (right - left) / 2;
        // left side merge sort
        merge_sort_divide(array, left, mid, temp);
        // right side merge sort
        merge_sort_divide(array, mid + 1, right, temp);
        // aggregate the two of list
        merge_Sort_conquer(array, left, mid, right, temp);
    }
}

void mergeSort(int *array, int size)
{
    int *temp = (int*)malloc(sizeof(int) * size);
    merge_sort_divide(array, 0, size - 1, temp);
}


int main(int argc, char *argv[])
{
    //printf("this is the file name: %s/n",argv[0]);
    //printf("and this is the first parameter: %s", argv[1]);
    int arr[10] = {1,3,5,7,9,2,4,6,8,10};
    int len1 = sizeof(arr) / sizeof(arr[0]);
    char judge = *(argv[1]); // 从终端获取
    if (judge == '1')
        merge_sort(arr,len1);
    else if (judge == '2')
        mergeSort(arr, len1);
    print_arr(arr,len1);
    return EXIT_SUCCESS;
}
