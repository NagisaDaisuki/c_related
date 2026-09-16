#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// 定义结构
struct Person {
  int id;
  char name[36];
  int age;
};

// 子线程的处理代码
#define IF_WORKING 2
#if IF_WORKING == 0
void *working(void *arg) {
  printf("我是子线程，线程ID: %ld\n", pthread_self());
  for (int i = 0; i < 9; ++i) {
    printf("child == i: = %d\n", i);
    if (i == 6) {
      // struct Person p; 这里局部变量子线程 working 函数
      // 内部的栈局部变量
      // 当 pthread_exit(&p)调用的那一瞬间，子线程立刻宣告死亡
      // 主线程通过pthread_join接收到的ptr实际上是一个指向已经
      // 死亡对象的dangling pointer（悬垂指针/野指针）
      struct Person *p = (struct Person *)malloc(sizeof(struct Person));
      p->age = 12;
      strcpy(p->name, "tom");
      p->id = 100;
      // 该函数的参数将这个地址传递給了主线程的pthread_join()
      pthread_exit(p);
    }
  }
  return NULL; // 代码执行不到这个位置就退出了
}
#elif IF_WORKING == 1
void *working(void *arg) {
  struct Person *p = (struct Person *)arg;
  printf("我是子线程，线程ID: %ld\n", pthread_self());
  for (int i = 0; i < 9; ++i) {
    printf("child == i: = %d\n", i);
    if (i == 6) {
      p->age = 12;
      strcpy(p->name, "tom");
      p->id = 100;
      // 该函数的参数将这个地址传递給了主线程的pthread_join()
      pthread_exit(p);
    }
  }
  return NULL; // 代码执行不到这个位置就退出了
}
#elif IF_WORKING == 2
void *working(void *arg) {
  struct Person *p = (struct Person *)arg;
  printf("我是子线程，线程ID: %ld\n", pthread_self());
  for (int i = 0; i < 9; ++i) {
    printf("child == i: = %d\n", i);
    if (i == 6) {
      p->age = 12;
      strcpy(p->name, "tom");
      p->id = 100;
      // 该函数的参数将这个地址传递給了主线程的pthread_join()
      pthread_exit(p);
    }
  }
  return NULL; // 代码执行不到这个位置就退出了
}
#endif

int main() {
  // 1 . 创建一个子线程
  pthread_t tid;
  // 2. 将结构体作为传入参数传入子线程
  // struct Person *p = NULL;
  struct Person *p = (struct Person *)malloc(sizeof(struct Person));
  pthread_create(&tid, NULL, working, (void *)p);

  printf("子线程创建成功，线程ID: %ld\n", tid);

  // 2. 子线程不会执行下边的代码，主线程执行
  for (int i = 0; i < 3; ++i) {
    printf("i = %d\n", i);
  }

  // 阻塞等待子线程退出
  void *ptr = NULL;
  // ptr是一个传出参数，在函数内部让这个指针指向一块有效内存
  // 这个内存地址就是 pthread_exit()参数指向的内存
  pthread_join(tid, &ptr);
  // 打印信息
  struct Person *pp = (struct Person *)ptr;
  printf("子线程返回数据： name: %s, age: %d, id: %d\n", pp->name, pp->age,
         pp->id);
  printf("子线程资源被成功回收...\n");
  return 0;
}
