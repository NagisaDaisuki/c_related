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

int Depth(BiTree &T) {
  if (T == NULL)
    return 0;
  int leftDepth = Depth(T->lchild);
  int rightDepth = Depth(T->rchild);

  return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
}

int main() {
  BiTree tree;
  CreateBiTree(tree);
  cout << Depth(tree) << endl;
}
