#include <cstdlib>
#include <iostream>

using namespace std;

typedef struct BiNode {
  char data;
  struct BiNode *lchild, *rchild;
} BiTNode, *BiTree;

void CreateBiTree(
    BiTree &
        T) { // 指针的引用，不是给临时的拷贝指针变量分配内存而是事实給传入的实参指针变量分配内存
  char ch;
  cin >> ch;

  if (ch == '#')
    T = NULL;
  else {
    T = new BiTNode;
    T->data = ch;
    CreateBiTree(T->lchild);
    CreateBiTree(T->rchild);
  }
}

void output_leaves_and_num(BiTree T, int &count) {
  if (T == NULL)
    return; // 如果为空结点返回

  // 判断是否为叶子结点(左右子节点皆为空)
  if (T->lchild == NULL && T->rchild == NULL) {
    cout << T->data; // 输出叶子结点
    count++;
    return; // 已经是叶子结点直接返回
  }

  // 递归遍历左子树和右子树
  output_leaves_and_num(T->lchild, count);
  output_leaves_and_num(T->rchild, count);
}

int main(void) {
  BiTree bT;
  int count = 0;
  CreateBiTree(bT);
  output_leaves_and_num(bT, count);
  cout << "\n";
  cout << count << endl;
  return EXIT_SUCCESS;
}
