#include <iostream>

using namespace std;

int OK = 0;
int ERROR = 1;

typedef char ElemType;

struct LNode {
  ElemType data; // 数据域
  LNode *next;   // 指针域
};

// *LinkList为LNode类型的指针
int initList_L(LNode *&L) {

  // if (L != NULL)
  //   return ERROR;
  L = new LNode;
  L->data = ' ';
  L->next = NULL;
  return OK;
}

// 在线性表L中查找值为e的数据元素
LNode *LocateElem_L(LNode *L, ElemType e) {
  // 返回L中值为e的数据元素的地址，查找失败返回NULL
  if (L == NULL)
    return NULL;

  LNode *p = L;
  while (p->next != NULL && p->data != e)
    p = p->next;
  if (p->data == e)
    return p;
  return NULL;
}

// 在L中第i个元素之前插入数据元素e
int ListInsert_L(LNode *&L, int i, ElemType e) {
  LNode *p = L;
  int j = 0;
  while (p && j < i - 1) {
    p = p->next;
    ++j;
  }
  if (!p || j < i - 1)
    return ERROR;
  LNode *InsertNode = new LNode;
  InsertNode->data = e;
  InsertNode->next = p->next->next;
  p->next = InsertNode;
  return OK;
}

// 将线性表L中第i个数据元素删除
int ListDelete_L(LNode *&L, int i, ElemType &e) {
  LNode *p = L;
  int j = 0;
  while (p->next && j < i - 1) { // 寻找第i个结点，并令p指向其前驱
    p = p->next;
    ++j;
  }
  if (!(p->next) || j > i - 1)
    return ERROR;     // 删除位置不合理
  LNode *q = p->next; // 绑住要删除的节点
  p->next = p->next->next;
  delete q; // 释放删除结点的空间
  return OK;
}

int DestroyList_L(LNode *&L) {
  LNode *p;
  p = L;
  LNode *q;
  while (p != NULL) {
    q = p;
    p = p->next;
    delete q;
  }
  L = NULL;
  return OK;
}

void CreateList_F(LNode *&L, int n) {
  if (initList_L(L) != OK)
    return;

  // 先建立一个带头结点的单链表
  for (int i = n; i > 0; --i) {
    LNode *p = new LNode; // 生成新结点
    cin >> p->data;       // 输入元素值
    p->next = L->next;
    L->next = p;
  }
}
