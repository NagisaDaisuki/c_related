#include <iostream>
#include <memory>

/*
    原型:
      std::shared_ptr<T> lock() const noexcept;
      
      Creates a new std::shared_ptr that shares ownership of the managed object
      . If there is no managed object, i.e. *this is empty, 
      then the returned shared_ptr also is empty.

      Effectively returns expired() ? shared_ptr<T>() : shared_ptr<T>(*this),
      executed atomically.
*/

void observe(std::weak_ptr<int> weak)
{
    if(auto p = weak.lock())
      std::cout << "\tobserve() is able to lock weak_ptr<>, value = " << *p << '\n';
    else 
      std::cout << "\tobserve() is unable to lock weak_ptr<>\n";
}

int main()
{
    std::weak_ptr<int> weak;
    std::cout << "weak_ptr<> is not yet initialized\n";
    observe(weak);
    //scope 
    {
      auto shared = std::make_shared<int>(42);
      weak = shared;
      std::cout << "weak_ptr<> is initialized with shared_ptr\n";
      observe(weak);
    }
    std::cout << "shared_Ptr<> has been destructed due to scope exit\n";
    observe(weak);
    
    return 0;
}
