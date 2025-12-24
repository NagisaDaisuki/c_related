#include <stdio.h>
#include <stdlib.h>

int judge_if_per_num(int num);
void print_perfect_num_num();

int main(void) {
  print_perfect_num_num();
  return EXIT_SUCCESS;
}
int judge_if_per_num(int num) {
  int temp, count;
  temp = count = 0;
  while (num > 0) {
    temp = num % 10;
    if (temp == 6)
      count += 1;
    num /= 10;
  }
  if (count == 2)
    return 1;
  return 0;
}

void print_perfect_num_num() {
  int test_num = 0;
  if (scanf("%d", &test_num) != 1)
    return;

  int i, counter, temp;
  counter = temp = 0;
  for (i = 0; i < test_num; i++) {
    counter = temp = 0;
    if (scanf("%d", &temp) != 1 && temp <= 10 && temp >= 1000)
      return;
    if (temp < 66) {
      printf("0\n");
      continue;
    }

    int j;
    for (j = 66; j <= temp; j++)
      if (judge_if_per_num(j))
        counter++;
    printf("%d\n", counter);
  }
}
