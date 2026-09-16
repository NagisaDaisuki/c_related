#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// 链表的节点
struct Node {
  int number;
  struct Node *next;
};

// 生产者线程信号量
sem_t psem;

// 消费者线程信号量
sem_t csem;

// 互斥锁变量
pthread_mutex_t mutex;
// 指向头结点的指针
struct Node *head = NULL;

// 生产者的回调函数
void *producer(void *arg) {
  (void)arg;
  while (1) {
    // 1. 耗时的内存分配放在外面
    struct Node *pnew = (struct Node *)malloc(sizeof(struct Node));
    pnew->number = rand() % 1000;

    // 2. 信号量：申请队列配额（满五个就阻塞）
    sem_wait(&psem);

    // 3. 互斥锁：保护链表指针修改
    pthread_mutex_lock(&mutex);
    pnew->next = head;
    head = pnew;
    pthread_mutex_unlock(&mutex);

    // 4. 信号量：通知消费者有新货
    sem_post(&csem);

    sleep(rand() % 3);
  }
  return NULL;
}

// 消费者的回调函数
void *consumer(void *arg) {
  (void)arg;
  while (1) {
    // 1. 信号量：等待有可用数据
    sem_wait(&csem);

    // 2. 互斥锁：安全摘除节点
    pthread_mutex_lock(&mutex);
    struct Node *pnode = head;
    head = pnode->next;
    pthread_mutex_unlock(&mutex);

    // 3. 信号量：归还配额給生产者
    sem_post(&psem);

    // 4. 耗时的 I/O 和内存释放在锁外
    printf("--consumer: number: %d, tid = %ld\n", pnode->number,
           pthread_self());
    free(pnode);

    sleep(rand() % 3);
  }
  return NULL;
}

int main() {
  // 初始化信号量
  // 生产者和消费者拥有的信号灯的总和为1
  sem_init(&psem, 0, 1); // 生产者线程一共有1 个信号灯
  sem_init(&csem, 0, 0); // 消费者线程一共有0 个信号灯

  // 创建五个生产者，五个消费者
  pthread_t ptid[5];
  pthread_t ctid[5];

  for (int i = 0; i < 5; ++i) {
    pthread_create(&ptid[i], NULL, producer, NULL);
  }
  for (int i = 0; i < 5; ++i) {
    pthread_create(&ctid[i], NULL, consumer, NULL);
  }

  // 释放资源
  for (int i = 0; i < 5; ++i) {
    pthread_join(ptid[i], NULL);
  }
  for (int i = 0; i < 5; ++i) {
    pthread_join(ctid[i], NULL);
  }

  sem_destroy(&psem);
  sem_destroy(&csem);

  return 0;
}
