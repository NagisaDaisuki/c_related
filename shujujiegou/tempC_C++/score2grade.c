#include <stdio.h>

int main(void) {
  int score;

  printf("Please enter score:");
  scanf("%d", &score);
  if (score >= 90 && score <= 100)
    printf("%d:A", score);
  else if (score >= 80 && score < 90)
    printf("%d:B", score);
  else if (score >= 70 && score < 80)
    printf("%d:C", score);
  else if (score >= 60 && score < 70)
    printf("%d:D", score);
  else if (score >= 0 && score < 60)
    printf("%d:E", score);
  else
    printf("Input error!");

  return 0;
}
