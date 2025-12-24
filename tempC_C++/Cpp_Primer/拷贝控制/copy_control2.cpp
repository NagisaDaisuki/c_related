#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <sstream>
#include <memory>
#include <algorithm>
#include <memory>

//行为像值的类

class HasPtr
{
  public:
    HasPtr(const std::string& s) : ps(new std::string(s)),i(0){}
    HasPtr(const HasPtr& h) : ps(new std::string(*h.ps)),i(h.i){}
    HasPtr& operator=(const HasPtr&);
    ~HasPtr(){ delete ps; }
  private:
    std::string* ps;
    int i;
};

HasPtr& HasPtr::operator=(const HasPtr& rhs) //right hand side
{
    auto newp = new std::string(*rhs.ps); //拷贝底层string
    delete ps; //释放旧内存
    ps = newp; //从右侧运算对象拷贝数据到本对象
    i = rhs.i;
    return *this; //返回本对象
}

/*
  当你编写一个赋值运算符时，一个好的模式是先将右侧运算对象拷贝到一个局部临时对象中
  当拷贝完成后，销毁左侧运算对象的现有成员就是安全的了。一旦左侧运算对象的资源被销毁
  就只剩下将数据从临时对象拷贝到左侧运算对象的成员中了
*/

//定义行为像指针的类

/*
  对于行为类似指针的类，我们需要为其定义拷贝构造函数和拷贝赋值运算符
  来拷贝指针成员本身而不是它指向的string。我们的类仍需要自己的析构函数
  来释放接受string参数的构造函数分配的内存

  但是析构函数不能单方面地释放关联的string。
  只有当最后一个指向string的HasPtr销毁时才可以释放string
  浅拷贝是这样的

*/


//将计数器保存在动态内存中，当创建一个对象时，也同时分配一个计数器
//当拷贝或赋值对象时，拷贝指向计数器的指针并递增计数器

//定义一个使用引用计数的类
class HasPtr
{
  public:
    HasPtr(const std::string& s) : ps(new std::string(s)),i(0),use(1){}
    HasPtr(const HasPtr& h) : ps(new std::string(*h.ps)),i(h.i),use(*h.use)
    {
      ++*use;
    }
    HasPtr& operator=(const HasPtr&);
    ~HasPtr()
    {
      if(--*use == 0) //如果引用计数变为0
      {
        delete ps;
        delete use;
      }
    }
  private:
    std::string *ps;
    int i;
    std::size_t *use;
};
/*
    拷贝赋值运算符与往常一样执行类似拷贝构造函数和析构函数的操作
    即: 它必须递增右侧运算对象的引用计数，并递减左侧运算对象的引用计数(在将临时对象赋值左
    侧运算对象前左侧运算对象执行析构操作)
    （而且赋值运算符必须处理自赋值）
*/
HasPtr& HasPtr::operator=(const HasPtr& rhs) //right hand side
{
  ++*rhs.use;  //递增右侧运算对象的引用计数
  if(--*use == 0) //递减本对象的引用计数
  {
    delete ps;
    delete use;
    //如果没有其他用户，释放本对象分配的成员
  }
  ps = rhs.ps; //直接浅拷贝
  i = rhs.i; //内置类型值拷贝
  use = rhs.use;
  return *this;
}

int main()
{

    return 0;
}
