#include <stdio.h>
#include <string.h>

typedef struct {
  char name[30];
  int grade;
} STUDENT;

STUDENT class[40] = {"xiaoMing", 80, "xiaoQiang", 70, "xiaoHong", 90};

void sortClass(STUDENT st[], int nst);
void swap(STUDENT *p1, STUDENT *p2);

int main() {
  int n = 3, i;
  sortClass(class, n);
  for (i = 0; i < 3; i++) {
    printf("%s %d\n", class[i].name, class[i].grade);
  }
  return 0;
}

void sortClass(STUDENT st[], int nst) {
  int i, j, pick;
  for (i = 0; i < (nst - 1); i++) {
    pick = i;
    for (j = i + 1; j < nst; j++) {
      if (st[j].grade > st[pick].grade)
        pick = j;
    }
    if (pick != i)
      swap(&st[i], &st[pick]);
  }
}

void swap(STUDENT *p1, STUDENT *p2) {
  STUDENT temp;
  temp = *p1;
  *p1 = *p2;
  *p2 = temp;
}
