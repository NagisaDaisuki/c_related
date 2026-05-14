#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// hashcode = hashcode * P + ccode (ccode > 0)
// P 取 31 131 和 1313

#define BLOOM_SIZE 1000003
#define HASH_NUM 3
#define MAX_LINE 100000

int P[HASH_NUM] = {31, 131, 1313};

char bloom[BLOOM_SIZE];

int hashFunc(const char *s, int p) {
  long long hashcode = 0;

  for (int i = 0; s[i] != '\0'; i++) {
    int ccode = (int)s[i];

    if (ccode < 0)
      ccode += 100;

    hashcode = (hashcode * p + ccode) % BLOOM_SIZE;
  }

  return (int)hashcode;
}

void insert(const char *s) {
  for (int i = 0; i < HASH_NUM; i++) {
    int index = hashFunc(s, P[i]);
    bloom[index] = 1;
  }
}

int query(const char *s) {
  for (int i = 0; i < HASH_NUM; i++) {
    int index = hashFunc(s, P[i]);

    if (bloom[index] == 0) {
      return 0;
    }
  }
  return 1;
}

int main(void) {
  char *registeredLine = (char *)malloc(sizeof(char) * MAX_LINE);
  char *queryLine = (char *)malloc(sizeof(char) * MAX_LINE);

  if (registeredLine == NULL || queryLine == NULL) {
    return EXIT_FAILURE;
  }

  fgets(registeredLine, MAX_LINE, stdin);
  fgets(queryLine, MAX_LINE, stdin);

  registeredLine[strcspn(registeredLine, "\n")] =
      '\0'; // 把 fgets 加上的换行符替换成 字符串结束符
  queryLine[strcspn(queryLine, "\n")] = '\0';

  char *username = strtok(registeredLine, " ");

  while (username != NULL) {
    insert(username);
    username = strtok(NULL, " ");
  }

  username = strtok(queryLine, " ");

  int firstOutput = 1;

  while (username != NULL) {
    if (!firstOutput)
      fprintf(stdout, " ");

    if (query(username)) {
      printf("yes");
    } else {
      printf("no");
    }

    firstOutput = 0;
    username = strtok(NULL, " ");
  }

  free(registeredLine);
  free(queryLine);

  return EXIT_SUCCESS;
}
