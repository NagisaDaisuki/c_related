#include <iostream>
#include <algorithm>
#include <memory>
#include <iterator>
#include <vector>
#include <string>

struct 
{
    bool operator()(int a,int b) const { return a < b; }
}CustomLess;


int main()
{
    std::vector<int> vec{1,34,231,2135,213,322,312,532,23,57,88};
    std::sort(vec.begin(),vec.end(),CustomLess);
    //std::sort(vec.begin(),vec.end(),[](int a,int b){
    // return a < b;  });
    //std::sort(vec.begin(),vec.end(),std::greater<int>());
    std::copy(vec.begin(),vec.end(),std::ostream_iterator<int>(std::cout," "));
    
    return EXIT_SUCCESS;
}
