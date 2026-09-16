#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MaxSize 10 // 设小一点方便测试满队情况
typedef int ElemType;

// 顺序双端队列结构体定义
typedef struct {
  ElemType data[MaxSize];
  int front; // 队头指针
  int rear;  // 队尾指针 （指向下一个空位）
} SqDeque;

// 1. 初始化
void InitDeque(SqDeque *Q) {
  Q->front = 0;
  Q->rear = 0;
}

// 2. 判空
bool DequeEmpty(SqDeque Q) { return Q.front == Q.rear; }

// 3. 判满(牺牲一个单元法)
bool DequeFull(SqDeque Q) { return (Q.rear + 1) % MaxSize == Q.front; }

// ======================= 常规队列操作 ============================

// 4. 队尾入队 (Insert Rear) - 和普通循环队列一模一样
bool InsertRear(SqDeque *Q, ElemType x) {
  if (DequeFull(*Q))
    return false;

  Q->data[Q->rear] = x;              // 放入元素
  Q->rear = (Q->rear + 1) % MaxSize; // rear 往后走一步
  return true;
}

// 5. 队头出队（Delete Front）和普通循环队列一模一样
bool DeleteFront(SqDeque *Q, ElemType *x) {
  if (DequeEmpty(*Q))
    return false;

  *x = Q->data[Q->front];              // 拿出元素
  Q->front = (Q->front + 1) % MaxSize; // front 往后走一步
  return true;
}

// ================== 双端队列专属“逆行”操作 ==================

// 6. 队头入队（Insert Front）
bool InsertFront(SqDeque *Q, ElemType x) {
  if (DequeFull(*Q))
    return false;

  // 核心：front必须先 “往回倒一步”，然后再存入数据
  // 这里 Q->front - 1 + MaxSize 是为了防止出现 (0 - 1) % 8 这种负数取余操作
  Q->front = (Q->front - 1 + MaxSize) % MaxSize;
  Q->data[Q->front] = x;
  return true;
}

// 7. 队尾出队 (Delete Rear)
bool DeleteRear(SqDeque *Q, ElemType *x) {
  if (DequeEmpty(*Q))
    return false;

  // 核心：rear本来指向的就是空位，必须先“往回倒一步”找到真实元素
  Q->rear = (Q->rear - 1 + MaxSize) % MaxSize;
  *x = Q->data[Q->rear];
  return true;
}

// 打印测试辅助函数
void PrintDeque(SqDeque Q) {
  fprintf(stdout, "Deque:[ ");
  int p = Q.front;
  while (p != Q.rear) {
    fprintf(stdout, "%d ", Q.data[p]);
    p = (p + 1) % MaxSize;
  }
  printf("]\n");
}

int main(void) {
  SqDeque Q;
  InitDeque(&Q);

  printf("---- 开始测试双端队列 ----\n");

  // 1. 常规队尾入队
  InsertRear(&Q, 10);
  InsertRear(&Q, 20);
  printf("队尾插入10,20后：\n");
  PrintDeque(Q);

  // 2. 队头插入
  InsertFront(&Q, 5);
  InsertFront(&Q, 1);
  printf("队头插入10,20后：\n");
  PrintDeque(Q);

  // 3. 常规队头出队
  int val;
  DeleteFront(&Q, &val);
  printf("队头出队: %d\n", val);

  // 4. 骚操作：队尾出队
  DeleteRear(&Q, &val);
  printf("队尾出队: %d\n", val);

  printf("最终状态:\n");
  PrintDeque(Q); // 预期结果应该是 [ 5 10 ]

  return 0;
}
