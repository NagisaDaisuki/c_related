#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 10
#define N 5

void SortString(char *ptr[], int n);

int main(void) {
  int i, n;
  char name[N][MAX_LEN]; // 定义二维字符数组
  char *pStr[N];         // 定义字符指针数组
  scanf("%d", &n);

  char ch;
  while ((ch = getchar()) != '\n' && ch != EOF)
    ;

  for (i = 0; i < n; i++) {
    pStr[i] = name[i]; // 让 pStr[i] 指向二维字符数组的name的第i行
    fgets(pStr[i], MAX_LEN, stdin);
  }
  SortString(pStr, n);
  printf("Sorted results:\n");
  for (i = 0; i < n; i++) {
    fputs(pStr[i], stdout);
  }
  return EXIT_SUCCESS;
}

void SortString(char *ptr[], int n) {
  int i, j;
  char *temp;

  for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - 1 - i; j++) {
      if (strcmp(ptr[j], ptr[j + 1]) > 0) {
        temp = ptr[j];
        ptr[j] = ptr[j + 1];
        ptr[j + 1] = temp;
      }
    }
  }
}
