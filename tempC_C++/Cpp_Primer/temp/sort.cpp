#include <algorithm>
#include <array>
#include <functional>
#include <iostream>

//#define PARTIAL_SORT__
#define STABLE_SORT__

#ifdef PARTIAL_SORT__
void print(std::array<int,10>& s,int middle)
{
  for(int a : s)
    std::cout << a << ' ';
  std::cout << '\n';
  if(middle > 0)
  {
    while(middle-- > 0)
      std::cout << "--";
    std::cout << '^';
  }
  else if(middle < 0)
  {
    for(auto i = s.size() + middle;--i;std::cout << " ")
    {}

    for(std::cout << "^";middle++ < 0;std::cout << "--")
    {}
  }
  std::cout << '\n';
}

int main()
{
    std::array<int,10> s{5,7,4,2,8,6,1,9,0,3};
    print(s,0);
    std::partial_sort(s.begin(),s.begin() + 3,s.end());
    print(s,3);
    std::partial_sort(s.rbegin(),s.rbegin() + 4,s.rend());
    print(s,-4);
    std::partial_sort(s.rbegin(),s.rbegin() + 5,s.rend(),std::greater{});
    print(s,-5);
    return 0;
}
#endif

#ifdef STABLE_SORT__

int main()
{
    std::array<int,10> s{5,7,4,2,8,6,1,9,0,3};
    std::replace(s.begin(),s.end(),8,88);

    for(int a : s)
      std::cout << a << " ";
    std::cout << '\n';
    
    std::replace_if(s.begin(),s.end(),std::bind(std::less<int>(),std::placeholders::_1,5),55);

//    std::replace_if(s.begin(),s.end(),std::bind(std:less<int>(),std::placeholders::_1,5),55);

}

#endif

