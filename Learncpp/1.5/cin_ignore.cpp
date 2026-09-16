#include <cstdlib>
#include <iostream>
#include <limits> // std::numeric_limits
#include <string>

int main(void) {
  int age{};       // direct line initialization
  std::cin >> age; // get value from default input device and temporarily
                   // preserved on the buttom of input buffer area.
  // and when you entered the Enter key operation system will put the whole line
  // of data to the cin buffer of C++.

  // diminish the buffer area
  // ignore any of characters until this function swallow a char '\n'.
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::string name{};
  std::getline(
      std::cin,
      name); // now you can safely waiting user to input the entire line name.
  return EXIT_SUCCESS;
}
