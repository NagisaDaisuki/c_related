#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MaxSize 50
typedef int ElemType;

typedef struct {
  ElemType data[MaxSize];
  int front; // 队头指针：指向队头元素
  int rear;  // 队尾指针：指向队尾元素的下一个位置
} SqQueue;

// 1. 初始化
void InitQueue(SqQueue *Q) {
  Q->front = 0;
  Q->rear = 0;
}

// 2. 判空
bool QueueEmpty(SqQueue Q) { return Q.front == Q.rear; }

// 3. 入队
bool EnQueue(SqQueue *Q, ElemType x) {
  // 牺牲一个单元来判断队满
  if ((Q->rear + 1) % MaxSize == Q->front)
    return false; // 队满

  Q->data[Q->rear] = x;              // 将 x 插入队尾
  Q->rear = (Q->rear + 1) % MaxSize; // 队尾指针往后转圈
  return true;
}

// 4. 出队
bool DeQueue(SqQueue *Q, ElemType *x) {
  if (QueueEmpty(*Q)) // 队空报错
    return false;
  *x = Q->data[Q->front];              // 拿出队头元素
  Q->front = (Q->front + 1) % MaxSize; // 队头指针往后转圈
  return true;
}

// 5. 队满判断
bool QueueFull(SqQueue Q) { return (Q.rear + 1) % MaxSize == Q.front; }

// 6. 获取队首元素
bool GetHead(SqQueue Q, ElemType *x) {
  if (QueueEmpty(Q))
    return false;
  *x = Q.data[Q.front];
  return true;
}
