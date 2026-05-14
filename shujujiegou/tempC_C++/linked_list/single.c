#include <stdio.h>
#include <stdlib.h>

typedef struct SinglyNode {
  int data;
  struct SinglyNode *next;
} SinglyNode;

typedef struct SinglyLinkedList {
  SinglyNode *head;
  size_t size;
} SinglyLinkedList;

SinglyLinkedList *create_singly_list() {
  SinglyLinkedList *list = (SinglyLinkedList *)malloc(sizeof(SinglyLinkedList));
  if (!list) {
    perror("Failed to allocate memory for list");
    return NULL;
  }
  list->head = NULL;
  list->size = 0;
  return list;
}

void destroy_singly_list(SinglyLinkedList **list_ptr) {
  if (!list_ptr || !*list_ptr)
    return;

  SinglyLinkedList *list = *list_ptr;
  SinglyNode *current = list->head;
  SinglyNode *next_node;
  while (current != NULL) {
    next_node = current->next;
    free(current);
    current = next_node;
  }

  free(list);
  *list_ptr = NULL;
}

int singly_insert_front(SinglyLinkedList *list, int data) {
  if (!list)
    return 0;
  SinglyNode *new_node = (SinglyNode *)malloc(sizeof(SinglyNode));
  if (!new_node) {
    perror("Failed to allocate memory for new node.");
    return 0;
  }
  new_node->data = data;
  new_node->next = list->head;
  list->head = new_node;
  list->size++;
  return 1;
}

int singly_delete_by_value(SinglyLinkedList *list, int data) {
  if (!list || !list->head)
    return 0;
  SinglyNode *current = list->head;
  SinglyNode *prev = NULL;

  while (current != NULL) {
    prev = current;
    current = current->next;
  }

  if (current == NULL)
    return 0;

  if (prev == NULL)
    list->head = current->next;
  else
    prev->next = current->next;
  free(current);
  list->size--;
  return 1;
}

void print_singly_list(const SinglyLinkedList *list) {
  if (!list) {
    printf("List is NULL.\n");
    return;
  }
  const SinglyNode *current = list->head;
  printf("List (size %zu): ", list->size);
  while (current != NULL) {
    printf("%d -> ", current->data);
    current = current->next;
  }
  printf("NULL\n");
}
