// #include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXSIZE 100 // 栈最大容量
#define TRUE 1
#define FALSE 0

typedef int Status;

// 数字栈
typedef struct {
  int elem[MAXSIZE];
  int top;
} NumStack;

// 运算符栈
typedef struct {
  int elem[MAXSIZE];
  int top;
} OpStack;

// 初始化数字栈
void initNumStack(NumStack *pNumStack) {
  memset(pNumStack->elem, 0, sizeof(pNumStack->elem));
  pNumStack->top = 0;
}

// 初始化符号栈
void initOpStack(OpStack *pOpStack) {
  memset(pOpStack->elem, 0, sizeof(pOpStack->elem)); // 对于静态数组
  pOpStack->top = 0;
}

// 数字栈入栈
Status pushNum(NumStack *pNumStack, int num) {
  if (pNumStack->top == MAXSIZE)
    return FALSE;
  pNumStack->elem[pNumStack->top] = num;
  pNumStack->top++;
  return TRUE;
}

// 数字栈出栈，栈空时返回 -1
int popNum(NumStack *pNumStack) {
  if (pNumStack->top == 0)
    return -1;
  pNumStack->top--;
  int popnum = pNumStack->elem[pNumStack->top];
  return popnum;
}

// 运算符栈入栈
Status pushOp(OpStack *pOpStack, char op) {
  if (pOpStack->top == MAXSIZE)
    return FALSE;
  pOpStack->elem[pOpStack->top] = op;
  pOpStack->top++;
  return TRUE;
}

// 运算符栈出栈，栈空时返回\0
char popOp(OpStack *pOpStack) {
  if (pOpStack->top == 0)
    return '\0';
  pOpStack->top--;
  char popop = pOpStack->elem[pOpStack->top];
  return popop;
}

// 获取符号栈顶元素，栈空时返回\0
char getTopOp(OpStack opstack) {
  if (opstack.top == 0)
    return '\0';
  // top - 1才是最后一个存入数据的真实位置
  return opstack.elem[opstack.top - 1];
}

// 符号栈判空
Status emptyOp(OpStack opStack) {
  if (opStack.top == 0)
    return TRUE;
  return FALSE;
}

// 返回运算符优先级
int priority(char op) {
  switch (op) {
  case '+':
  case '-':
    return 1;
  case '*':
  case '/':
    return 2;
  case '(':
    return 0;
  default:
    return 0;
  }
}

// 计算两个数
int calc(int a, int b, char op) {
  switch (op) {
  case '+':
    return a + b;
  case '-':
    return a - b;
  case '*':
    return a * b;
  case '/':
    return a / b;
  default:
    return 0;
  }
}

// 判断一个字符是否为数字
int isdigit(char c) {
  if (c >= '0' && c <= '9')
    return TRUE;
  else
    return FALSE;
  ;
}

// 表达式 求值
int evaluate(char *expr) {
  NumStack numStack;
  OpStack opStack;

  int i = 0, len = strlen(expr); // 字符串长度
  initNumStack(&numStack);
  initOpStack(&opStack);

  while (i < len) {
    // 数字：处理多位数
    if (isdigit(expr[i])) {
      int num = 0;
      while (i < len && isdigit(expr[i])) {
        num = num * 10 + (expr[i] - '0');
        i++;
      }
      pushNum(&numStack, num);
    }
    // 如果是空格直接跳过
    else if (expr[i] == ' ') {
      i++;
      continue;
    }
    // 左括号直接进栈
    else if (expr[i] == '(') {
      pushOp(&opStack, expr[i]);
      i++;
    }
    // 右括号：计算到左括号
    else if (expr[i] == ')') {
      while (getTopOp(opStack) != '(') {
        int b = popNum(&numStack);
        int a = popNum(&numStack);
        char op = popOp(&opStack);
        pushNum(&numStack, calc(a, b, op));
      }
      popOp(&opStack); // 弹出左括号
      i++;
    }
    // 运算符：按优先级处理
    else {
      while (!emptyOp(opStack) &&
             priority(getTopOp(opStack)) >= priority(expr[i])) {
        int b = popNum(&numStack);
        int a = popNum(&numStack);
        char op = popOp(&opStack);
        pushNum(&numStack, calc(a, b, op));
      }
      pushOp(&opStack, expr[i]);
      i++;
    }
  }
  // 处理剩余运算符
  while (!emptyOp(opStack)) {
    int b = popNum(&numStack);
    int a = popNum(&numStack);
    char op = popOp(&opStack);
    pushNum(&numStack, calc(a, b, op));
  }
  return popNum(&numStack);
}

int main(void) {
  char expr[MAXSIZE];
  // 正则表达式思想，读取直到遇到换行符 '\n'
  fscanf(stdin, "%[^\n]", expr);
  int res = evaluate(expr);
  fprintf(stdout, "%d\n", res);
  return 0;
}
