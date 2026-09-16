#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// 每一个线程都有一个唯一的线程ID，ID类型为pthread_t，这个ID是一个无符号长整形数，如果想要得到当前线程的线程ID，可以调用如下函数：
// pthread_t pthread_self(void); 返回当前线程的线程ID

// 在一个进程中调用线程创建函数，就可得到一个子线程，
// 和进程不同，需要给每一个创建出的线程指定一个处理函数，否则这个线程无法工作。
/*
 *  int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
 *                void *(*start_routine) (void*), void *arg);
 * 参数:
    thread: 传出参数，是无符号长整形数，线程创建成功,
 会将线程ID写入到这个指针指向的内存中
    attr: 线程的属性,
 一般情况下使用默认属性即可, 写NULL
    start_routine:
 函数指针，创建出的子线程的处理动作，也就是该函数在子线程中执行。
    arg:
 作为实参传递到 start_routine 指针指向的函数内部
    返回值：线程创建成功返回0，创建失败返回对应的错误号
 * */

// 子线程的处理代码
void *working(void *arg) {
  printf("我是子线程，线程ID: %ld\n", pthread_self());
  for (int i = 0; i < 9; ++i) {
    printf("child == i: = %d\n", i);
  }
  return NULL;
}

int main() {
  // 1. 创建一个子线程
  pthread_t tid;
  pthread_create(&tid, NULL, working, NULL);

  printf("子线程创建成功！线程ID: %ld\n", tid);
  // 2. 子线程不会执行下边的代码，主线程执行
  printf("我是主线程，线程ID: %ld\n", pthread_self());
  for (int i = 0; i < 3; ++i) {
    printf("i = %d\n", i);
  }

  // sleep：子线程是否能在 1 秒内跑完
  // sleep(1); // unistd.h

  // 替换 sleep(1): 阻塞等待子线程退出并回收资源
  pthread_join(tid, NULL);

  return EXIT_SUCCESS;
}
