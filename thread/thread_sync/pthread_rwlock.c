#define _DEFAULT_SOURCE

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// 读写锁是互斥锁的升级版,
// 在做读操作的时候可以提高程序的执行效率，如果所有的线程都是做读操作,
// 那么读是并行的，但是使用互斥锁，读操作也是串行的。
// 如果说程序中所有的线程都对共享资源做写操作，使用读写锁没有优势，和互斥锁是一样的，如果说程序中所有的线程都对共享资源有写也有读操作，并且对共享资源读的操作越多，读写锁更有优势。

// 全局变量
int number = 0;
#define MAX_WRITE 100

// 定义读写锁
pthread_rwlock_t rwlock;

// 写的线程的处理函数
void *writeNum(void *arg);
void *writeNumSafe(void *arg);

// 读的线程处理函数
void *readNum(void *arg);
void *readNumSafe(void *arg);

int main() {
  // 初始化读写锁
  pthread_rwlock_init(&rwlock, NULL);

  // 3个写线程，5个读线程
  pthread_t wtid[3];
  pthread_t rtid[5];

  for (int i = 0; i < 3; ++i) {
    // pthread_create(&wtid[i], NULL, writeNum, NULL);
    pthread_create(&wtid[i], NULL, writeNumSafe, NULL);
    // 使用非 safe的函数永远卡死在第一个子写线程
    // while循环没有被释放
  }

  for (int i = 0; i < 5; ++i) {
    // pthread_create(&rtid[i], NULL, readNum, NULL);
    pthread_create(&rtid[i], NULL, readNumSafe, NULL);
  }

  // 释放资源
  for (int i = 0; i < 3; ++i) {
    pthread_join(wtid[i], NULL);
  }

  for (int i = 0; i < 5; ++i) {
    pthread_join(rtid[i], NULL);
  }

  // 销毁读写锁
  pthread_rwlock_destroy(&rwlock);

  return EXIT_SUCCESS;
}

// 写的线程的处理函数
void *writeNum(void *arg) {
  while (1) {
    pthread_rwlock_wrlock(&rwlock);
    int cur = number;
    cur++;
    number = cur;
    printf("++写操作完成，number: %d, tid = %ld\n", number, pthread_self());
    pthread_rwlock_unlock(&rwlock);
    // 添加sleep目的是要看到多个线程交替工作
    usleep(rand() % 100);
  }

  return NULL;
}
void *writeNumSafe(void *arg) {
  (void)arg;
  unsigned int seed = (unsigned int)pthread_self();

  while (1) {
    pthread_rwlock_wrlock(&rwlock);
    if (number > MAX_WRITE) {
      pthread_rwlock_unlock(&rwlock);
      break; // 达到目标，退出循环
    }
    number++;
    printf("++[写线程 %ld] 写入完成，当前 number: %d\n", pthread_self(),
           number);
    pthread_rwlock_unlock(&rwlock);

    usleep(rand_r(&seed) % 5000);
  }

  return NULL;
}

// 读的线程处理函数
void *readNum(void *arg) {
  while (1) {
    pthread_rwlock_rdlock(&rwlock);
    printf("--全局变量number = %d, tid = %ld\n", number, pthread_self());
    pthread_rwlock_unlock(&rwlock);
    usleep(rand() % 100);
  }

  return NULL;
}
void *readNumSafe(void *arg) {
  (void)arg;
  unsigned int seed = (unsigned int)pthread_self();

  while (1) {
    pthread_rwlock_rdlock(&rwlock);
    printf("--[读线程 %ld] 正在读取，当前 number: %d\n", pthread_self(),
           number);
    int current = number;
    pthread_rwlock_unlock(&rwlock);

    if (current >= MAX_WRITE) {
      break;
    }
    usleep(rand_r(&seed) % 5000);
  }

  return NULL;
}
