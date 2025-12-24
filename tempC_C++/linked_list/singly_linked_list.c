#include <stdio.h>
#include <stdlib.h>

// 节点结构体
typedef struct SinglyNode {
  int data;
  struct SinglyNode *next;
} SinglyNode;

// 链表结构体，包含头指针和大小
typedef struct SinglyLinkedList {
  SinglyNode *head; // 头结点
  size_t size;
} SinglyLinkedList;

/*
 *  @brief 创建并初始化一个新的空链表
 *  @return 指向新链表的指针；如果内存分配失败则返回NULL
 * */
SinglyLinkedList *create_singly_list() {
  SinglyLinkedList *list = (SinglyLinkedList *)malloc(sizeof(SinglyLinkedList));
  if (!list) {
    perror("Failed to allocate memory for list.");
    return NULL;
  }
  list->head = NULL;
  list->size = 0;
  return list;
}

/*
 *  @brief 安全地销毁整个链表，释放所有节点和链表本身的内存
 *  @param list 指向要销毁的链表的指针的指针，操作后会将其设为NULL
 * */
void destroy_singly_list(SinglyLinkedList **list_ptr) {
  if (!list_ptr || !*list_ptr) {
    return; // 安全检查：如果指针无效，则不执行任何操作
  }
  SinglyLinkedList *list = *list_ptr;
  SinglyNode *current = list->head;
  SinglyNode *next_node;

  while (current != NULL) {
    next_node = current->next; // 保存下一个节点的指针
    free(current);             // 释放当前节点
    current = next_node;       // 移动到下一个节点
  }
  free(list);       // 释放链表结构体本身
  *list_ptr = NULL; // 将外部指针设为NULL，防止悬垂指针
}

/*
 *  @brief 在链表头部插入一个新节点
 *  @param list 指向链表的指针
 *  @param data 要插入的数据
 *  @return 成功返回1 失败返回0
 * */
int singly_insert_front(SinglyLinkedList *list, int data) {
  if (!list)
    return 0; // 安全检查
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

/*
 *  @brief 对已经存在的节点修改数据
 *  @param list 指向链表的指针
 *  @param data 要修改的数据
 *  @param changed_data 修改后的数据
 * */
int singly_change_by_value(SinglyLinkedList *list, int data, int changed_data) {
  if (!list || !list->head)
    return 0;
  SinglyNode *current = list->head;

  // 寻找要修改的节点
  while (current != NULL && current->data != data)
    current = current->next;

  // 如果没有找到
  if (current == NULL)
    return 0;

  // 找到并修改数据
  current->data = changed_data;

  return 1;
}

/*
 *  @brief 根据值删除第一个匹配的节点
 *  @param list 指向要删除的指针
 *  @param data 要删除的数据
 *  @return 成功删除返回1 未找到或失败返回 0
 * */
int singly_delete_by_value(SinglyLinkedList *list, int data) {
  if (!list || !list->head)
    return 0; // 安全检查： 链表为空或无效

  SinglyNode *current = list->head;
  SinglyNode *prev = NULL;

  // 寻找要删除的节点
  while (current != NULL && current->data != data) {
    prev = current;
    current = current->next;
  }

  // 如果未找到
  if (current == NULL)
    return 0;

  // 如果删除的是头节点
  if (prev == NULL)
    list->head = current->next;
  else
    prev->next = current->next;

  free(current); // 释放节点
  list->size--;
  return 1;
}

/*
 *  @brief 打印链表内容
 *  @param list 指向链表的指针
 * */
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

int main() {
  printf("--- C Singly Linked List Demo ---\n");
  SinglyLinkedList *my_list = create_singly_list();
  if (!my_list)
    return 1; // 创建失败

  print_singly_list(my_list);

  printf("\nInserting 10,20,30 at the front...\n");
  singly_insert_front(my_list, 30);
  singly_insert_front(my_list, 20);
  singly_insert_front(my_list, 10);
  print_singly_list(my_list);

  printf("\nDeleting node with value 20...\n");
  singly_delete_by_value(my_list, 20);
  print_singly_list(my_list);

  printf("\nDeleting head node with value 10...\n");
  singly_delete_by_value(my_list, 10);
  print_singly_list(my_list);

  printf("\nDeleting non-existent node with value 99...\n");
  singly_delete_by_value(my_list, 99);
  print_singly_list(my_list);

  printf("\nInserting 10,20,30 at the front...\n");
  singly_insert_front(my_list, 30);
  singly_insert_front(my_list, 20);
  singly_insert_front(my_list, 10);
  print_singly_list(my_list);

  printf("\n修改节点值为20的值为50\n");
  singly_change_by_value(my_list, 20, 50);
  print_singly_list(my_list);

  printf("\nDestroying list...\n");
  destroy_singly_list(&my_list);

  // my_list 现在是 NULL，下面的打印会安全地处理
  print_singly_list(my_list);
  printf("Demo finished.\n");

  return EXIT_SUCCESS;
}
