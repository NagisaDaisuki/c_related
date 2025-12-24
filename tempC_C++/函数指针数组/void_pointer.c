// void* 通用指针可以指向任何类型的数据，是C语言中实现
// 泛型(Genericity)的基础
// 强制类型转换：void*可以无需显式转换就被赋给任何数据指针类型，
// 反之亦然（尽管解引用前必须转换）

// malloc就是一个使用void*的典型例子，malloc分配好的内存返回值是
// 一个void*类型，所以通常会在malloc前加上一个类型强制转换，
// 不过大部分情况在C99后不加也没问题，只要用于接收的类型没问题就行

// 统一签名：使用void*作为参数和返回值，可以创建一个通用的函数签名，
// 让任何处理不同数据类型的函数都能符合这个签名

/*
 *  通用处理函数表(Command Dispatch Table)
 * */

#include <stdio.h>
#include <stdlib.h>

// 1. 定义通用签名
typedef void *(*GenericHandler)(void *input_data);

// 2. 定义处理函数
// 每个处理函数内部都需要进行强制类型转换来操作实际的数据
typedef struct {
  int id;
  int value;
} ItemData;

// 处理函数A：接收 int* ，返回 float*
void *process_int_to_float(void *input_data) {
  int *input_int = (int *)input_data;

  // 假设进行一些复杂的计算...
  float *result = (float *)malloc(sizeof(float));
  if (result == NULL) {
    perror("failed to allocate memory for float.");
    return NULL;
  }
  *result = (float)(*input_int) * 3.14f;

  // 返回结果指针
  return (void *)result;
}

// 处理函数B：接收 ItemData*， 返回 int*
void *process_struct_to_int(void *input_data) {
  ItemData *item = (ItemData *)input_data;

  // 假设进行一些复杂的计算
  int *result = (int *)malloc(sizeof(int));
  if (result == NULL) {
    perror("failed to allocate memory for int.");
    return NULL;
  }
  *result = item->id + item->value;

  // 返回结果指针
  return (void *)result;
}

// 3. 构建通用转换表
GenericHandler command_table[] = {
    process_int_to_float,
    process_struct_to_int,
};

// 4. 使用 和 类型转换
// 在使用时，你需要知道每个函数的预期输入和输出类型，并执行相应的转换和内存管理。
int main(void) {
  int input_a = 10;
  ItemData input_b = {5, 20};
  void *result_ptr = NULL;

  result_ptr = command_table[0]((void *)&input_a);

  if (result_ptr != NULL) {
    // 必须将 void* 转换回 float* 才能安全解引用
    float final_float = *(float *)result_ptr;
    printf("Result 0 (float): %.2f\n", final_float);
    free(result_ptr); // 释放处理函数内部 malloc 的内存
  }
  result_ptr = command_table[1]((void *)&input_b);

  if (result_ptr != NULL) {
    // 必须将 void* 转换回 int* 才能安全解引用
    int final_int = *(int *)result_ptr;
    printf("Result 1 (int): %d\n", final_int);
    free(result_ptr); // 释放处理函数内部 malloc 的内存
  }
  return 0;
}
