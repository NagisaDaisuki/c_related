#include <memory.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MaxSize 50    // 408 标准宏定义
typedef int ElemType; // 抽象数据类型

typedef struct {
  ElemType data[MaxSize]; // 静态数组存放栈中元素
  int top;                // 栈顶指针
} SqStack;

// 1. 初始化
void InitStack(SqStack *S) { S->top = -1; }

// 2. 判空
bool StackEmpty(SqStack S) {
  return S.top == -1; // 不要用指针传递，只需传值即可判断
}

// 3. 进栈（Push）
bool Push(SqStack *S, ElemType x) {
  if (S->top == MaxSize - 1) // 栈满报错
    return false;
  S->top += 1;         // 指针加一上移
  S->data[S->top] = x; // 入栈
  return true;
}

// 4. 出栈 （Pop）：x必须传入指针，用于把弹出的数据带出来
bool Pop(SqStack *S, ElemType *x) {
  if (S->top == -1) // 栈空报错
    return false;
  *x = S->data[S->top]; // 先出栈
  S->top -= 1;          // 再指针减 1
  // *x = S->data[S->top--];
  return true;
}

// 5. 读栈顶元素(GetTop)
bool GetTop(SqStack S, ElemType *x) {
  if (S.top == -1)
    return false;
  *x = S.data[S.top];
  return true;
}

int main(void) {
  SqStack *S = (SqStack *)calloc(1, sizeof(SqStack));
  if (S == NULL) {
    perror("Failed to init SqStack.\n");
    return EXIT_FAILURE;
  }
  // 初始化栈
  InitStack(S);
  time_t t; // time.h
  // 初始化随机数发生器
  srand((unsigned)time(&t));

  size_t i;
  for (i = 0; i < MaxSize; i++) {
    Push(S, rand() % 101); // 　生成 0 - 100 的随机数
  }

  // char is_empty[50];
  // memset(is_empty, 0, sizeof(is_empty));
  // snprintf(is_empty,sizeof(is_empty),"%s",(StackEmpty(*S) ? "Yes" : "No"));

  int elem_ret = 0;
  fprintf(stdout, "if i push success ? %s\n",
          Push(S, 101) ? "Yes" : "No"); // 栈满无法push进去
  Pop(S, &elem_ret);
  fprintf(stdout, "the elem i pop is %d\n", elem_ret);
  fprintf(stdout, "current top elem is %d\n",
          GetTop(*S, &elem_ret) ? elem_ret : 0);

  free(S);
  return EXIT_SUCCESS;
}
