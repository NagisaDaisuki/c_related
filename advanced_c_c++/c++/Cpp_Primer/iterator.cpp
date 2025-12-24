#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main()
{
    //创建一个 vector 来存储输入内容
    std::vector<int> numbers;
    

    //从控制台读取整数，直到遇到文件结束符或非整数输入为止
    std::cout << "Enter integers (Press Ctrl+D on Unix/Linux,Ctrl+Z on Windows: )\n";
    std::copy(std::istream_iterator<int>(std::cin), //输入迭代器
              std::istream_iterator<int>(), //结束迭代器，指示输入结束
              std::back_inserter(numbers)); //输出迭代器，用于将输入内容插入到vector中

    //输出存储的整数
    std::cout << "You entered: ";
    std::copy(numbers.begin(),numbers.end(),std::ostream_iterator<int>(std::cout," "));
    std::cout << std::endl;
    return 0;
}
