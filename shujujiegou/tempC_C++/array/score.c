#include <stdio.h>

int main(void) {
  float score[][4] = {{60, 70, 80, 90}, {56, 89, 67, 88}, {34, 78, 90, 66}};
  float *search(float (*pointer)[4], int n);
  float *p;
  int i, k;
  char ch;

  scanf("%d", &k); // 输入要查找的学生序号
  while ((ch = getchar()) != '\n' && ch != EOF)
    ;
  printf("The scores of No.%d are:\n", k);
  p = search(score, k); // 返回 score[k][0]的地址
  for (i = 0; i < 4; i++) {
    printf("%-5.2f ", *(p + i));
  }

  printf("\n");

  return 0;
}

float *search(float (*pointer)[4], int n) {
  float *pt;
  pt = pointer[n];
  return pt;
}
