#include <cmath>
#include <iomanip>
#include <iostream>

int main(void) {
  int a, b, c;

  std::cin >> a >> b >> c;

  if (a + b > c && a + c > b && b + c > a) {
    // 1. 计算半周长 (s)
    double s = (a + b + c) / 2.0;

    // 2. 计算面积 (Area)
    double area = std::sqrt(s * (s - a) * (s - b) * (s - c));

    // 3. 设置输出格式，保留两位小数
    std::cout << std::fixed << std::setprecision(2);

    // 4. 输出面积
    std::cout << area << std::endl;
  } else
    std::cout << "N" << std::endl;
  return 0;
}
