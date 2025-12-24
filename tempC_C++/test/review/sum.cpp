#include <iostream>

int f(int n) {
  int sum;
  if (n == 1)
    sum = 1;
  else
    sum = f(n - 1) + n;
  return sum;
}

int main() {
  int n;
  std::cin >> n;
  std::cout << f(n);
  return 0;
}
