#include <cstdio>
#include <iostream>

long long fibonacci_iterative(int n) {
  if (n <= 1)
    return n;

  long long a = 0;
  long long b = 1;
  long long result = 0;

  for (int i = 2; i <= n; ++i) {
    result = a + b;
    a = b;
    b = result;
  }
  return result;
}

int main(void) {
  int num;
  std::cout << "Enter a number to find its Fibonacci value (iterative): ";
  std::cin >> num;

  if (num < 0)
    std::cout << "Invalid input. Please enter a non-negative number."
              << std::endl;
  else
    std::cout << "Fibonacci(" << num << ") = " << fibonacci_iterative(num)
              << std::endl;
  return 0;
}
