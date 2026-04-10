#pragma once
#include <initializer_list>
#include <iostream>
#include <stdexcept>

template <typename T> class DoubleList {
private:
  struct Node {
    T data;
    Node *prev;
    Node *next;
    Node(const T &d = T{}, Node *p = nullptr, Node *n = nullptr)
        : data{d}, prev{p}, next{n} {}
  };

  Node *head; // 头结点
  Node *tail; // 尾结点
  int length; // 链表长度

public:
  DoubleList();
  DoubleList(std::initializer_list<T>);
  ~DoubleList();
  // 避免浅拷贝导致对一个内存多次delete
  DoubleList(const DoubleList &) = delete;
  DoubleList &operator=(const DoubleList &) = delete;

  void insert(int index, const T &val);
  void remove(int index);
  void update(int index, const T &val);

  [[nodiscard]] T get(int index) const;
  [[nodiscard]] size_t size() const;

  void print() const;
};

template <typename T> DoubleList<T>::DoubleList() : length{0} {
  head = new Node{};
  tail = new Node{};
  head->next = tail;
  tail->prev = head;
}

template <typename T>
DoubleList<T>::DoubleList(std::initializer_list<T> list)
    : DoubleList() { // 委托无参构造函数初始化

  Node *curr = head;
  for (T val : list) {
    curr->next = new Node{val, curr, curr->next};
    curr = curr->next;
    length++;
  }
}
