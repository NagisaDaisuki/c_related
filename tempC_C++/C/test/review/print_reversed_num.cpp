#include <iostream>

int reverse(int n);

int main(void) {
  int n, rn;
  std::cin >> n;
  rn = reverse(n);
  std::cout << rn;
  return 0;
}
int reverse(int n) {
  int temp = n % 10;
  n /= 10;
  while (temp == 0) {
    temp = n % 10;
    n /= 10;
  }
  int res = 0;
  res = res * 10 + temp;
  while (n != 0) {
    temp = n % 10;
    res = res * 10 + temp;
    n /= 10;
  }
  return res;
}
