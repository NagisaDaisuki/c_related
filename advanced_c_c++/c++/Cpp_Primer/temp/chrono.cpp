#include <chrono>
#include <iostream>

long Fibonacci(unsigned n)
{
  return n < 2 ? n : Fibonacci(n - 1) + Fibonacci(n - 2);
}

int main()
{
  const auto start{std::chrono::steady_clock::now()};
  const auto fb{Fibonacci(42)};
  const auto end{std::chrono::steady_clock::now()};
  const std::chrono::duration<double> elapsed_seconds{end - start};

  std::cout << "Fibonacci(42): " << fb << "\nElapsed time: ";
  std::cout << elapsed_seconds.count() << "s\n";
}
