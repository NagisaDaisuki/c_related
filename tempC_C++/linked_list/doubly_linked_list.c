#include <stdio.h>
#include <stdlib.h>

// --- C语言：安全的双链表实现 ---

// 节点结构体
typedef struct DoublyNode {
  int data;
  struct DoublyNode *next;
  struct DoublyNode *prev;
} DoublyNode;

// 链表结构体，包含头、尾指针和大小
typedef struct DoublyLinkedList {
  DoublyNode *head;
  DoublyNode *tail;
  size_t size;
} DoublyLinkedList;

/**
 * @brief 创建并初始化一个新的空链表
 * @return 指向新链表的指针；如果内存分配失败则返回 NULL
 */
DoublyLinkedList *create_doubly_list() {
  DoublyLinkedList *list = (DoublyLinkedList *)malloc(sizeof(DoublyLinkedList));
  if (!list) {
    perror("Failed to allocate memory for list");
    return NULL;
  }
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  return list;
}

/**
 * @brief 安全地销毁整个链表，释放所有节点和链表本身的内存
 * @param list_ptr 指向要销毁的链表的指针的指针，操作后会将其设为 NULL
 */
void destroy_doubly_list(DoublyLinkedList **list_ptr) {
  if (!list_ptr || !*list_ptr) {
    return; // 安全检查
  }
  DoublyLinkedList *list = *list_ptr;
  DoublyNode *current = list->head;
  DoublyNode *next_node;
  while (current != NULL) {
    next_node = current->next;
    free(current);
    current = next_node;
  }
  free(list);
  *list_ptr = NULL; // 防止悬垂指针
}

/**
 * @brief 在链表尾部插入一个新节点
 * @param list 指向链表的指针
 * @param data 要插入的数据
 * @return 成功返回 1，失败返回 0
 */
int doubly_insert_back(DoublyLinkedList *list, int data) {
  if (!list) {
    return 0; // 安全检查
  }
  DoublyNode *new_node = (DoublyNode *)malloc(sizeof(DoublyNode));
  if (!new_node) {
    perror("Failed to allocate memory for new node");
    return 0;
  }
  new_node->data = data;
  new_node->next = NULL;

  if (list->tail == NULL) { // 链表为空
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

/**
 * @brief 根据值删除第一个匹配的节点
 * @param list 指向链表的指针
 * @param data 要删除的数据
 * @return 成功删除返回 1，未找到或失败返回 0
 */
int doubly_delete_by_value(DoublyLinkedList *list, int data) {
  if (!list || !list->head) {
    return 0; // 安全检查
  }

  DoublyNode *current = list->head;

  // 寻找要删除的节点
  while (current != NULL && current->data != data) {
    current = current->next;
  }

  // 如果未找到
  if (current == NULL) {
    return 0;
  }

  // 更新前一个节点的 next 指针
  if (current->prev != NULL) {
    current->prev->next = current->next;
  } else { // 删除的是头节点
    list->head = current->next;
  }

  // 更新后一个节点的 prev 指针
  if (current->next != NULL) {
    current->next->prev = current->prev;
  } else { // 删除的是尾节点
    list->tail = current->prev;
  }

  free(current); // 释放节点
  list->size--;
  return 1;
}

/**
 * @brief 打印链表内容（从头到尾）
 * @param list 指向链表的指针
 */
void print_doubly_list(const DoublyLinkedList *list) {
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

// --- 示例 main 函数 ---
// 您可以取消下面的注释来编译和运行一个示例

int main() {
  printf("--- C Doubly Linked List Demo ---\n");
  DoublyLinkedList *my_list = create_doubly_list();
  if (!my_list) {
    return 1;
  }

  print_doubly_list(my_list);

  printf("\nInserting 10, 20, 30 at the back...\n");
  doubly_insert_back(my_list, 10);
  doubly_insert_back(my_list, 20);
  doubly_insert_back(my_list, 30);
  print_doubly_list(my_list);

  printf("\nDeleting node with value 20...\n");
  doubly_delete_by_value(my_list, 20);
  print_doubly_list(my_list);

  printf("\nDeleting head node with value 10...\n");
  doubly_delete_by_value(my_list, 10);
  print_doubly_list(my_list);

  printf("\nDeleting tail node with value 30...\n");
  doubly_delete_by_value(my_list, 30);
  print_doubly_list(my_list);

  printf("\nDestroying list...\n");
  destroy_doubly_list(&my_list);

  print_doubly_list(my_list);
  printf("Demo finished.\n");

  return 0;
}
