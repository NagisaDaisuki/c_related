#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <sstream>
#include <fstream>
#include <cstdio> 
#include <cstring>
#include <functional>
#include <algorithm>
#include <numeric>
#include <iterator>

/*
namespace Lambda_expression
{
  std::vector<std::string> strVec{"hello","name","beautify","aesthetic","sentiment"};
  // lambda表达式
  bool isShorter(const std::string& s1,const std::string& s2)
  {
    return s1.size() < s2.size();
  }

  void elimDups(std::vector<std::string> words)
  {
    std::stable_sort(words.begin(),words.end(),[](const std::string& s1,const std::string& s2){
            return s1.size() < s2.size();
            // 稳排(按字典序排列)
        });
    std::vector<std::string>::iterator it = std::unique(words.begin(),words.end()); //去重
    words.erase(it,words.end());
  }

  std::string make_plural(size_t ctr,const std::string& words,const std::string& ending)
  {
    return (ctr > 1) ? words + ending : words;
  }

  void biggies(std::vector<std::string>& words,std::vector<std::string>::size_type sz)
  {
    elimDups(strVec);
    auto wc = std::find_if(words.begin(),words.end(),[sz](const std::string& a){
          return a.size() >= sz;
        }); //对find_if 的调用返回一个迭代器，指向第一个参数长度不小于给定参数sz的元素
    // 如果这样的参数不存在，则返回words.end() 的一个拷贝
    auto count = words.end() - wc; // 计算满足 size >= sz 的元素的数量
    std::cout << count << " " << make_plural(count,"word","s") << " of length " << sz
      << " or longer" << std::endl;

    // 打印长度大于等于给定值的单词，每个单词后面接一个空格
    std::for_each(wc,words.end(),[](const std::string& s){ std::cout << s << " "; });
    std::cout << std::endl;

  }

  void test_find_if()
  {
    std::vector<int> numbers = {1,2,3,4,5,6,7,8,9,10};
    int target = 5;
    auto it = std::find_if(numbers.begin(),numbers.end(),[target](int val){
            return val > target;
        });
    if(it != numbers.end())
    {
      std::cout << "找打第一个大于" << target << "的元素: " << *it << std::endl;

    }
    else 
    {
      std::cout << "未找到满足条件的元素." << std::endl;
    }
  }

  void episode01()
  {
      // 已经使用过的可调用对象: 函数和函数指针
      // 还有两个可调用对象，重载了函数调用运算符的类和lambda表达式
      // 
      auto sum = [](int a,int b){ std::cout << a << " + " << b << " = " << a + b << '.'; return a + b; };
      int res = sum(1,2);
        
      std::function<int(int)> test = [res](int t){ return res + t; };
      // std::function是一个通用的函数封装器,可以用于存储任意可调用对象,包含函数指针、函数对象、成员函数
      // lambda表达式

  }

  template<typename Callable>
  void myFunction(Callable func)
  {
    func(3,4);
  }

  void test_temp()
  {
    // lambda表达式的类型有编译器根据其内容自动推断，通常可以使用auto关键字接受lambda表达式
    // 使用auto可以使得代码更灵活，因为它运行变量的类型根据初始化表达式自动推断

    // 1.std::function()
    auto lambda = [](int a,int b){ return a + b; };
    std::function<int(int,int)> func = lambda;
    
    // 使用std::function调用 lambda表达式
    int result = func(3,4);

    // 2.auto
    //3. 模板参数
    // 可以使用模板参数来接收lambda表达式，这样函数模板可以接受不用类型的lambda
    myFunction(lambda);
    
    // 4.函数指针
    // 如果lambda表达式没用捕获任何变量，可以将其转换为对应的函数指针类型
    int(*funcPointer)(int,int) = [](int a,int b){ return a + b; };

    // 使用函数指针调用lambda表达式
    int result1 = funcPointer(3,4);

  }

  void _Test_partition()
  {
    // std::partition 是algorithm头文件中的一个函数
    // 用于按照指定条件对容器进行划分(partition)
    // 具体来说，std::partition将满足条件的元素移动到容器的前部
    // 而不满足条件的元素移动到容器的后部，保持它们的相对顺序
    // std::partition 返回一个迭代器，该迭代器指向容器中第一个不满足划分条件的元素的位置

    std::vector<int> numbers = {1,2,3,4,5,6,7,8,9,10};

    //使用std::partition 将奇数移动到前部，偶数移动到后部
    auto it = std::partition(numbers.begin(),numbers.end(),[](int& num){
          return num % 2 != 0;
        }); //一元谓词(unary predicate)，函数形参列表值从输入序列中捕获
    std::sort(numbers.begin(),it);
    std::sort(it,numbers.end());
    // 输出划分后的结果
    std::cout << "Partitioned vector: ";
    for(auto iter = numbers.begin(); iter != it;++iter)
    {
      std::cout << *iter << " ";
    }
    std::cout << " | ";
    std::for_each(it,numbers.end(),[](int val){ std::cout << val << " "; });
    std::cout << std::endl;
    // 划分后的元素相对位置保持不变(在内存中的位置),只是根据划分条件的不同移动到了不同的位置

  }

  void _Test_transform()
  {
    // 在C++中，std::transform()是algorithm 头文件中的一个函数，用于对容器中的元素执行某个操作并将结果
    // 存储在另一个容器中
    // std::transform 接受两个或三个输入迭代器范围，并可选地提供一个目标容器的起始迭代器
    
    std::vector<int> source = {1,2,3,4,5};
    std::vector<int> destination;
    
    // 使用 std::transform 对每个元素执行乘法操作，并将结果存储到destination
    std::transform(source.begin(),source.end(),std::back_inserter(destination),[](int val)
        {
          return val * 2;
        });

    // 输出结果
    for(auto num : source)
      std::cout << num << " ";
    std::cout << "\nDoubled vector: ";
    std::for_each(destination.begin(),destination.end(),[](int val){ std::cout << val << " "; });

  }

  void _Test_count_if()
  {
    // 在C++中，"std::count_if"是algorithm头文件中的一个函数
    //用于计算满足指定条件的元素个数
    // std::count_if 接受两个迭代器参数和一个谓词函数
    // 返回满足条件的元素个数
    
    constexpr std::array v{1,2,3,4,5,6,7,8,9,10};
    std::cout << "v: ";
    std::copy(v.begin(),v.end(),std::ostream_iterator<int>(std::cout," "));
    std::cout << "\n";

    // determine how many integers match a target value.
    for(const int target : {3,4,5})
    {
      const int num_items = std::count(v.cbegin(),v.cend(),target);
      std::cout << "number: " << target << ", count: " << num_items << '\n';
    }

    // Use a lambda expression to count elements divisible by 4
    int count_div4 = std::count_if(v.begin(),v.end(),[](int i){ return i % 4 == 0; });
    std::cout << "numbers divisible by four: " << count_div4 << '\n';

    // A simplified version of 'distance' with 0(N) complexity 
    auto distance = [](auto first,auto last)
    {
      return std::count_if(first,last,[](auto){ return true; });
    };
    static_assert(distance(v.begin(),v.end()) == 10);
  }
  
  bool t(const std::string& s,std::string::size_type sz)
  {
    return s.size() >= sz;
  }
  
  std::ostream& t1(const std::string& s,std::ostream& os,char c)
  {
    return os << s << c;
  }


  void biggies(std::vector<std::string>& words,
            std::vector<std::string>::size_type sz,
            std::ostream& os = std::cout,char c = ' ')
  {
    elimDups(words);

    // 获取一个迭代器，指向第一个满足size >= sz 的元素
    auto wc = std::partition(words.begin(),words.end(),std::bind(t,std::placeholders::_1,sz));
    // 计算满足size >= sz的元素个数
    auto count = words.end() - wc;
   //  std::cout << count << " " >> make_plural(count,"word","s") << " of length" << 
     // sz << " or longer." << std::endl;
    
    //打印长度大于等于给定值的单词，每个单词后面接一个空格
    std::for_each(wc,words.begin(),std::bind(t1,std::placeholders::_1,std::cref(os),c));
    // 使用bind函数适配器重写lambda表达式
  }

  void biggies1(std::vector<std::string>& words,
            std::vector<std::string>::size_type sz,
            std::ostream& os = std::cout,char c = ' ')
  {
    elimDups(words);
    
    // 获取一个迭代器，指向第一个满足size>=sz的元素
    auto wc = std::partition(words.begin(),words.end(),[sz](std::string s)
        {
          return s.size() >= sz;
        });
    // 计算满足size >= sz的元素个数
    auto count = words.end() - wc;
    std::cout << count << " " << make_plural(count,"word","s") << 
      " of length" << sz << " or longer." << std::endl;
    // 打印长度大于等于给定值的单词，每个单词后面接一个空格
    std::copy(wc,words.end(),std::ostream_iterator<std::string>(std::cout," "));
    std::for_each(wc,words.end(),[&os,c](std::string& s)
        { 
          os << s << c;
        });
  }

}

*/

void test()
{
  // 使用流迭代器读取一个文本文件，存入一个vector中的string里
  
  // 打开文本文件
  std::ifstream file("./test.txt");

  // 检查文件是否成功打开
  if(!file.is_open())
  {
    std::cerr << "Error opening the file." << std::endl;
    return;
  }
  
  // 使用 std::istream_iterator 从文件中读取字符串直到文件末尾
  std::istream_iterator<std::string> fileIterator(file); // 文本文件输入流
  std::istream_iterator<std::string> endIterator; // eof
  
  // 使用迭代器将文件中的字符串存储到vector中
  std::vector<std::string> lines;//(fileIterator,endIterator);
  
  // 使用while循环读取每行文本
  while(fileIterator != endIterator)
  {
    lines.push_back(*fileIterator);
    ++fileIterator;
  }



  // 打印vector中的字符串
  std::cout << "Contents of vector: " << std::endl;
  
  for(const auto& line : lines)
  {
    std::cout << line << std::endl;
  }
  file.close();

}

int main()
{
    //Lambda_expression::_Test_count_if();
  test();  
  return 0;
}
