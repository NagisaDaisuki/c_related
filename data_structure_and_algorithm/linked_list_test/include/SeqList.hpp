#pragma once
#include <iostream>
#include <memory> // 引入 memory 头文件使用智能指针
#include <stdexcept>

template <typename T> class SeqList {
private:
  // 管理动态数组的专属智能指针
  std::unique_ptr<T[]> data;
  size_t length;
  size_t capacity;

  // 扩容机制更改
  void resize() {
    capacity *= 2;
    // 使用 make_unique 安全地开辟新数组 自动零初始化
    auto newData = std::make_unique<T[]>(capacity);

    // 使用 std::move转移旧元素，而不是无脑拷贝
    // 如果 T 是一个很大的对象（比如std::string），move能做到 零拷贝
    for (size_t i = 0; i < length; ++i) {
      newData[i] = std::move(data[i]);
    }

    // 老大交接！直接把 newData 的所有权交给 data
    // 旧的 data 指向的内存在这一瞬间会被 unique_ptr 自动且无情地销毁！
    data = std::move(newData);
  }

public:
  // 构造函数：直接用 make_unique 在堆上捏出数组
  SeqList(size_t init_cap = 10) : length{0}, capacity{init_cap} {
    data = std::make_unique<T[]>(capacity);
  }

  // 析构函数不需要了，因为智能指针 unique_ptr 已经帮我们把事情办好了
  // 只要显式声明一下析构函数
  ~SeqList() = default;

  // 增
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

  // 删
  void remove(size_t index) {
    if (index >= length)
      throw std::out_of_range("Remove index out of range");

    // 数据整体前移 O(n)
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
    std::cout << "SeqList：[";
    for (size_t i = 0; i < length; ++i) {
      std::cout << data[i] << (i == length - 1 ? "" : ", ");
    }
    std::cout << "]\n";
  }
};
