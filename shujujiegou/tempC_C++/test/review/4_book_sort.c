#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct book {
  char name[100];
  int year;
  float price;
} Book;

void book_sort(void);

int main(void) {
  book_sort();
  return 0;
}

void book_sort(void) {
  int n = 0;
  scanf("%d", &n);
}
