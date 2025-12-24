#include <stdio.h>
#include <stdlib.h>

struct list {
  int data;
  struct list *next;
};

struct list *createlist(int m);           // 创建链表
void display(struct list *head);          // 显示链表结点信息
void deleteMemory(struct list *head);     // 回收内存
int selectKing(struct list *head, int c); // 选大王

int main() {
  struct list *head;
  int m, c;
  scanf("%d %d", &m, &c);
  head = createlist(m);
  // display(head);
  printf("%d", selectKing(head, c));
  deleteMemory(head);
  return 0;
}

// 创建环形链表
struct list *createlist(int m) {
  struct list *head = NULL, *p = NULL, *s = NULL;
  int i;
  p = (struct list *)malloc(sizeof(struct list *));
  if (p == NULL)
    return NULL;
  head = p;
  p->data = 1;
  for (i = 2; i <= m; i++) {
    s = (struct list *)malloc(sizeof(struct list *));
    s->data = i;
    p->next = s;
    p = s;
  }
  p->next = head;
  return head;
}

// 显示环形链表各结点信息
void display(struct list *first) {
  struct list *p = first;
  printf("%d ", p->data);
  for (p = p->next; p != first; p = p->next) {
    printf("%d ", p->data);
  }
  printf("\n");
}

// 回收环形链表各个结点内存
void deleteMemory(struct list *head) {
  struct list *p = head->next, *pr = NULL;
  while (p != head) {
    pr = p;
    p = p->next;
    free(pr);
  }
  free(head);
}

// 猴子选大王，每次淘汰c的整数倍结点
int selectKing(struct list *head, int c) {
  struct list *p = NULL, *q = NULL;
  int t = 0; // 计数
  p = head;
  do {
    t++;
    if ((t % c) != 0) {
      q = p;
      p = p->next;
    } else {
      t = 0;
      q->next = p->next;
      p = p->next;
    }
  } while (p->next != p);
  return (p->data);
}
