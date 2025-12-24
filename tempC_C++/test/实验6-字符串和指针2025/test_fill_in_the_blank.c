#include <math.h>
#include <stdalign.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void strlen_end(void) {
  int len = 0;
  len = strlen("ab\n\\012\\\""); // a b \n \\ 012 \\ \"
  // len = 9
  printf("%d", len);
}

void test1(void) {
  char ch[] = "600";
  int a, s = 0;
  for (a = 0; ch[a] >= '0' && ch[a] <= '9'; a++) {
    s = 10 * s + ch[a] - '0';
  }
  printf("%d", s);
}

void test2(void) {
  char x[] = "the teacher";
  int i = 0;
  while (x[++i] != '\0') // 是否到字符串末尾
  {
    if (x[i - 1] == 't')
      printf("%c", x[i]);
  }
}

void test3(void) {
  int i;
  char a[] = "Time", b[] = "Tom";
  for (i = 0; a[i] != '\0' && b[i] != '\0'; i++) {
    if (a[i] == b[i]) {
      if (a[i] >= 'a' && a[i] <= 'z') // 小写字母判断(islower())
        printf("%c", a[i] - 32);      // toupper()
      else
        printf("%c", a[i] + 32); // tolower
    } else
      printf("*");
  }
}

void test4(void) {
  char a[2][6] = {"Sun", "Moon"};
  int i, j, len[2];
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 6; j++) {
      if (a[i][j] == '\0') {
        len[i] = j; // i = 0  j = 3 i = 1 j = 4
        break;
      }
    }
    printf("%s:%d\n", a[i], len[i]);
  }
}

void test5(void) {
  int i, r;
  char s1[80] = "bus", s2[80] = "book";
  for (i = r = 0; s1[i] != '\0' && s2[i] != '\0'; i++) {
    if (s1[i] == s2[i])
      i++;
    else {
      r = s1[i] - s2[i]; // s - o
      break;
    }
  }
  printf("%d", r);
}

#define LEN 4

void test6() {
  int j, c;
  char n[2][LEN + 1] = {"8980", "9198"};
  for (j = LEN - 1; j >= 0; j--) {
    c = n[0][j] + n[1][j] - 2 * '0'; // '0' + '8'

    n[0][j] = c % 10 + '0';
  }
  for (j = 0; j <= 1; j++)
    fputs(n[j], stdout); // fputs 不输出 \n
}

void test7() {
  int i = 5;
  char c[6] = "abcd";
  do {
    c[i] = c[i - 1]; // " abcd"
  } while (--i > 0);
  puts(c);
}

void test8() {
  char s[80];
  int i = 0;
  fgets(s, 80, stdin); // 自动添加

  while (s[i] != '\0') {
    if (s[i] <= 'z' && s[i] >= 'a')
      s[i] = 'z' + 'a' - s[i];
    i++;
  }
  puts(s);
}

void test9() {
  char s[] = "ABCCDA";
  int k;
  char c;

  for (k = 1; (c = s[k]) != '\0'; k++) {
    switch (c) {
    case 'A':
      putchar('%');
      continue;
    case 'B':
      ++k;
      break;
    default:
      putchar('*');
    case 'C':
      putchar('&');
      continue;
    }
    putchar('#');
  }
}

void test10() {
  int i = 0;
  char a[] = "abm", b[] = "aqid", c[10];
  while (a[i] != '\0' && b[i] != '\0') {
    if (a[i] >= b[i])
      c[i] = a[i] - 32;
    else
      c[i] = b[i] - 32;
    ++i;
  }
  c[i] = '\0';
  puts(c);
}

void test11() {
  int i;
  char str[10], temp[10] = "Control";
  for (i = 0; i < 4; i++) {
    fgets(str, 10, stdin);
    if (strcmp(temp, str) < 0)
      strcpy(temp, str);
  }
  puts(temp);
}

void test12() {
  char a[2][80];
  int i, j, m, n, l, max;
  for (i = 0; i <= 1; i++)
    fgets(a[i], 80, stdin);
  max = a[0][0];
  for (i = 0; i <= 1; i++) {
    l = strlen(a[i]);
    for (j = 0; j <= l; j++) {
      if (a[i][j] > max) {
        max = a[i][j];
        m = i;
        n = j;
      }
    }
  }
  printf("%c %d %d\n", max, m, n);
}

void call_test() {

  // strlen_end();
  // test1();
  // test2();
  // test3();
  // test4();
  // char ch1 = 's';
  // char ch2 = 'o';
  // printf("%d\n", ch1 - ch2);
  // test5();
  // test6();
  // test7();
  // test8();
  // test9();
  // test10();
  // test11();
  test12();
}

int main(void) {
  call_test();
  return 0;
}
