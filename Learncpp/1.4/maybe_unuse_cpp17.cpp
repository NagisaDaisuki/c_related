#include <iostream>

int main() {
  // Here's some math/physics values that we copy-pasted from elsewhere
  double pi{3.14159};
  double gravity{9.8};
  double phi{1.61803};

  std::cout << pi << '\n';  // pi is used
  std::cout << phi << '\n'; // phi is used

  // The compiler will likely complain about gravity being defined but unused.
  // And to address such cases, C++ 17 introduced the [[maybe_unused]]
  // attribute, which allows us to tell the compiler that we're okay with a
  // variable being unused. The compiler will not generate unused variable
  // warnings for such variables.

  [[maybe_unused]] double pi1{3.14159};
  [[maybe_unused]] double gravity1{9.8};
  [[maybe_unused]] double phi1{1.61803};
  // The compiler will no longer warn about variable not being used.
  return 0;
}
