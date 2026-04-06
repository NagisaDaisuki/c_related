#pragma once
#include <iostream>
#include <stdexcept>

template <typename T> class DoubleList {
private:
  struct DNode {
    T data;
    DNode *prev;
    DNode *next;
    DNode(const T &d = T{}, DNode *p = nullptr, DNode *n = nullptr)
        : data{d}, prev{p}, next{n} {
    } // const T& d 常量左值对临时对象 T{} 右值的续命 lifetime extension
    // 这里 如果 是 T& d = T{} 编译器会直接报错，因为一般左值
    // 在之后会被修改，而一个将亡值（右值）马上就有可能消失 所以在 C++
    // 设计之初就封死了这条路
  };

  DNode *head;
  DNode *tail;   // 双哨兵结点，Linux内核和C++ STL std::list 的实现方式
  size_t length; // 插入和删除时永远不需要判断 if (prev == nullptr),
                 // 因为前后永远有哨兵挡着

public:
  DoubleList() : length{0} {
    head = new DNode{};
    tail = new DNode{};
    head->next = tail;
    tail->prev = head;
  }

  ~DoubleList() {
    DNode *curr = head;
    while (curr != nullptr) {
      DNode *nextNode = curr->next;
      delete curr;
      curr = nextNode;
    }
  }

  // 增
  void insert(size_t index, const T &val) {
    if (index > length)
      throw std::out_of_range("Insert index out of range");

    DNode *p = head;
    for (size_t i = 0; i <= index; ++i)
      p = p->next;

    // 在 p 的 前面 插入新结点（完美切断并重连 4 根指针）
    DNode *newNode = new DNode(val, p->prev, p);
    p->prev->next = newNode;
    p->prev = newNode;
    length++;
  }

  // 删
  void remove(size_t index) {
    if (index >= length)
      throw std::out_of_range("Remove index out of range");

    DNode *p = head->next;
    for (size_t i = 0; i < index; ++i)
      p = p->next;

    // 旁路断开
    p->prev->next = p->next;
    p->next->prev = p->prev;
  }

  // 改
  void update(size_t index, const T &val) {
    if (index >= length)
      throw std::out_of_range("Update index out of range");
    DNode *p = head->next;
    for (size_t i = 0; i < index; i++)
      p = p->next;
    p->data = val;
  }

  // 查
  T get(size_t index) const {
    if (index >= length)
      throw std::out_of_range("Get index out of range");
    DNode *p = head->next;
    for (size_t i = 0; i < index; ++i)
      p = p->next;
    return p->data;
  }

  void print() const {
    std::cout << "DoubleList: [";
    DNode *p = head->next;
    while (p != tail) {
      std::cout << p->data << (p->next != tail ? "<->" : "");
      p = p->next;
    }
    std::cout << "]\n";
  }
};
