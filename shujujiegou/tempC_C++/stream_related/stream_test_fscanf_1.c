#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 100 // 要处理的最长行

void function(FILE *input) {}

int main(int argc, char *argv[]) {

  // if (argc == 0) {
  //   perror("Failed to receive file from argv.\n");
  //   return EXIT_FAILURE;
  // }

  char file1[BUFFER_SIZE] = {};
  if (argc > 1) {
    strncpy(file1, argv[1], BUFFER_SIZE - 1);
    file1[BUFFER_SIZE - 1] = '\0';
  } else {
    perror("Failed to receive file from argv.\n");
    return EXIT_FAILURE;
  }
  printf("要使用的文件名/路径是: [%s]\n", file1);

  return 0;
}
