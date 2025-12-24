#include <iostream>
#include <string>
#include <vector>
#include <list> 
#include <tuple>

// 标准库占据了新标准文本将近三分之二的篇幅
// tuple、bitset、正则表达式以及随机数是标准库设施
// 中比较实用的

/*
  tuple是类似pair的模板。每个pair的成员类型都不相同
  但是每个pair都恰好有两个成员
  
  不同tuple类型的成员类型也不相同，但一个tuple可以有任意数量
  的成员
  每个确定的tuple类型的成员数目是固定的，但是一个tuple类型的成员数目可以与另一个tuple类型不同

*/

// 定义和初始化tuple
void test01()
{
  //当我们定义一个tuple 时，需要指出每个成员的类型
  std::tuple<size_t,size_t,size_t> threeD; //三个成员都设置为0
  std::tuple<std::string,std::vector<double>,int,std::list<int>> 
    someVal("constants",{3.14, 2.718},42,{0,1,2,3,4,5});
  // 使用tuple的默认构造函数，会对每个成员进行值初始化
  // 也可以像本例中初始化someval一样为每个成员提供一个初始值
  // tuple 的这个构造函数是explicit 
  // 因此我们必须使用直接初始化语法
  std::tuple<size_t,size_t,size_t> threeD1 = {1,2,3};  

  // 可以使用make_tuple 函数生成tuple对象
  auto item = std::make_tuple("0-999-s",3,20.00);
  //auto == std::tuple<const char*,int,double>
  // 类似make_pair，make_tuple 函数使用初始值的类型来推断tuple的类型
  
}

// 可以将tuple看作一个"快速而随意"的数据结构


// 访问tuple的成员
void test02()
{
  // 一个pair总是有两个成员,标准库可以为这两个成员分别命名为first和second
  
  // 要访问一个tuple的成员，就要使用一个名为get的标准库函数模板
  auto item = std::make_tuple("hello","world",2.00,2);
  auto first = std::get<0>(item);
  auto second = std::get<1>(item);
  auto third = std::get<2>(item);
  auto forth = std::get<3>(item);
  forth *= 0.8; // get返回指定成员的引用,修改forth同时修改tuple模板内第四个元素的参数
  

  // 如果不知道一个tuple准确的类型细节信息，可以用两个辅助类模板来查询tuple成员的数量和类型
  typedef decltype(item) trans;
  
  // 返回trans类型对象中成员的数量
  size_t sz = std::tuple_size<trans>::value; //返回4
  // cnt 的类型与item中第二个成员相同
  std::tuple_element<1,trans>::type cnt = std::get<1>(item);
  // cnt 是一个 const char*类型
  
  /*
    为了使用tuple_size 或tuple_element ，我们需要知道一个tuple对象的类型
    使用decltype确定tuple对象的具体类型
    
    std::tuple_size<T>::value 是一个public static 数据成员,表示给定tuple 中成员的数量
    std::tuple_element<num,T> 是一个public 类型成员 ,表示给定tuple类型中指定成员的类型
    类似get，tuple_element 所使用的索引也是从0开始计数的

*/
}

// 关系和相等运算符

// 类似容器的对应操作，只有两个tuple具有相同数量的成员时，我们才可以比较它们
// 为了使用tuple的相等或不等运算符，对每个成员使用== 运算符必须都是合法的
// 为了使用tuple的关系运算符,对每个成员使用< 必须都是合法的
void test03()
{
   std::tuple<std::string,std::string> duo("1","2");
   std::tuple<size_t,size_t> twoD(1,2);
   //bool b = (duo == twoD); //invalid operands to binary expression 
   std::tuple<size_t,size_t,size_t> threeD(1,2,3);
   //b = (twoD < threeD); //tuple objects can only be compared if they have equal element size
   std::tuple<size_t,size_t> origin(0,0);
   b = (origin < twoD);
}

// 使用tuple返回多个值
// tuple的一个常见用途是从一个函数返回多个值
// 例如记录多家连锁书店中的一家，每家书店都有一个销售记录文件
// 保存每本书近期的销售数据
// 我们可能希望在所有书店中 查询某本书的销售情况

class Sales_data;

// matches有三个成员: 一家书店的索引和两个指向书店vector中元素的迭代器
typedef std::tuple<std::vector<Sales_data>::size_type,
              std::vector<Sales_data>::const_iterator,
              std::vector<Sales_data>::const_iterator> matches;



void test04()
{
  
}


