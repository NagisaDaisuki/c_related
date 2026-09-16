#define _DEFAULT_SOURCE

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX 100
// 全局变量
int number;

// 创建一把互斥锁
// 全局变量，多个线程共享
pthread_mutex_t mutex;

// 线程处理函数
void *funcA_num(void *arg) {
  for (int i = 0; i < MAX; ++i) {
    // 如果线程 A 加锁成功，不阻塞
    // 如果 B 加锁成功, 线程 A 阻塞
    pthread_mutex_lock(&mutex);
    int cur = number;
    cur++;
    usleep(10);
    number = cur;
    pthread_mutex_unlock(&mutex);
    printf("Thread A, id = %lu, number = %d\n", pthread_self(), number);
  }

  return NULL;
}

void *funcB_num(void *num) {
  for (int i = 0; i < MAX; ++i) {
    // a 加锁成功，b线程 访问这把锁的时候 是 锁定的
    // 线程 B 先阻塞， a 线程解锁之后阻塞解除
    // 线程 B 加锁 成功了
    pthread_mutex_lock(&mutex);
    int cur = number;
    cur++;
    number = cur;
    pthread_mutex_unlock(&mutex);
    printf("Thread B, id = %lu, number = %d\n", pthread_self(), number);
    usleep(5);
  }

  return NULL;
}

int main(int argc, const char *argv[]) {
  pthread_t p1, p2;

  // 初始化互斥锁
  pthread_mutex_init(&mutex, NULL);

  // 创建两个子线程
  pthread_create(&p1, NULL, funcA_num, NULL);
  pthread_create(&p2, NULL, funcB_num, NULL);

  // 阻塞，资源回收
  pthread_join(p1, NULL);
  pthread_join(p2, NULL);

  // 销毁互斥锁
  // 线程销毁之后，再去释放互斥锁
  pthread_mutex_destroy(&mutex);

  return EXIT_SUCCESS;
}
