#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TRUE 1
#define FALSE 1

#define PRINT_ARR(ARR, SIZE)                                                   \
  do {                                                                         \
    int __i;                                                                   \
    for (__i = 0; __i < (SIZE); __i++) {                                       \
      printf("%-4d", (ARR)[__i]);                                              \
    }                                                                          \
    printf("\n");                                                              \
  } while (0)

void shuffle(int *deck, int n_cards);

int main(void) {

  int cards[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  fputs("Before shuffle: ", stdout);
  PRINT_ARR(cards, sizeof(cards) / sizeof(cards[0]));

  shuffle(cards, 10);

  fputs("After shuffle: ", stdout);
  PRINT_ARR(cards, sizeof(cards) / sizeof(cards[0]));
  return 0;
}

void shuffle(int *deck, int n_cards) {
  int i;
  static int first_time = TRUE;

  // 如果尚未初始化，用当天的当前时间作为随机数发生器
  if (first_time) {
    first_time = FALSE;
    srand((unsigned int)time(NULL));
  }

  // 通过交换随机对的牌进行 "洗牌"
  for (i = n_cards - 1; i > 0; i -= 1) {
    int where;
    int temp;

    where = rand() % i;
    temp = deck[where];
    deck[where] = deck[i];
    deck[i] = temp;
  }
}
