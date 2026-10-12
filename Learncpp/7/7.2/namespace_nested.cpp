#include <iostream>

namespace Foo {
namespace Goo { // Goo is a namespace inside the Foo namespace
int add(int x, int y) { return x + y; }
} // namespace Goo
} // namespace Foo

namespace Fooo::Gooo // Gooo is a namespace inside the Foo namespace (C++17
                     // style)
{
int add(int x, int y) { return x + y; }
} // namespace Fooo::Gooo

namespace Fooo // later need to add declarations to the Fooo namespace(only)
{
void someFcn() {} // This function is in Fooo only
} // namespace Fooo

int main(void) {
  std::cout << Foo::Goo::add(1, 2) << '\n';
  std::cout << Fooo::Gooo::add(1, 3) << '\n';
  return 0;
}