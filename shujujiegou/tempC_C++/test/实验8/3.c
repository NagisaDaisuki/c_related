#include <stdio.h>

struct man {
  char name[20];
  int age;
} person[] = {"li-ming", 18, "wang-hua", 19, "zhang-ping", 20};

int main() {
  int i, j, max, min;
  max = min = person[0].age;

  for (i = 1; i < 3; i++) {
    if (person[i].age > max)
      max = person[i].age;
    else if (person[i].age < min)
      min = person[i].age;
  }

  for (i = 0; i < 3; i++) {
    if (person[i].age != max && person[i].age != min) {
      printf("%s,%d\n", person[i].name, person[i].age);
      break;
    }
  }
  return 0;
}
