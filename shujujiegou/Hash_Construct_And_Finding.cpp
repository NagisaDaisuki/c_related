#include <cstdlib>
#include <iostream>
#include <stdbool.h>
#include <stdexcept>
#include <vector>

const int Length = 11;
const int Hash_Length = 18;

template <class T> class Hash_Table {
private:
  std::vector<int> arr;
  int hash_table[Hash_Length];

public:
  Hash_Table();
  ~Hash_Table() = default;

  void Arr_Push_Back(const T &val);
  void Arr_Pop_Back();

  int My_Hash_Func(int K);

  bool Construct_Hash_Table();

  void Finding_Elem_On_Hash_Table(int elem);
};

template <typename T> Hash_Table<T>::Hash_Table() {
  arr = {};

  for (int i = 0; i < Hash_Length; i++) {
    hash_table[i] = -1;
  }
}

template <typename T> void Hash_Table<T>::Arr_Push_Back(const T &val) {
  arr.push_back(val);
}

template <typename T> void Hash_Table<T>::Arr_Pop_Back() { arr.pop_back(); }

template <typename T> int Hash_Table<T>::My_Hash_Func(int K) { return K % 16; }

template <typename T> bool Hash_Table<T>::Construct_Hash_Table() {
  for (int i = 0; i < Length; i++) {
    int key = arr.at(i);
    int pos = My_Hash_Func(key);

    int count = 0;

    while (hash_table[pos] != -1 && count < Hash_Length) {
      pos = (pos + 1) % Hash_Length;
      count++;
    }
    if (count >= Hash_Length)
      return false;
    hash_table[pos] = key;
  }
  return true;
}

template <typename T> void Hash_Table<T>::Finding_Elem_On_Hash_Table(int elem) {
  int pos = My_Hash_Func(elem);
  int compare_count = 1;
  int search_count = 0;

  while (hash_table[pos] != -1 && hash_table[pos] != elem &&
         search_count < Hash_Length) {
    pos = (pos + 1) % Hash_Length;
    compare_count++;
    search_count++;
  }

  if (hash_table[pos] == elem)
    std::cout << pos << " " << compare_count;
  else
    std::cout << -1 << " " << compare_count;
}

int main(void) {

  Hash_Table<int> *ht = new Hash_Table<int>;
  int temp{}, finding{};
  for (int i = 0; i < Length; i++) {
    if (std::cin >> temp && temp > 0)
      ht->Arr_Push_Back(temp);
    else
      ht->Arr_Push_Back(0);
  }

  if (!(std::cin >> finding && finding > 0)) {
    delete ht;
    throw std::out_of_range("Could not find a negative num.");
    return EXIT_FAILURE;
  }

  if (!ht->Construct_Hash_Table()) {
    std::cerr << "Construct Hash_Table failed";
    // perror("Construct Hash_Table failed");
    delete ht;
    return EXIT_FAILURE;
  }

  ht->Finding_Elem_On_Hash_Table(finding);

  delete ht;

  return EXIT_SUCCESS;
}
