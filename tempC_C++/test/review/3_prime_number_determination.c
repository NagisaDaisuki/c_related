#include <math.h>
#include <stdio.h>

void prime_determination(void);
int is_prime(int n);

int main(void) {
  prime_determination();
  return 0;
}

int is_prime(int n) {
  if (n <= 1)
    return 0;
  if (n == 2)
    return 1;
  // performance optimization
  if (n % 2 == 0)
    return 0;

  for (int i = 2; i <= (int)sqrt(n); i++) {
    if (n % i == 0)
      return 0;
  }
  return 1;
}

void prime_determination(void) {
  int n = 0;
  fscanf(stdin, "%d", &n);
  if (is_prime(n))
    puts("Yes");
  else
    puts("No");
}
