#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 10

typedef struct {
  int id;
  char gender;
  double avg_score;
  unsigned short int math_score;
  unsigned short int eng_score;
  char name[LENGTH];

} Students;

Students *initialize_students(int n) {
  int i;
  Students *class = (Students *)calloc(sizeof(Students), n);

  if (class == NULL)
    return NULL;

  for (i = 0; i < n; i++) {
    if (fscanf(stdin, "%d %s %c %hu %hu", &class[i].id, class[i].name,
               &class[i].gender, &class[i].math_score,
               &class[i].eng_score) != 5)
      return NULL;
    // 判断 %c 是否溢出
    class[i].avg_score = (double)(class[i].math_score + class[i].eng_score) / 2;
  }

  return class;
}

void sort_with_avg(Students *class, int n) {
  for (int gap = n / 2; gap > 0; gap /= 2) {
    for (int i = gap; i < n; i += 1) {
      Students temp = class[i];

      int j;
      for (j = i; j >= gap && class[j - gap].avg_score < temp.avg_score;
           j -= gap)
        class[j] = class[j - gap];
      class[j] = temp;
    }
  }
}

void sort_with_name(Students *class, int n) {
  for (int gap = n / 2; gap > 0; gap /= 2) {
    for (int i = gap; i < n; i += 1) {
      Students temp = class[i];

      int j;
      for (j = i; strncmp(class[j - gap].name, temp.name, LENGTH) > 0; j -= gap)
        class[j] = class[j - gap];
      class[j] = temp;
    }
  }
}

void print_class(Students *class, int n) {
  for (int i = 0; i < n; i++) {
    fprintf(stdout, "%d %s %c %hu %hu %.1lf\n", class[i].id, class[i].name,
            class[i].gender, class[i].math_score, class[i].eng_score,
            class[i].avg_score);
  }
}

void print_avg(Students *class, int n) {
  int sum_math, sum_eng;
  sum_math = sum_eng = 0;
  double avg_math, avg_eng;
  avg_math = avg_eng = 0.0;
  for (int i = 0; i < n; i++) {
    sum_math += class[i].math_score;
    sum_eng += class[i].eng_score;
  }

  avg_math = (double)sum_math / n;
  avg_eng = (double)sum_eng / n;

  fprintf(stdout, "%.1lf %.1lf\n", avg_math, avg_eng);
}

int main(void) {

  int n = 0;
  if (fscanf(stdin, "%d", &n) != 1)
    return -1;
  Students *class = initialize_students(n);
  Students *class_avg = (Students *)calloc(sizeof(Students), n);
  Students *class_name = (Students *)calloc(sizeof(Students), n);
  memcpy(class_avg, class, sizeof(Students) * n);
  memcpy(class_name, class, sizeof(Students) * n);

  sort_with_avg(class_avg, n);
  print_class(class_avg, n);
  print_avg(class, n);
  sort_with_name(class_name, n);
  print_class(class_name, n);
  print_avg(class, n);

  free(class_name);
  free(class_avg);
  free(class);
  return 0;
}
