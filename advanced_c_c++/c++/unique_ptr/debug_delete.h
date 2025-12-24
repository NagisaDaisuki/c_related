#ifndef DEBUG_DELETE_H
#define DEBUG_DELETE_H
#include <iostream>

/*
  @brief The DebugDelete class is a deleter functor using delete 
*/

class DebugDelete
{
  public:
    DebugDelete(std::ostream& s = std::cerr) : os(s){}
    template<typename T>
    void operator()(T* p) const 
    {
      os << "deleting ptr" << std::endl;
      delete p;
    }
  private:
    std::ostream& os;
};

#endif
