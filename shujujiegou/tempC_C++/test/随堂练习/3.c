#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
  char name[10];
  unsigned int score;
} Score;

#define ASSIGN_ARR(ARR, SIZE)                                                  \
  do {                                                                         \
    int __i;                                                                   \
    for (__i = 0; __i < (SIZE); __i++) {                                       \
      if (scanf("%s %u", (ARR)[__i].name, &(ARR)[__i].score) != 2) {           \
        fprintf(stderr, "Error reading input.\n");                             \
        abort();                                                               \
      }                                                                        \
    }                                                                          \
  } while (0)

#define PRINT_ARR(ARR, SIZE)                                                   \
  do {                                                                         \
    int __i;                                                                   \
    for (__i = 0; __i < (SIZE); __i++) {                                       \
      fprintf(stdout, "%s %u", (ARR)[__i].name, (ARR)[__i].score);             \
      fprintf(stdout, "\n");                                                   \
    }                                                                          \
  } while (0)

void bubble_sort(Score *arr, int n) {
  int i, j;
  for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - 1 - i; j++) {
      if (arr[j].score < arr[j + 1].score) {
        Score temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }

      if (arr[j].score == arr[j + 1].score) {
        if (strcmp(arr[j].name, arr[j + 1].name) > 0) {
          Score temp = arr[j];
          arr[j] = arr[j + 1];
          arr[j + 1] = temp;
        }
      }
    }
  }
}

int main(void) {
  int n = 0;
  if (scanf("%d", &n) != 1)
    return -1;
  Score *students = (Score *)calloc(sizeof(Score), 5);

  if (students == NULL) {
    fprintf(stderr, "Memory allocate failed.\n");
    return -1;
  }

  ASSIGN_ARR(students, n);
  bubble_sort(students, n);
  PRINT_ARR(students, n);
  return 0;
}
