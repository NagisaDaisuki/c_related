#pragma once
#include <iostream>
#include <stdexcept>

template <typename T> class SingleList {
private:
  struct Node {
    T data;
    Node *next; // C 中得完整声明 struct Node
    Node(const T &d = T{}, Node *n = nullptr) : data{d}, next{n} {}
  };

  Node *head; // 表头结点（不存真实数据）
  size_t length;

public:
  SingleList() : length{0} {
    head = new Node{}; // 创建哨兵结点
  }

  ~SingleList() {
    Node *curr = head;
    while (curr != nullptr) {
      Node *nextNode = curr->next;
      delete curr;
      curr = nextNode;
    }
  }

  // 增：在逻辑索引 index 处插入 (index 从0 开始)
  void insert(size_t index, const T &val) {
    if (index > length)
      throw std::out_of_range("Inset index out of range");

    Node *p = head; // 游标 p 寻找前驱结点
    for (size_t i = 0; i < index; ++i)
      p = p->next;

    Node *newNode = new Node(val, p->next);
    p->next = newNode;
    length++;
  }

  // 删
  void remove(size_t index) {
    if (index >= length)
      throw std::out_of_range("Remove index out of range");

    Node *p = head; // 游标 p 依旧寻找前驱节点
    for (size_t i = 0; i < index; i++)
      p = p->next;

    Node *q = p->next; // 锁定目标
    p->next = q->next; // 旁路断开
    delete q;
    length--;
  }

  // 改
  void update(size_t index, const T &val) {
    if (index >= length)
      throw std::out_of_range("Update index out of range");

    Node *p = head->next;
    for (size_t i = 0; i < index; ++i)
      p = p->next;
    p->data = val;
  }

  // 查
  T get(size_t index) const {
    if (index >= length)
      throw std::out_of_range("Get index out of range");
    Node *p = head->next;
    for (size_t i = 0; i < index; ++i)
      p = p->next;
    return p->data;
  }

  void print() const {
    std::cout << "SingleList: [";
    Node *p = head->next;
    while (p != nullptr) {
      std::cout << p->data << (p->next ? "->" : "");
      p = p->next;
    }
    std::cout << "]\n";
  }
};
