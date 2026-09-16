#pragma once
#include <iostream>
#include <stdexcept>

template <typename T> class SeqList {
private:
  T *data;         // 指向堆区数组的指针
  size_t capacity; // 数组的最大容量
  size_t length;   // 当前真实数据个数

  // 私有扩容机制
  void resize() {
    capacity *= 2;
    T *newData = new T[capacity]{}; // 现代 C++ 初始化
    for (size_t i = 0; i < length; i++) {
      newData[i] = data[i];
    }
    delete[] data; // 释放老内存
    data = newData;
  }

public:
  // 构造与析构
  SeqList(size_t init_cap = 10) : capacity{init_cap}, length{0} {
    data = new T[capacity]{};
  }
  ~SeqList() { delete[] data; } // RAII 对象死亡时自动清理堆内存

  // 增：在 index 处插入（0 <= index <= length）
  void insert(size_t index, const T &val) {
    if (index > length)
      throw std::out_of_range("Insert index out of range");
    if (length == capacity)
      resize();

    // 数据整体后移 O(n)
    for (size_t i = length; i > index; --i) {
      data[i] = data[i - 1];
    }
    data[index] = val;

    length++;
  }

  // 删：删除 index 处的元素
  void remove(size_t index) {
    if (index >= length)
      throw std::out_of_range("Remove index out of range");

    // 数据整体前移
    for (size_t i = index; i < length; i++) {
      data[i] = data[i + 1];
    }
    length--;
  }

  // 改
  void update(size_t index, const T &val) {
    if (index >= length)
      throw std::out_of_range("Update index out of range");
    data[index] = val;
  }

  // 查
  T get(size_t index) const {
    if (index >= length)
      throw std::out_of_range("Get index out of range");
    return data[index];
  }

  // 打印
  void print() const {
    std::cout << "SeqList: [";
    for (size_t i = 0; i < length; ++i)
      std::cout << data[i] << (i == length - 1 ? "" : ", ");
    std::cout << "]\n";
  }
};
