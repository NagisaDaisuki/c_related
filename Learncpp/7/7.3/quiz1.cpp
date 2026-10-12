#include <iostream>

int main() {
  int smaller;
  int larger;

  std::cout << "Enter an integer: ";
  std::cin >> smaller;
  std::cout << "Enter a larger integer: ";
  std::cin >> larger;
  {
    int temp;
    if (smaller > larger) {
      temp = smaller;
      smaller = larger;
      larger = temp;
    }
  }
  std::cout << "Swapping the values\n";
  std::cout << "The smaller value is " << smaller << '\n';
  std::cout << "The larger value is " << larger << '\n';
  return 0;
}