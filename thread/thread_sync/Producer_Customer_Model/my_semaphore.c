#define _DEFAULT_SOURCE

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SEM_NUM 5
#define PRODUCER_NUM 20
#define CONSUMER_NUM 10

// 链表结构
typedef struct Node {
  int e_id;
  // char e_name[32];
  struct Node *next;
} Node;

// 互斥锁
pthread_mutex_t mutex;
// 信号量
sem_t psem, csem;
// 链表
Node *head = NULL;
// 生产者函数
void *producer(void *arg);
// 消费者函数
void *consumer(void *arg);

// 主线程函数
int main(void) {
  // 1. 信号量和锁初始化
  sem_init(&psem, 0, SEM_NUM);
  sem_init(&csem, 0, 0);
  pthread_mutex_init(&mutex, NULL);

  // 2. 分配 5 个生产者线程， 5 个消费者线程
  pthread_t ptid[5], ctid[5];

  for (int i = 0; i < 5; ++i) {
    pthread_create(&ptid[i], NULL, producer, NULL);
  }
  for (int i = 0; i < 5; ++i) {
    pthread_create(&ctid[i], NULL, consumer, NULL);
  }

  // 3. 回收子线程的所有分配的资源
  for (int i = 0; i < 5; ++i) {
    pthread_join(ptid[i], NULL);
  }
  for (int i = 0; i < 5; ++i) {
    pthread_join(ctid[i], NULL);
  }

  // 4. 回收信号量
  sem_destroy(&psem);
  sem_destroy(&csem);

  return EXIT_SUCCESS;
}

// 生产者函数
void *producer(void *arg) {
  (void)arg;
  unsigned int seed = (unsigned int)pthread_self();

  while (1) {
    // 在临界区外执行分配内存的操作
    Node *p_node = (Node *)malloc(sizeof(Node));

    sem_wait(&psem);
    pthread_mutex_lock(&mutex);
    p_node->e_id = (rand_r(&seed) % 10000 + 1);
    p_node->next = head;
    head = p_node;
    pthread_mutex_unlock(&mutex);

    // 通知消费者队列已有可以消费的产品
    sem_post(&csem);
    sleep(rand_r(&seed) % 3 + 1);
  }
  return NULL;
}
// 消费者函数
void *consumer(void *arg) {
  (void)arg;
  unsigned int seed = (unsigned int)pthread_self();
  while (1) {
    sem_wait(&csem);
    pthread_mutex_lock(&mutex);
    Node *c_node = head;
    int e_id = c_node->e_id;
    head = c_node->next;
    pthread_mutex_unlock(&mutex);

    // 告诉消费者有多余的空位了(归还配额給消费者)
    sem_post(&psem);

    // 在临界区外执行释放分配内存操作 和耗时IO操作
    fprintf(stdout, "线程 %ld 拿到的产品id：%d...\n", (long)pthread_self(),
            e_id);

    free(c_node);
    sleep(rand_r(&seed) % 3 + 1);
  }
  return NULL;
}
