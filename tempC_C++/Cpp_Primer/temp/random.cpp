#include <iostream>
#include <random>

/*
    在C++中<random>头文件提供了用于生成随机数的功能。主要的函数和类包括以下几种

    1.随机数引擎(Random Number Engines)
      -std::random_device : 一个用于生成真随机数的设备，可以用于生成种子
      -std::default_random_engine : 一个伪随机数生成器引擎，通常使用梅森旋转算法(Mersense Twister)
      来实现
    2.分布(Distribution)
      -std::uniform_int_distribution : 生成指定范围内的均匀分布的整数
      -std::uniform_real_distribution : 生成指定范围内的均匀分布的浮点数
      -std::normal_distribution : 生成正态分布的随机数
      -std::binomial_distribution : 生成二项分布的随机数
    3.随机数生成
      -std::generate_canonical : 生成[0.1)范围内的均匀分布的浮点数
      -std::generate_seed : 生成一个用于随机数引擎的随机种子

*/

int main()
{
    std::random_device rd; // 随机设备，用于生成种子
    std::mt19937 gen(rd()); //使用梅森旋转算法的伪随机数生成器
    std::default_random_engine dre(rd()); //梅森旋转算法随机数生成器
    
    //定义一个均匀分布的整数分布器,范围为[1,6]
    std::uniform_int_distribution<> dis(1,6);

    //生成随机数字
    for(int i = 0;i < 10;++i)
    {
      std::cout << dis(dre) << " ";
    }
    std::cout << "\n";

    return 0;
    
}
