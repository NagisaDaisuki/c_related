#include <cstdlib>
#include <iostream>

// 1. 定义链栈的结点结构
struct StackNode {
  int data;        // 存放余数
  StackNode *next; // 指向下一个结点的指针
};

// 2. 封装链栈类
class LinkedStack {
private:
  StackNode *top; // 栈顶指针
public:
  // 构造函数：初始化空栈
  LinkedStack() : top{nullptr} {}

  // 析构函数：防止内存泄露
  ~LinkedStack() {
    while (!isEmpty()) {
      pop();
    }
  }

  // 入栈操作（头插法）
  void push(int val) {
    StackNode *newNode = new StackNode;
    newNode->data = val;
    newNode->next = top;
    top = newNode;
  }

  // 出栈操作
  int pop() {
    if (isEmpty())
      return -1; // 触发空栈出队

    int val = top->data;   // 取出栈顶数据
    StackNode *temp = top; // 暂时保存原来的栈顶结点
    top = top->next;       // top 指针下移
    delete temp;
    return val;
  }

  // 判断栈是否为空
  bool isEmpty() { return top == nullptr; }
};

int main(void) {
  long long n;

  // 读取输入的十进制非负数
  if (std::cin >> n) {
    // 边界处理情况（如果是0直接输出0）
    if (n == 0)
      std::cout << 0 << "\n";

    LinkedStack s;

    // 核心逻辑：除 2 取余，余数入栈
    while (n > 0) {
      int remainder = n % 2; // 取余数
      s.push(remainder);     // 余数压入链栈
      n = n / 2;             // 更新 n 为商
    }

    // 输出逻辑：依次出栈，实现逆序输出
    while (!s.isEmpty()) {
      std::cout << s.pop();
    }
    std::cout << "\n";
  }
  return EXIT_SUCCESS;
}
