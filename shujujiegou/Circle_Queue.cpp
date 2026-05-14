#include <iostream>
using namespace std;

#define MAXQSIZE 100

int OK = 0;
int ERROR = 1;
typedef int QElemType;
struct SqQueue {
  QElemType *base; // 初始化时动态分配存储空间
  int front;       // 头指针
  int rear;        // 尾指针
};

// 循环队列的初始化
int InitQueue(SqQueue &Q) { // 构造一个空队列Q
  Q.base =
      new QElemType[MAXQSIZE]; // 为队列分配一个最大容量为 MAXSIZE的数组空间
  if (!Q.base)
    return ERROR;

  // 初始化时，头尾指针必须全部指向 0
  Q.front = Q.rear = 0;
  return OK;
}

// 判断队空
int isQEmpty(SqQueue Q) {
  // 在循环队列中，头尾指针相遇即代表队列为空
  return Q.front == Q.rear;
}

// 判断队满
int isFull(SqQueue Q) {
  // 尾指针在循环意义上加1后等于头指针，表明队满（牺牲一个空间防止歧义）
  return (Q.rear + 1) % MAXQSIZE == Q.front;
}

// 求循环队列的长度
int QueueLength(SqQueue Q) { // 返回 Q 的 元素个数，即队列的长度
  return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

// 循环队列的入队
int EnQueue(SqQueue &Q, QElemType e) {
  if (isFull(Q))
    return ERROR;

  Q.base[Q.rear] = e;               // 新元素插入队尾
  Q.rear = (Q.rear + 1) % MAXQSIZE; // 队尾指针加1（利用取模实现物理内存的循环）

  return OK;
}

// 循环队列的出队
int DeQueue(SqQueue &Q, QElemType &e) {
  if (isQEmpty(Q))
    return ERROR; // 队空

  e = Q.base[Q.front];                // 保存队头元素，用e带回
  Q.front = (Q.front + 1) % MAXQSIZE; // 队头指针加1（利用取模）

  return OK;
}

// 删除队列
void Destroy(SqQueue &Q) {
  if (Q.base)
    delete[] Q.base;
  Q.base = NULL;
  Q.front = Q.rear = 0;
}

// 取循环队列的队头元素
QElemType GetHead(SqQueue Q) { // 返回 Q 的队头元素，不修改队头指针
  if (Q.front != Q.rear)       // 队列非空
    return Q.base[Q.front];    // 返回队头元素的值，队头指针不变
  return 0;
}

int main() {
  int n;
  cin >> n;

  SqQueue Q;
  QElemType e;
  InitQueue(Q);
  for (int i = 0; i < MAXQSIZE - 1 - n / 2; i++) {
    EnQueue(Q, i);
  }

  for (int i = 0; i < MAXQSIZE - 1 - n / 2; i++) {
    DeQueue(Q, e);
  }
  for (int i = 0; i < n; i++) {
    QElemType e;
    cin >> e;
    EnQueue(Q, e);
  }
  for (int i = 0; i < n; i++) {
    QElemType e;
    DeQueue(Q, e);
    cout << e << ' ';
  }
  Destroy(Q);
  return 0;
}
