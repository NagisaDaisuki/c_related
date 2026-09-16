#include <cstdlib>
#include <iostream>

typedef struct BiNode {
  char data;
  struct BiNode *lchild, *rchild;
} BiTNode, *BiTree;

void CreateBiTree(BiTree &T) {
  // 传入的是指针引用类型，可以传入未初始化的指针变量并在函数内分配内存
  char ch;
  std::cin >> ch;
  if (ch == '#')
    T = NULL;
  else {
    T = new BiTNode;
    T->data = ch;
    CreateBiTree(T->lchild);
    CreateBiTree(T->rchild);
  }
}

void Copy(BiTree T, BiTree &new_tree) {
  if (T == NULL) {
    new_tree = NULL;
    return;
  }
  new_tree = new BiTNode;
  new_tree->data = T->data;
  Copy(T->lchild, new_tree->lchild);
  Copy(T->rchild, new_tree->rchild);
}

void PostOrderTraverse(BiTree T) {
  if (T == NULL)
    return;
  PostOrderTraverse(T->lchild);
  PostOrderTraverse(T->rchild);
  std::cout << T->data << " ";
}

void PreOrderTraverse(BiTree T) {
  if (T == NULL)
    return;
  std::cout << T->data << " ";
  PreOrderTraverse(T->lchild);
  PreOrderTraverse(T->rchild);
}

int main() {
  BiTree tree, new_tree;
  CreateBiTree(tree);
  Copy(tree, new_tree);
  PreOrderTraverse(new_tree);
  std::cout << "\n";
  PostOrderTraverse(new_tree);
  std::cout << "\n";
  std::cout << std::endl;

  return EXIT_SUCCESS;
}
