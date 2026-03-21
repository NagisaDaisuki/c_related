#include <iostream>

using namespace std;

int OK = 0;
int ERROR = 1;

typedef char ElemType;

struct LNode {
  ElemType data; // 数据域
  LNode *prev;   // 指针域
  LNode *next;   // 指针域
};

// *LinkList为Lnode类型的指针
int InitList_L(LNode *&L) {
  L = new LNode;
  L->data = ' ';
  L->prev = NULL;
  L->next = NULL;
  return OK;
}

// 在线性表L中查找值为e的数据元素
LNode *LocateElem_L(LNode *L, ElemType e) {
  // 返回L中值为e的数据元素的地址，查找失败返回NULL
  if (L == NULL)
    return NULL;

  LNode *p = L->next;
  while (p != NULL && p->data != e) {
    p = p->next;
  }
  if (p->data == e) {
    return p;
  }
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
  if (!p || j > i - 1)
    return ERROR;
  LNode *q = new LNode;
  q->data = e;
  q->next = p->next;
  q->prev = p;
  if (p->next != NULL)
    p->next->prev = q; // 后面挂前面
  p->next = q;
  return OK;
}

// 将线性表L中第i个数据元素删除
int ListDelete_L(LNode *&L, int i, ElemType &e) {
  LNode *p = L;
  int j = 0;
  while (p->next && j < i) {
    p = p->next;
    ++j;
  }
  if (!p)
    return ERROR;
  if (j < i)
    return ERROR;
  LNode *q = p;
  e = q->data;
  p->prev->next = p->next;
  // 确认删除节点后节点是一个非NULL节点
  if (p->next != NULL)
    p->next->prev = p->prev;
  delete q;

  return OK;
}

int DestroyList_L(LNode *&L) {
  if (L == NULL)
    return OK;

  LNode *p = L;
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
  // 先建立一个带头结点的单链表
  if (InitList_L(L) != OK)
    return;

  for (int i = n; i > 0; i--) {
    LNode *p = new LNode; // 生成新结点
    cin >> p->data;       // 输入元素值

    p->prev = L;
    p->next = L->next;
    if (L->next != NULL)
      L->next->prev = p;
    L->next = p;
  }
}

void output(LNode *L) {
  L = L->next;
  while (L != NULL) {
    cout << L->data << ' ';
    L = L->next;
  }
  cout << endl;
}

void invoutput(LNode *L) {
  LNode *T = L;
  while (T->next != NULL) {
    T = T->next;
  }
  while (T != L) {
    cout << T->data << ' ';
    T = T->prev;
  }
  cout << endl;
}

int main() {
  LNode *head;

  // 创建链表
  int n;
  cin >> n;
  CreateList_F(head, n);
  invoutput(head);

  // 插入元素
  int loc;
  ElemType ne;
  cin >> loc;
  cin >> ne;
  ListInsert_L(head, loc, ne);
  invoutput(head);

  // 定位并输出其下一个
  cin >> ne;
  LNode *pt = LocateElem_L(head, ne);
  if (pt == NULL)
    cout << "no found!" << endl;
  else if (pt->next == NULL)
    cout << "NULL" << endl;
  else
    cout << pt->next->data << endl;
  invoutput(head);

  // 删除元素
  cin >> loc;
  ListDelete_L(head, loc, ne);
  invoutput(head);

  // 销毁链表
  DestroyList_L(head);

  return 0;
}
