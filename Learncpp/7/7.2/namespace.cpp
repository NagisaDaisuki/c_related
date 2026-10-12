#include <iostream>

namespace Foo // define a namespace named Foo
{
int doSomething(int x, int y) { return x + y; }
} // namespace Foo

namespace Goo // define a namespace named Goo
{
int doSomething(int x, int y) { return x - y; }
void print() { std::cout << "Goo scope.\n"; }
} // namespace Goo

void print() { std::cout << "Global There.\n"; }

int main() {
  std::cout << Foo::doSomething(4, 3) << '\n';
  std::cout << Goo::doSomething(4, 3) << '\n';
  Goo::print(); // call print() in Goo namespace.
  ::print();    // call print() in global namespace
                // (same as just calling print() in this case.)
  return 0;
}
