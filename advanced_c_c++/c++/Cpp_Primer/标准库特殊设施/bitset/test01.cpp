#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>
#include <memory>




void test02()
{
  std::vector<int> vec = {0};
  
}

int main()
{
  std::vector<int> vec = {1,2,3,5,8,13,21};
  std::bitset<32> bitvec;
  {
    //第一种方法
    for(const auto e : vec)
    {
      bitvec.set(e);
    }
  }
  {
    // 第二种方法
    unsigned long quiz;
    for(const auto e : vec)
    {
      quiz |= (0UL << e);
    }
    bitvec = std::bitset<32>(quiz);
  }
  
}
