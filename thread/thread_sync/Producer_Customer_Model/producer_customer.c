#define _DEFAULT_SOURCE
// #define _POSIX_C_SOURCE 200112L

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define QUEUE_CAPACITY 5 // 缓冲区最大容量
#define ITEM_COUNT 20    // 总共生产消费的数据量

// 环形缓冲队列结构体
typedef struct {
  int buffer[QUEUE_CAPACITY];
  int head;  // 消费指针
  int tail;  // 生产指针
  int count; // 当前已有元素个数

  pthread_mutex_t mutex;    // 保持队列状态的互斥锁
  pthread_cond_t not_full;  // 队列不满条件(供生产者等待)
  pthread_cond_t not_empty; // 队列非空条件(供消费者等待)
} BoundedQueue;

BoundedQueue g_queue;

// 队列入队（生产者调用）
void queue_push(BoundedQueue *q, int val);

// 队列出队（消费者调用）
int queue_pop(BoundedQueue *q);

// 生产者线程函数
void *producer(void *arg);

// 消费者线程函数
void *consumer(void *arg);

int main() {
  // 1. 初始化队列及其同步原语
  g_queue.head = 0;
  g_queue.tail = 0;
  g_queue.count = 0;
  pthread_mutex_init(&g_queue.mutex, NULL);
  pthread_cond_init(&g_queue.not_full, NULL);
  pthread_cond_init(&g_queue.not_empty, NULL);

  pthread_t prod_tid, cons_tid;

  // 2. 创建一个生产者和一个消费者
  pthread_create(&prod_tid, NULL, producer, NULL);
  pthread_create(&cons_tid, NULL, consumer, NULL);

  // 3. 等待生产消费完成
  pthread_join(prod_tid, NULL);
  pthread_join(cons_tid, NULL);

  // 4. 清理资源
  pthread_mutex_destroy(&g_queue.mutex);
  pthread_cond_destroy(&g_queue.not_empty);
  pthread_cond_destroy(&g_queue.not_full);

  printf("\n所有数据生产与消费全部完成，程序安全退出。\n");

  return EXIT_SUCCESS;
}

// 队列入队（生产者调用）
void queue_push(BoundedQueue *q, int val) {
  pthread_mutex_lock(&q->mutex);

  // 1. 缓冲区满了，生产者必须等待
  while (q->count == QUEUE_CAPACITY) {
    pthread_cond_wait(&q->not_full, &q->mutex);
  }
  // 2. 写入数据
  q->buffer[q->tail] = val;
  q->tail = (q->tail + 1) % QUEUE_CAPACITY;
  q->count++;
  printf("[生产者 %ld] 生产数据：%02d (当前库存：%d/%d)\n",
         (long)pthread_self(), val, q->count, QUEUE_CAPACITY);

  // 3. 通知消费者可以取货了
  pthread_cond_signal(&q->not_empty);

  pthread_mutex_unlock(&q->mutex);
}

// 队列出队（消费者调用）
int queue_pop(BoundedQueue *q) {
  pthread_mutex_lock(&q->mutex);

  // 1. 缓冲区空了，消费者必须等待
  while (q->count == 0) {
    pthread_cond_wait(&q->not_empty, &q->mutex);
  }

  // 2. 取出数据
  int val = q->buffer[q->head];
  q->head = (q->head + 1) % QUEUE_CAPACITY;
  q->count--;
  printf("[消费者 %ld] 消费数据：%02d (剩余库存：%d/%d)\n",
         (long)pthread_self(), val, q->count, QUEUE_CAPACITY);

  // 3. 通知生产者有空位了
  pthread_cond_signal(&q->not_full);

  pthread_mutex_unlock(&q->mutex);

  return val;
}

// 生产者线程函数
void *producer(void *arg) {
  (void)arg;
  for (int i = 0; i <= ITEM_COUNT; ++i) {
    queue_push(&g_queue, i);
    usleep(30000); // 30ms
  }
  return NULL;
}

// 消费者线程函数
void *consumer(void *arg) {
  (void)arg;
  for (int i = 0; i <= ITEM_COUNT; ++i) {
    int val = queue_pop(&g_queue);
    (void)val;
    usleep(80000); // 80ms, 触发队列被填满的边界
  }

  return NULL;
}