#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

// return value 
// pointer to the managed object or nullptr if no object is owned
class Res 
{
  std::string s;
  public:
    Res(std::string arg) : s{std::move(arg)}
    {
      std::cout << "Res::Res(" << std::quoted(s) << ");\n";
    }
    
    ~Res()
    {
      std::cout << "Res::~Res();\n";
    }
  private:
    friend std::ostream& operator<<(std::ostream& os, Res const& r)
    {
      return os << "Res { s = " << std::quoted(r.s) << "; }";
    }
};

int main()
{
  std::unique_ptr<Res> up(new Res{"Hello world!"});
  Res* res = up.get();
  std::cout << *res << '\n';
}
