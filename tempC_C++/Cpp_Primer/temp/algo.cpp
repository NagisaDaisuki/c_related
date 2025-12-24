#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
int main()
{
  // 创建一个包含整数的向量
  std::vector<int> numbers = {1,2,3,4,5,6,7,8,9,10};
  
  // 使用std::find 查找特定元素
  int target = 5;
  auto it = std::find(numbers.begin(),numbers.end(),target);
  if(it != numbers.end())
    std::cout << "Element " << target << "found at index " 
    <<  std::distance(numbers.begin(),it)  << std::endl;
  else
    std::cout << "Element " << target << " not found" << std::endl;

  // 使用find_if 查找符合符合条件的元素
  auto even_number = std::find_if(numbers.begin(),numbers.end(),
      [](int n){
        return n % 2 == 0;
      }); // 找到第一个符合条件的值在容器中的位置(迭代器)

  if(even_number != numbers.end())
    std::cout << "First even number found: " << *even_number << std::endl;
  else 
    std::cout << "No even number found" << std::endl;
  
  // 使用 std::replace 替换特定元素
  std::replace(numbers.begin(),numbers.end(),5,50);

  // 使用 std::replace_if 根据条件替换元素
  std::replace_if(numbers.begin(),numbers.end()
      ,[](int n){
        return n > 5;
      },50);

  std::copy(numbers.begin(),numbers.end(),std::ostream_iterator<int>(std::cout,""));
  
  // 使用std::remove 删除特定元素
  std::remove(numbers.begin(),numbers.end(),0);

  // 使用std::remove_if 根据条件删除元素
  numbers.erase(std::remove_if(numbers.begin(),numbers.end(),
        [](int n){return n > 5;}),numbers.end()); // std::remove_if 返回第一个满足条件的numbers迭代器
  // 打印最终结果
  std::cout << "Final numbers: ";
  for(int num : numbers)
  {
    std::cout << num << " ";
  }
  std::cout << std::endl;
  return 0;

}
