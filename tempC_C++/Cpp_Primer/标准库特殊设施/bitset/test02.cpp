#ifndef QUIZ 
#define QUIZ 

#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <utility>
#include <memory>
#include <algorithm>

// 定义一个数据结构,包含一个整形对象，记录一个包含10个问题的真假测验的解答

template<std::size_t M>
class Quiz 
{
  public:

  Quiz() = default;
  Quiz(std::string& s) : bitvec(s){}
  ~Quiz() = default;
  Quiz& operator=(const std::string& s)
  {
    bitvec(s);
    return *this;
  }

  void bitchange(std::pair<std::size_t,std::size_t> pair)
  {
    bitvec[pair.first] = pair.second;
  }
  
  void upgrade(unsigned long correct)
  {
    std::bitset<M> temp(correct);
    for(int i = 0;i < bitvec.size();i++)
    {
      std::cout << "position " << i 
        << ", result: " << (bitvec.test(i) == temp.test(i))
        << std::endl;
    }
  }

  private:
    std::bitset<M> bitvec;
};

template<typename T,std::size_t M>
void update(std::pair<T,T> pai,Quiz<M> q)
{
  if(!std::is_same_v<T,std::decay<std::size_t>>)
    return;
  //q[pai.first] = pai.second; // pai.second 如果检测到非0或1的值终止读取过程
  q.bitchange(pai);
}

int main()
{
  std::string s = "11010101";
  Quiz<10> q1 = s;

  std::pair<std::size_t,std::size_t> pai = std::make_pair(1,1);
  update(pai,q1);

  unsigned long correct = std::bitset<10>("0011001100").to_ulong();
  q1.upgrade(correct);
  return 0;
}

#endif 
