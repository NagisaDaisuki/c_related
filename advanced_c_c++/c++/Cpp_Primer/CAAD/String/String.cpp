#include "String.h"
#include <algorithm>
#include <iostream>

std::pair<char*,char*>
String::alloc_n_copy(const char* b,const char* e)
{
  auto str = alloc.allocate(e - b);
  return {str,std::uninitialized_copy(b,e,str)};
}

void String::range_initializer(const char* first,const char* last)
{
    auto newstr = alloc_n_copy(first,last);
    elements = newstr.first;
    ends = newstr.second;
}

String::String(const char* s)
{
    char* s1 = const_cast<char*>(s);
    while(*s1)
      ++s1;
    range_initializer(s,++s1);
}

String::String(const String& rhs)
{
    range_initializer(rhs.elements,rhs.ends);
    std::cout << "copy constructor" << std::endl;
}

void String::free()
{
    if(elements)
    {
        std::for_each(elements,ends,[this](char& c)->void{
            alloc.destroy(&c);
        });
        alloc.deallocate(elements,ends - elements);
    }
}

String::~String()
{
    free();
}

String& String::operator=(const String& rhs)
{
    auto newdata = alloc_n_copy(rhs.elements,rhs.ends);
    free();
    elements = newdata.first;
    ends = newdata.second;
    std::cout << "copy-assignment" << std::endl;
    return *this;
}

int main()
{
    return 0;
}

