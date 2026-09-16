#include <iostream>
using namespace std;
typedef struct BiNode {
  char data;
  struct BiNode *lchild, *rchild;
} BiTNode, *BiTree;

void CreateBiTree(BiTree &T) {
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

void InOrderTraverse(BiTree &T) {
  if (T == NULL)
    return;

  InOrderTraverse(T->lchild);
  cout << T->data;
  InOrderTraverse(T->rchild);
}

int main() {
  BiTree tree;
  CreateBiTree(tree);
  InOrderTraverse(tree);
  cout << endl;
}
