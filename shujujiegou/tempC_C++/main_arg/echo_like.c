#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  /*
   *  打印参数，直到遇到NULL指针(未使用argc)，程序名被跳过。
   * */
  while (*++argv != NULL)
    printf("%s\t", *argv);
  printf("\n");
  return EXIT_SUCCESS;
}
