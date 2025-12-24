#include <iostream>
#include <vector>
#include <cstring>

//template 
template<typename T>
std::size_t count(std::vector<T> const& vec,T value)
{
  auto count = 0u;
  for(auto const& elem : vec)
    if(value == elem) ++count;
  return count;
}

// template specialization
template<>
std::size_t count(std::vector<const char*> const& vec,const char* value)
{
  auto count = 0u;
  for(auto const& elem : vec)
    if(0 == strcmp(value,elem)) ++count;
  return count;
}

int main()
{
  std::vector<double> vd = {1.1,1.1,2.3,3.4,4.5};
  
  std::cout << "result: " << count(vd,1.1) << std::endl;
  
  std::vector<const char*> vcc = {"alan","walker","Brisk","shiny","Blue","Funky"};
  std::cout << "template specialization result: " << count(vcc,"Blue") << std::endl;
  return 0;
}
