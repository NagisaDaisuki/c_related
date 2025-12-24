#include "unique_pointer.h"
#include <chrono>

long run_Fibonacci(long val)
{
  return val < 2 ? val : run_Fibonacci(val - 1) + run_Fibonacci(val - 2);
}

int main()
{
  const auto start{std::chrono::steady_clock::now()};
  const auto res = run_Fibonacci(42);
  const auto end{std::chrono::steady_clock::now()};
  const std::chrono::duration<double> elapsed_seconds{end - start};
  
  std::cout << "Fibonacci(42): " << res << "\nelapsed_seconds: ";
  std::cout << elapsed_seconds.count() << "s\n";
  
  return 0;
}
