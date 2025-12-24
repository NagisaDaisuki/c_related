#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
//#include <>

std::vector<int> Vec = {};

class numbered
{
  public:
    numbered(){
      mysn = genMysn();
    }

    numbered(const numbered& n)
    {
      mysn = genMysn();
    }

    numbered& operator=(const numbered&)=default;

    int genMysn()
    {
      int tmp = rand() % 100000;
      if(std::find(Vec.begin(),Vec.end(),tmp) != Vec.end())
        tmp = rand() % 100000;
      //mysn = rand() % 10000; //生成唯一序号
      //mysn = tmp;
      return tmp;
    }

    int getMysn() const
    {
      return mysn;
    }
  private:
    int mysn;

};
void f(const numbered& s)
{
    std::cout << s.getMysn() << std::endl;
}

void test01()
{
  numbered a,b = a,c = b;
  f(a);f(b);f(c);
}

int main()
{
  test01();
  return 0;
}
