#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student {
  int id;
  char name[10];
  char sex;
  float math, eng, avg;
} Student;

int compare_dict(const void *s1, const void *s2);
int compare_avg(const void *s1, const void *s2);

void score_manage();

int main(void) {
  score_manage();
  return EXIT_SUCCESS;
}

int compare_dict(const void *s1, const void *s2) {
  const Student *stu1 = (const Student *)s1;
  const Student *stu2 = (const Student *)s2;
  return strcmp(stu1->name, stu2->name);
}
int compare_avg(const void *s1, const void *s2) {
  const Student *stu1 = (const Student *)s1;
  const Student *stu2 = (const Student *)s2;
  if (stu1->avg < stu2->avg)
    return 1;
  if (stu1->avg > stu2->avg)
    return -1;
  return 0;
}

void score_manage() {
  int num_stu;
  float math_avg, eng_avg, math_sum, eng_sum;
  math_avg = eng_avg = math_sum = eng_sum = 0.0;
  if (scanf("%d", &num_stu) != 1)
    return;

  Student *class = (Student *)malloc(sizeof(Student) * num_stu);

  if (class == NULL) {
    free(class);
    return;
  }

  Student *p_cls;
  for (p_cls = class; p_cls < class + num_stu; p_cls++) {
    if (scanf("%d %s %c %f %f", &p_cls->id, p_cls->name, &p_cls->sex,
              &p_cls->math, &p_cls->eng) != 5)
      return;
    // scanf("%d %s %f %f", &p_cls->id, p_cls->name, &p_cls->math, &p_cls->eng);
    math_sum += p_cls->math;
    eng_sum += p_cls->eng;

    p_cls->avg = (float)(p_cls->math + p_cls->eng) / 2;
  }
  qsort(class, num_stu, sizeof(Student), compare_avg);
  math_avg = (float)math_sum / num_stu;
  eng_avg = (float)eng_sum / num_stu;

  for (p_cls = class; p_cls < class + num_stu; p_cls++) {
    printf("%d %s %c %.0f %.0f %.1f\n", p_cls->id, p_cls->name, p_cls->sex,
           p_cls->math, p_cls->eng, p_cls->avg);
  }
  printf("%.1f %.1f\n", math_avg, eng_avg);

  qsort(class, num_stu, sizeof(Student), compare_dict);
  for (p_cls = class; p_cls < class + num_stu; p_cls++) {
    printf("%d %s %c %.0f %.0f %.1f\n", p_cls->id, p_cls->name, p_cls->sex,
           p_cls->math, p_cls->eng, p_cls->avg);
  }
  printf("%.1f %.1f\n", math_avg, eng_avg);

  free(class);
}
