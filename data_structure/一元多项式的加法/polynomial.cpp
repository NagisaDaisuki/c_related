#include <cstdlib>
#include <iostream>

// 多项式结点定义
struct PolyNode {
  int coef;       // 系数 (coefficient)
  int exp;        // 指数 (exponent)
  PolyNode *next; // 指针域
};

// 尾插法创建多项式链表（带头结点）
void CreatePoly(PolyNode *&L, int n);
// 多项式加法，将第二个式子加到第一个式子上原路复用内存
void AddPoly(PolyNode *&A, PolyNode *&B);
// 打印多项式
void PrintPoly(PolyNode *L);

int main(void) {
  int n, m;
  PolyNode *A, *B;

  // 读取多项式 A
  if (std::cin >> n) {
    CreatePoly(A, n);
  }

  // 读取多项式B
  if (std::cin >> m) {
    CreatePoly(B, m);
  }
  // 执行加法
  AddPoly(A, B);

  // 输出结果
  PrintPoly(A);

  return EXIT_SUCCESS;
}

// ---------------------------------------
// 尾插法创建多项式链表（带头结点）
void CreatePoly(PolyNode *&L, int n) {
  L = new PolyNode;
  L->next = NULL;
  PolyNode *tail = L; // 尾指针

  for (int i = 0; i < n; i++) {
    PolyNode *p = new PolyNode;
    std::cin >> p->coef >> p->exp;
    p->next = NULL;
    tail->next = p;
    tail = p;
  }
}

// 多项式加法，将第二个式子加到第一个式子上原路复用内存
void AddPoly(PolyNode *&A, PolyNode *&B) {
  PolyNode *p1 = A->next; // 遍历A
  PolyNode *p2 = B->next; // 遍历B
  PolyNode *pc = A;       // 指向合并后的链表尾部，初始值指向链表A头结点

  while (p1 != NULL && p2 != NULL) {
    if (p1->exp < p2->exp) {
      pc->next = p1;
      pc = p1;
      p1 = p1->next;
    } else if (p1->exp > p2->exp) {
      pc->next = p2;
      pc = p2;
      p2 = p2->next;
    } else { // exp相等
      int sum = p1->coef + p2->coef;
      if (sum != 0) {
        p1->coef = sum; // 修改 p1 的系数
        pc->next = p1;  // 把修改后的 p1 挂上去
        pc = p1;
        p1 = p1->next;

        // 销毁p2
        PolyNode *temp = p2;
        p2 = p2->next;
        delete temp;
      } else {
        // 两个结点都不需要，都要销毁
        PolyNode *temp = p1;
        p1 = p1->next;
        delete temp;

        PolyNode *temp1 = p2;
        p2 = p2->next;
        delete temp1;
      }
    }
  }

  // 把还没有跑完的多项式添加到pc的后面
  // if (p1) pc->next = p1; else pc->next = p2;
  pc->next = (p1 != NULL) ? p1 : p2;

  // 最后释放B的空壳头结点（因为它的有效结点全被合并或者销毁了）
  delete B;
}

// 打印多项式
void PrintPoly(PolyNode *L) {
  PolyNode *p = L;

  // 空多项式
  if (p == NULL) {
    std::cout << "0" << std::endl;
    return;
  }

  bool isFirst = true; // 标记是否为第一项，判断是否要打印字符

  while (p != NULL) {
    // 如果不是第一项且系数为正数才需要手动输出 '+'
    // 如果是负数, p->coef 自身带负号，不需要管
    if (!isFirst && p->coef > 0) {
      std::cout << "+";
    }

    std::cout << p->coef << "x^" << p->exp;

    isFirst = false;
    p = p->next;
  }
  std::cout << std::endl;
}
