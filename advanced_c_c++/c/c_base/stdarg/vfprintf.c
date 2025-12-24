#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void file_log(FILE *stream, const char *format, ...);

void remove_line(char *str);

int main(void) {
  const char *log = "app.log";
  FILE *fp = fopen(log, "w");
  if (fp == NULL) {
    fprintf(stderr, "Failed to open file %s,exit...", log);
    fclose(fp);
    exit(1);
  }

  char name[20], passwd[50];
  memset(name, 0, sizeof(name));
  memset(passwd, 0, sizeof(passwd));
  fputs("Please input Your Loginame: \n", stdout);
  fgets(name, sizeof(name) / sizeof(name[0]), stdin);
  remove_line(name);
  fputs("Please input Your LoginPasswd: \n", stdout);
  fgets(passwd, sizeof(passwd) / sizeof(passwd[0]), stdin);
  remove_line(passwd);

  file_log(fp, "Everything I found great was sunfaded.");
  file_log(fp, "LoginName: %s", name);
  file_log(fp, "LoginPasswd: %s", passwd);
  fclose(fp);
  return 0;
}

void file_log(FILE *stream, const char *format, ...) {
  va_list args;
  va_start(args, format);

  fprintf(stream, "LOG: ");
  // 使用vfprintf 将参数列表打印到指定的文件流
  vfprintf(stream, format, args);
  fprintf(stream, "\n");

  va_end(args);
}

void remove_line(char *str) {
  if (str == NULL)
    return;
  int size = strlen(str);
  if (size > 0 && str[size - 1] == '\n')
    str[size - 1] = '\0';
}
