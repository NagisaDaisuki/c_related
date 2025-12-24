#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>

int main()
{
    std::string str = "#return #value #optimization";
    std::cout << "before: " << std::quoted(str) << '\n';
    
    std::cout << "after: \"";
    std::remove_copy(str.begin(),str.end(),std::ostream_iterator<char>(std::cout),'#');
    std::cout << "\"\n";
    
    return EXIT_SUCCESS;
}
