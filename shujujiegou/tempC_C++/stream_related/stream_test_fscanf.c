#include <stdio.h>
#include <stdlib.h>

int main(void) {

  int a, b, c;
  a = b = c = 0;
  FILE *f = (FILE *)fopen("./test.txt", "r+");
  FILE *f1 = (FILE *)fopen("./testout.txt", "r+");
  if (f == NULL || f1 == NULL) {
    perror("Failed to read from stream test.txt.\n");
    return EXIT_FAILURE;
  }

  if (fscanf(f, "%d %d", &a, &b) ==
      2) { // 这里如果接收的不是两个整型变量就会导致循环终止，且fscanf跳过空白字符，
           // 所以它没有办法验证这两个值是位于同一行还是分属于两个不同的输入行
    fprintf(stdout, "Two number i got from stream f to stdout is %d - %d\n", a,
            b);
  }

  // 重置文件指针到文件开头
  rewind(f);

  int nfield = fscanf(f, "%4d %4d %4d", &a, &b, &c);
  if (nfield == 2)
    fprintf(f1, "Two number i got from stream f to f1 is %d - %d", a, b);
  else if (nfield == 3)
    fprintf(f1, "Three number i got from stream f to f1 is %d - %d - %d", a, b,
            c);

  fclose(f1);
  fclose(f);
  return 0;
}
