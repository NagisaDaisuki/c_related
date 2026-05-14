#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

const int BLOOM_SIZE = 1000003; // 布隆过滤器大小，取一个较大的质数
const int HASH_NUM = 3;

int P[HASH_NUM] = {31, 131, 1313};

class BloomFilter {
private:
  std::vector<bool> bitset;

public:
  BloomFilter() { bitset.resize(BLOOM_SIZE, false); }

  int hashFunc(const std::string &s, int p) {
    long long hashcode = 0;

    for (char ch : s) {
      int ccode = (int)ch;

      if (ccode < 0) {
        ccode += 100;
      }

      hashcode = (hashcode * p + ccode) % BLOOM_SIZE;
    }
    return (int)hashcode;
  }

  void insert(const std::string &s) {
    for (int i = 0; i < HASH_NUM; i++) {
      int index = hashFunc(s, P[i]);
      bitset[index] = true;
    }
  }

  bool query(const std::string &s) {
    for (int i = 0; i < HASH_NUM; i++) {
      int index = hashFunc(s, P[i]);

      if (!bitset[index]) // 只要有一个哈希值与 bitset里存储的不同
        return false;     // 就不会重名，返回false
    }

    return true; // 三个哈希值都正确，重名，返回true
  }
};

int main() {
  BloomFilter bloom;

  std::string registeredLine;
  std::string queryLine;

  getline(std::cin, registeredLine);
  getline(std::cin, queryLine);

  std::stringstream ss1(registeredLine);
  std::string username;

  while (ss1 >> username) {
    bloom.insert(username);
  }

  std::stringstream ss2(queryLine);

  bool firstOutput = true;

  while (ss2 >> username) {
    if (!firstOutput) {
      std::cout << " ";
    }

    if (bloom.query(username)) {
      std::cout << "yes";
    } else {
      std::cout << "no";
    }

    firstOutput = false;
  }

  return EXIT_SUCCESS;
}
