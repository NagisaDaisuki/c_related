#include <iostream>

class Base{

public:
  Base(){
    std::cout << "Base constructo\n";
    //在构造函数中调用虚函数
    virtualFunction();
  }
  virtual ~Base()
  {
    std::cout << "Base destructor\n";
    //在虚构函数中调用虚函数
    virtualFunction();
  }

  virtual void virtualFunction(){
    std::cout << "Base virtual function\n";
  }

};

class Derived : public Base{

public:
  Derived() {
      std::cout << "Derived constructor\n";
      virtualFunction();
  }

  ~Derived(){
      std::cout << "Derived destructor\n";
      virtualFunction();
  }

  void virtualFunction() override
  {
    std::cout << "Derived virtual function\n";
  } 
};

int main()
{
    Derived d;
    return 0;
}
