#pragma once
#include <initializer_list> // C++11
#include <iostream>
#include <stdexcept>

template <typename T> class SingleList {
private:
  struct Node {
    T data;
    Node *next;
    Node(const T &d = T{}, Node *n = nullptr) : data{d}, next{n} {}
  };
  Node *head; // 表头结点
  size_t length;

public:
  SingleList();
  SingleList(std::initializer_list<T>);
  ~SingleList();
  // 遵循三/五法则，封杀浅拷贝导致的 Double Free 灾难
  SingleList(const SingleList &) = delete;            // 禁用拷贝构造
  SingleList &operator=(const SingleList &) = delete; // 禁用拷贝构造

  void insert(size_t index, const T &val);
  void remove(size_t index);
  void update(size_t index, const T &val);

  // 使用 [[nodiscard]] 保护查阅类函数
  [[nodiscard]] T get(size_t index) const;

  // 补充一个获取长度的安全接口
  [[nodiscard]] size_t size() const;

  void print() const;
};

template <typename T> SingleList<T>::SingleList() : length{0} {
  head = new Node{};
}

template <typename T>
SingleList<T>::SingleList(std::initializer_list<T> init)
    : SingleList() { // 委托构造函数调用默认构造函数
  Node *curr = head;
  for (const auto &val : init) {
    curr->next = new Node(val);
    curr = curr->next;
    length++;
  }
}

template <typename T> SingleList<T>::~SingleList() {
  Node *curr = head;
  while (curr != nullptr) {
    Node *nextNode = curr->next;
    delete curr;
    curr = nextNode;
  }
}

template <typename T> void SingleList<T>::insert(size_t index, const T &val) {
  if (index > length)
    throw std::out_of_range("Insert index out of range");

  Node *p = head;
  for (int i = 0; i < index; i++)
    p = p->next;
  p->next = new Node(val, p->next);
  length++;
}

template <typename T> void SingleList<T>::remove(size_t index) {
  if (index >= length)
    throw std::out_of_range("Remove index out of range");

  Node *p = head;
  for (int i = 0; i < index; i++)
    p = p->next;
  Node *q = p->next;
  p->next = q->next;
  delete q;
  length--;
}

template <typename T> void SingleList<T>::update(size_t index, const T &val) {
  if (index >= length)
    throw std::out_of_range("Update index out of range");

  Node *p = head->next;
  for (int i = 0; i < index; i++)
    p = p->next;
  p->data = val;
}

template <typename T> T SingleList<T>::get(size_t index) const {
  if (index >= length)
    throw std::out_of_range("Get index out of range");

  Node *p = head->next;
  for (int i = 0; i < index; i++)
    p = p->next;
  return p->data;
}

template <typename T> size_t SingleList<T>::size() const { return length; }

template <typename T> void SingleList<T>::print() const {
  std::cout << "SingleList: [";
  Node *p = head->next;
  while (p != nullptr) {
    std::cout << p->data << (p->next ? "->" : "");
    p = p->next;
  }
  std::cout << "]\n";
}
