#include <iostream>
#include <bitset>

/*
  bitset类使得位运算的使用更为容易

*/

// 定义和初始化bitset

// 用unsigned 值初始化bitset
void test01()
{
  // bitset 是一个类模板，它类似array类，具有固定的大小
  std::bitset<32> bitvec(1U); // 32 位，低位为1，其他位为0

  // 当定义一个bitset时，需要声明它包含多少个二进制位: 
  //std::bitset<num>
  // num必须是一个常量表达式

  // 当我们使用一个整型值来初始化bitset时，此值被转换为unsigned long long 
  // 类型并被当作位模式来处理
  // 如果bitset的大小大于一个unsigned long long 中的二进制数
  // 则剩余的高位被置为0
  // 如果bitset的大小小于一个unsigned long long 中的二进制位数
  // 则只使用给定值中的低位
  // 超出bitset大小的高位被丢弃
  
  // bitvec1 比初始值小,初始值中的高位被丢弃
  std::bitset<13> bitvec1(0xbeef); // 二进制位序列为 1111 0111 01111
  // bitvec2 比初始值大,它的高位被置为0
  std::bitset<20> bitvec2(0xbeef); // 二进制位序列为 0000 1011 1110 1110 1111 
  // 在64位机器中，long long 0ULL 是64个0比特，因此~0ULL 是64个1
  std::bitset<128> bitvec3(~0ULL); // 0-63 位为1,63-127 位为0
}

// 从一个string 初始化 bitset
void test02()
{
  // 我们可以从一个string 或一个字符数组指针来初始化bitset
  // 两种情况下，字符都直接表示位模式
  // 当使用字符串表示数时，字符串中下标最小的字符对应高位,反之亦然
  
  std::bitset<32> bitvec4("1100"); // 2,3两位为1,剩余两位为0
  // 如果string包含的字符数比bitset少，则bitset的高位被置为0


  // 可以使用string中的子串作为初始值
  std::string str("1111111000000011001010101");
  std::bitset<32> bitvec5(str,5,4); // 从str[5]开始的四个二进制位,1100 
  std::bitset<32> bitvec6(str,str.size() - 4); // 使用最后四个字符 0101
}


// bitset 操作
// bitset 操作定义了多种检测或设置一个或多个二进制位的方法


void test03()
{
  std::bitset<32> bitvec(1U); // 32位，低位为1,剩余位为0
  bool is_set = bitvec.any(); // true,因为有1位置位
  bool is_not_set = bitvec.none(); // false,因为有1位置位
  bool all_set = bitvec.all(); // false，因为只有1位置位
  size_t onBits = bitvec.count(); // 返回 1
  size_t sz = bitvec.size(); // 返回 32 size()是一个constexpr函数，因此可以用在
  // 要求常量表达式的地方

  bitvec.flip(); // 翻转bitvec中的所有位
  bitvec.reset(); // 将所有位复位
  bitvec.set(); // 将所有位置位
}

void test04()
{
  std::bitset<32> bitvec(1U);
  bitvec.flip(0); // 翻转第一位
  bitvec.set(bitvec.size() - 1); // 置位最后一位
  bitvec.set(0,0); // 复位第一位
  //bitvec.reset(i); // 复位第i位
  bitvec.test(0); // 返回false ，因为第一位是复位的
  // test函数测试bitvec中指定位置是否为置位，是返回true,否则返回false
  
  
  bitvec[0] = 0; // 将第一位复位
  bitvec[31] = bitvec[0]; // 将最后一位设置为与第一位一样
  bitvec[0].flip(); // 和bitvec.flip()作用类似，翻转第一位
  ~bitvec[0]; // 等价操作，也是翻转第一位
  // 常用的逻辑操作都可以在bitset类型上操作
  bool b = bitvec[0];  // 将bitvec[0] 的值转换为bool类型
  

}

// 提取bitset的值
void test05()
{
  std::string m = "110101001010000101010";
  std::bitset<32> bitvec3(m.substr(1,5)); 
  unsigned long ulong = bitvec3.to_ulong();
  // 只有当bitset的大小小于对应的大小(to_ulong为unsigned long,to_ullong)
  // 为unsigned long long 时才能使用这两个操作
  std::cout << "ulong = " << ulong << std::endl;

  // bitset 的IO运算符
  // 输入运算符从一个输入流读取字符，保存到一个临时的string对象中
  // 直到读取的字符数达到对于bitset大小或是遇到非0或1的字符时，或者
  // 是遇到文件尾或输入错误时，读取过程停止
  // 随即用临时string对象初始化bitset
  std::bitset<16> bits;
  std::cin >> bits;
  std::cout << "bits: " << bits << std::endl;
}

// 使用bitset
void test06()
{

  bool status;
  unsigned long quizA = 0; // 此值被当作位集合使用
  quizA |= 1UL << 27; // 设置第27个学生通过了测试
  status = quizA & (1UL << 27); // 检查第27个学生是否通过了测试
  quizA &= ~(1UL << 27); // 取反 执行与等 ~(1UL << 27) 除了第27个其他都通过了测试
  // 使用标准库类bitset 完成等价的工作
  std::bitset<30> quizB; 
  quizB.set(27); 
  status = quizB[27]; 
  quizB.reset(27);  
}



int main()
{

  return 0;
}

