#include <iostream>
#include <memory>
#include <cassert>
struct Foo 
{
  Foo() { std::cout << "Foo..." << '\n'; }
  ~Foo() { std::cout << "~Foo..." << '\n'; }
};

template<typename T>
struct D 
{
  void operator()(T* p)
  {
    std::cout << "Calling delete for Foo object... \n";
    delete p;
  }
};

int main()
{
  std::cout << "Creating new Foo..." << '\n';
  std::unique_ptr<Foo,D<Foo>> up(new Foo(),D<Foo>());
  
  std::cout << "Replace owned Foo with a new Foo.... \n";
  up.reset(new Foo()); // calls deleter for the old one 
  
  std::cout << "Release and delete the owned Foo.... \n";
  up.reset(nullptr);
  
  assert(up == nullptr);
  return 0;

}

