#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct student {
  char name[21];
  int score;
} Student;

void cal_lisan(void);

int main(void) {
  cal_lisan();
  return EXIT_SUCCESS;
}

void cal_lisan(void) {
  int n = 0;
  fscanf(stdin, "%d", &n);
  Student *class = (Student *)calloc(n, sizeof(Student));

  if (class == NULL) {
    perror("Failed to allocate memory!");
    return;
  }

  int i;
  float res, avg;
  res = avg = 0.0;
  for (i = 0; i < n; i++) {
    fscanf(stdin, "%s %d", class[i].name, &class[i].score);
    avg += class[i].score;
  }
  avg = (float)avg / n;
  for (i = 0; i < n; i++) {
    res += pow((class[i].score - avg), 2);
  }
  res = (float)1 / n * res;
  res = sqrt(res);

  fprintf(stdout, "%.2f\n", res);

  free(class);
}
