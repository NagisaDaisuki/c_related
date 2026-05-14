#include <iostream>
#include <random>
#include <vector>

class GenRandomNum {
private:
  std::mt19937 gen;

public:
  GenRandomNum() : gen(std::random_device{}()) {}

  std::vector<int> genInt(size_t count = 10, int left = 1, int right = 10000);
  std::vector<double> genDouble(size_t count = 10, double left = 1.00,
                                double right = 10000.00);
  template <typename T> void printVec(const std::vector<T> &vec) const;
};

std::vector<int> GenRandomNum::genInt(size_t count, int left, int right) {
  std::vector<int> vec;

  return vec;
}

std::vector<double> GenRandomNum::genDouble(size_t count, double left,
                                            double right) {}

template <typename T>
void GenRandomNum::printVec(const std::vector<T> &vec) const {}
