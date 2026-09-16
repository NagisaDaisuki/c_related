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

  for (T val : list) {
    insert(length, val);
  }
}

template <typename T> DoubleList<T>::~DoubleList() {
  Node *p = head;
  while (p != nullptr) {
    Node *q = p;
    p = p->next;
    delete q;
  }
  head = nullptr;
  tail = nullptr;
  length = 0;
}

template <typename T> void DoubleList<T>::insert(int index, const T &val) {
  if (index > length)
    throw std::out_of_range("Insert index out of range");

  Node *p = head;
  for (int i = 0; i <= index; ++i) {
    p = p->next;
  }
  Node *newNode = new Node{val, p->prev, p};
  p->prev->next = newNode;
  p->prev = newNode;
  length++;
}

template <typename T> void DoubleList<T>::remove(int index) {
  if (index >= length)
    throw std::out_of_range("Remove index out of range");
  Node *p = head;
  for (int i = 0; i <= index; i++)
    p = p->next;

  p->prev->next = p->next;
  if (p->next != nullptr)
    p->next->prev = p->prev;

  delete p;
  length--;
}

template <typename T> void DoubleList<T>::update(int index, const T &val) {
  if (index >= length)
    throw std::out_of_range("Update index out of range");
  Node *p = head;
  for (int i = 0; i <= index; i++)
    p = p->next;
  p->data = val;
}

template <typename T> [[nodiscard]] T DoubleList<T>::get(int index) const {
  if (index >= length)
    throw std::out_of_range("Get index out of range");
  Node *p = head;
  for (int i = 0; i <= index; i++)
    p = p->next;
  return p->data;
}

template <typename T> [[nodiscard]] size_t DoubleList<T>::size() const {
  return length;
}

template <typename T> void DoubleList<T>::print() const {
  std::cout << "DoubleList: [";
  Node *p = head->next;
  while (p != tail) {
    std::cout << p->data << (p->next == tail ? "" : " <-> ");
    p = p->next;
  }
  std::cout << "]\n";
}
