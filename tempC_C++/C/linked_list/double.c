#include <stdio.h>
#include <stdlib.h>

typedef struct DoublyNode {
  struct DoublyNode *prev;
  struct DoublyNode *next;
  int data;
} DoublyNode;

typedef struct DoublyLinkedList {
  DoublyNode *head;
  DoublyNode *tail;
  size_t size;
} DoublyLinkedList;

DoublyLinkedList *create_doubly_list() {
  DoublyLinkedList *list = (DoublyLinkedList *)malloc(sizeof(DoublyLinkedList));
  if (!list) {
    perror("Failed to allocate memory for list.");
    return NULL;
  }
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  return list;
}

void delete_doubly_list(DoublyLinkedList **list_ptr) {
  if (!list_ptr || !*list_ptr)
    return;
  DoublyLinkedList *list = *list_ptr;
  DoublyNode *current = list->head;
  DoublyNode *next_node;

  while (current != NULL) {
    next_node = current;
    free(current);
    current = next_node;
  }

  free(list);
  *list_ptr = NULL;
}

int doubly_insert_back(DoublyLinkedList *list, int data) {
  if (!list)
    return 0;
  DoublyNode *new_node = (DoublyNode *)malloc(sizeof(DoublyNode));
  if (!new_node) {
    perror("failed to allocate memory for node.");
    return 0;
  }
  new_node->data = data;
  new_node->next = NULL;
  if (list->tail == NULL) // 链表为空
  {
    new_node->prev = NULL;
    list->head = new_node;
    list->tail = new_node;
  } else { // 链表不为空
    new_node->prev = list->tail;
    list->tail->next = new_node;
    list->tail = new_node;
  }
  list->size++;
  return 1;
}

int doubly_delete_by_value(DoublyLinkedList *list, int data) {
  if (!list || !list->head)
    return 0;
  DoublyNode *current = list->head;

  while (current != NULL && current->data != data) {
    current = current->next;
  }

  if (current == NULL)
    return 0;

  if (current->prev != NULL)
    current->prev->next = current->next;
  else
    list->head = current->next;

  if (current->next != NULL)
    current->next->prev = current->prev;
  else
    list->tail = current->prev;

  free(current);
  list->size--;
  return 1;
}

void print_doubly_list(DoublyLinkedList *list, int data) {
  if (!list) {
    printf("List is NULL.\n");
    return;
  }
  const DoublyNode *current = list->head;
  printf("List (size %zu): HEAD -> ", list->size);
  while (current != NULL) {
    printf("%d <-> ", current->data);
    current = current->next;
  }
  printf("NULL\n");
}
