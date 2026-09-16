#pragma once
#include <stdexcept>
#include <utility>
#include <vector>

template <typename T> class SeqStack {
private:
  std::vector<T> data;

public:
  SeqStack() = default;
  ~SeqStack() = default;

  // C++11 移动语义：支持右值引用，避免不必要的拷贝
  void push(const T &val) { data.push_back(val); }
  void push(T &&val) { data.push_back(std::move(val)); }

  void pop() {
    if (empty())
      throw std::underflow_error("Stack is empty");
    data.pop_back();
  }

  [[nodiscard]] T &top() {
    if (empty())
      throw std::underflow_error("Stack is empty");
    return data.back();
  }

  [[nodiscard]] const T &top() const {
    if (empty())
      throw std::underflow_error("Stack is empty");
    return data.back();
  }

  [[nodiscard]] bool empty() const noexcept { return data.empty(); }
  [[nodiscard]] size_t size() const noexcept { return data.size(); }
};
