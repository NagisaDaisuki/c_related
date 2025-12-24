#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 10

typedef struct student {
  char name[LENGTH];
  unsigned short int score;
} Student;

static Student *initialize_class(int n);
static void print_Student(Student *class, int n);
static Student *sort_by_score_and_name(const Student *class, int n);

int main(void) {
  int n = 0;
  if (fscanf(stdin, "%d", &n) != 1)
    return -1;

  Student *class = initialize_class(n);
  Student *class_change = sort_by_score_and_name(class, n);

  // print_Student(class, n);
  print_Student(class_change, n);

  free(class_change);
  free(class);

  return 0;
}

static Student *sort_by_score_and_name(const Student *class_ori, int n) {
  Student *class = (Student *)malloc(sizeof(Student) * n);

  if (class == NULL)
    return NULL;

  memcpy(class, class_ori, sizeof(Student) * n);

  for (int gap = n / 2; gap > 0; gap /= 2) {
    for (int i = gap; i < n; i += 1) {
      Student temp = class[i];

      int j;
      // for (j = i; j >= gap && class[j - gap].score <= temp.score; j -= gap) {
      //   if (class[j - gap].score == temp.score) {
      //     if (strcmp(class[j - gap].name, temp.name) > 0)
      //       class[j] = class[j - gap];
      //   } else
      //     class[j] = class[j - gap];
      // }

      for (j = i; j >= gap; j -= gap) {
        Student prev = class[j - gap];

        // 统一的移动逻辑判断

        if (prev.score < temp.score) {
          class[j] = prev; // 移动
          continue;
        }

        if (prev.score == temp.score) {
          if (strcmp(prev.name, temp.name) > 0) {
            class[j] = prev;
            continue;
          }
        }

        break; // 停止内层循环
      }
      class[j] = temp;
    }
  }

  return class;
}

static void print_Student(Student *class, int n) {
  for (int i = 0; i < n; i++) {
    fprintf(stdout, "%s %hu\n", class[i].name, class[i].score);
  }
}

static Student *initialize_class(int n) {
  Student *class = (Student *)malloc(sizeof(Student) * n);

  if (class == NULL)
    return NULL;

  int i;
  for (i = 0; i < n; i++) {
    if (fscanf(stdin, "%s %hu", class[i].name, &class[i].score) != 2)
      return NULL;
  }
  return class;
}
