// 满二叉树 和 完全二叉树
// 使用 std::unique_ptr 来明确节点的独占所有权，完全避免了
// 手动 new 和 delete，即使发生异常也不会造成内存泄漏。
// 在遍历时，使用裸指针（Raw Pointer）作为“观察者”进行访问。

#include <iostream>
#include <memory>
#include <queue>
#include <vector>

// 定义结点结构体
struct TreeNode {
  int data;
  std::unique_ptr<TreeNode> left;
  std::unique_ptr<TreeNode> right;

  // 构造函数
  explicit TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BinaryTree {
 private:
 public:
};
