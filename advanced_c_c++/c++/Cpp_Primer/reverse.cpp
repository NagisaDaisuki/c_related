#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>


class Reverse_Iterator
{
  public:
    Reverse_Iterator(){}
    ~Reverse_Iterator(){}
  public:
    void rTest()
    {
      //使用反向迭代器
      //从尾元素到首元素的反向迭代器
      std::vector<int> vec = {0,1,2,3,4,5,6,7,8,9};
      for(auto r = vec.rbegin();r != vec.rend();r++)
      {
          std::cout << *r << std::endl;
      }

      //利用反向迭代器改变sort排序元素顺序
      std::sort(vec.begin(),vec.end()); //正常顺序 
      std::sort(vec.rbegin(),vec.rend()); //逆序排序
      
      

      //反向迭代器和其他迭代器之间的关系
      /*
        假设有一个名为line的string类型变量，保存着一个逗号分割的单词列表
        我们希望打印line中的第一个单词。使用find可以很容易完成这一任务
      */
      std::string line = "FIRST,MIDDLE,LAST";
      //std::istream_iterator<std::string> in(std::cin),eof;
      //std::copy(in,eof,std::back_inserter(line));

      //在一个逗号分割的列表中查找第一个元素
      auto comma = std::find(line.cbegin(),line.cend(),',');
      std::cout << std::string(line.cbegin(),comma) << std::endl;
      //如果line中有逗号，那么comma将指向这个逗号;否则它将等于line.cend()
      
      //在一个逗号分割的列表中查找最后一个元素
      //可以使用反向迭代器
      auto rcomma = std::find(line.crbegin(),line.crend(),',');
      //但是当尝试使用反向迭代器进行输出时，会生成错误的结果
      std::cout << std::string(line.crbegin(),rcomma) << std::endl;
      /*
        当我们使用反向迭代器时，会反向处理string
        所以上面的操作将string元素反向输出了
        如果需要正确获取最后一个元素，需要将rcomma换回一个普通
        迭代器，能在line中正向移动

        可以调用reverse_iterator的base成员函数来进行转换,这个成员函数会返回
        其对应的普通迭代器

      */
      std::cout << std::string(rcomma.base(),line.cend()) << std::endl;
      //这个结果就是我们预期的输出结果
      
      
      
    }
    
  private:

};

int main()
{
  //反向迭代器
  Reverse_Iterator t1;
  t1.rTest();

  return 0;

}
