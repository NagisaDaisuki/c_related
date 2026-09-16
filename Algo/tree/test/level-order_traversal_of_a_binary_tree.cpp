#include <iostream>
#include <math.h>
#include <stdio.h>
#define MAXQSIZE 100
using namespace std;

struct BiNode {
  char data;
  BiNode *lchild, *rchild;
};

struct SqQueue {
  BiNode *base[100];
  int front, rear;
};

void CreateBiTree(BiNode *&T) {

  char ch;
  cin >> ch;
  if (ch == '#')
    T = NULL;
  else {
    T = new BiNode;
    T->data = ch;
    CreateBiTree(T->lchild);
    CreateBiTree(T->rchild);
  }
}

// 用队列实现：根结点入队->出队访问->左孩子入队->右孩子入队
void LevelOrder(BiNode *T) {
  if (T == NULL)
    return;

  SqQueue Q;
  Q.front = Q.rear = 0;
  Q.base[Q.rear++] = T;

  while (Q.front != Q.rear) {
    // 出队
    BiNode *p = Q.base[Q.front++];

    // 访问当前结点
    cout << p->data;

    // 左孩子入队
    if (p->lchild != NULL)
      Q.base[Q.rear++] = p->lchild;

    // 右孩子入队
    if (p->rchild != NULL)
      Q.base[Q.rear++] = p->rchild;
  }
}

int main() {

  BiNode *Tree;
  // 按先序遍历次序输入
  CreateBiTree(Tree);
  LevelOrder(Tree);
  return 0;
}
