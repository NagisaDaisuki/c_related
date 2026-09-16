#define _DEFAULT_SOURCE // 告诉 glibc 开启默认的 BSD/System V/XSI 扩展支持

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// 所谓的同步并不是多个线程同时对内存进行访问，而是按照先后顺序依次进行的。

#define MAX 50

// 全局变量
int number;

// 线程处理函数
void *funcA_num(void *arg) {
  for (int i = 0; i < MAX; ++i) {
    int cur = number;
    cur++;
    usleep(10);
    number = cur;
    printf("Thread A, id = %lu, number = %d\n", pthread_self(), number);
  }

  return NULL;
}

void *funcB_num(void *arg) {
  for (int i = 0; i < MAX; ++i) {
    int cur = number;
    cur++;
    number = cur;
    printf("Thread B, id = %lu, number = %d\n", pthread_self(), number);
    usleep(5);
  }
  return NULL;
}
int main(int argc, char *argv[]) {
  pthread_t p1, p2;

  // 创建两个子线程
  pthread_create(&p1, NULL, funcA_num, NULL);
  pthread_create(&p2, NULL, funcB_num, NULL);

  // 阻塞，资源回收
  pthread_join(p1, NULL);
  pthread_join(p2, NULL);

  return EXIT_SUCCESS;
}