#include <stdio.h>
#include <stdlib.h>

struct list {
  int data;
  struct list *next;
};

struct list *createlist();                           // 创建链表
void display(struct list *h);                        // 显示链表结点信息
void insert(struct list *head, int a, int key);      // 插入节点
struct list *deleteNode(struct list *head, int key); // 删除节点
int sum(struct list *head);
void deleteMemory(struct list *head); // 回收内存
void invert(struct list *head);

int main() {
  struct list *head;
  int a, key;
  head = createlist();
  display(head);
  invert(head);
  display(head->next);
  // printf("%d\n", sum(head));
  deleteMemory(head);
  return 0;
}

struct list *createlist() {
  struct list *p = NULL, *q = NULL, *head = NULL;
  int a;
  // 创建头结点
  scanf("%d", &a);
  if (a != -1) {
    p = (struct list *)malloc(sizeof(struct list));
    p->data = a;
    p->next = NULL;
    head = q = p;
  }
  scanf("%d", &a);

  while (a != -1) // 创建各个数据节点
  {
    p = (struct list *)malloc(sizeof(struct list));
    p->data = a;
    p->next = NULL;
    q->next = p;
    q = p;
    scanf("%d", &a);
  }
  return head;
}

void display(struct list *h) {
  while (h != NULL) {
    printf("%d", h->data);
    h = h->next;
  }
  printf("\n");
}

void deleteMemory(struct list *head) {
  struct list *p = head, *pr = NULL;
  while (p != NULL) {
    pr = p;
    p = p->next;
    free(pr);
  }
}

int sum(struct list *head) {
  struct list *p = head;
  int s = 0;
  while (p != NULL) {
    s += p->data;
    p = p->next;
  }
  return s;
}

void invert(struct list *head) {
  struct list *p, *q;
  p = head->next;
  if (p != NULL) {
    head->next = NULL;
    do {
      q = p->next;
      p->next = head->next;
      head->next = p;
      p = q;
    } while (p != NULL);
  }
}

void insert(struct list *head, int a, int key) {
  struct list *s, *p, *q;
  s = malloc(sizeof(struct list *));
  s->data = key;
  s->next = NULL;
  q = head;
  p = head->next; // p 指向第一个数据结点

  if (p == NULL) { // 没有数据结点，key是第一个数据结点
    // s->next  = p;
    q->next = s;
    return;
  }

  while ((p->data != a) && (p->next != NULL)) {
    q = p;
    p = p->next;
  }
  if (p->data == a) {

    // q = p;
    // p = p->next;
    // q->next = s;
    // s->next = p;
  } else {
    q->next = s;
  }
}
struct list *deleteNode(struct list *head, int key) {
  struct list *p = head, *pr = head;
  if (head == NULL) {
    return head;
  }
  while (key != p->data && p->next != NULL) {
    pr = p;
    p = p->next;
  }
  if (key == p->data) {
    if (p == head) {
      head = p->next;
    } else {
      pr->next = p->next;
    }
  }
}
