#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define A_BIG_NUMBER 1e7

typedef struct Student {
  int age;
  char name[30];
  long id;
} Student;

// 子线程的处理代码
#define IS_WORKING 0
void *working(void *arg) {
  // 获取主线程传入参数
  Student *stu = (Student *)arg;
  int i;
  for (i = 1; i < A_BIG_NUMBER; i *= rand() % 7 + 1) {
    fprintf(stdout, "Current Location: \t%d\n", i);
    if (i >= 1e6) {
      stu->age = 20;
      // stu->name = "Akeboshi Himari"; 因为
      // char数组是一个左值，只可以在初始化的 时候赋值 其他时候使用 strcpy或
      // snprintf 赋值
      strcpy(stu->name, "Akeboshi Himari");
      stu->id = 1145141919810;

      pthread_exit(stu);
    }
  }
  return NULL;
}
#if IS_WORKING == 0
#elif IS_WORKING == 1
#elif IS_WORKING == 2
#endif

void print_title(const char *str) {
  fprintf(stdout, "==========================================================");
  fprintf(stdout, "\t\t\t%s\t\t\t", str);
  fprintf(stdout, "==========================================================");
  puts("");
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "用法： %s (一个需要展示在程序最顶端的文字！)\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  print_title(argv[1]);
  // 随机数种子
  srand((unsigned int)time(NULL));

  // 1. 创建子线程
  pthread_t tid;
  Student *stu1 = (Student *)calloc(1, sizeof(Student));
  pthread_create(&tid, NULL, working, (void *)stu1);

  // 2. 不会在子线程执行的操作
  uint32_t Frac = 1;
  do {
    fprintf(stdout, "现在Frac的状态码: \t%u\n", Frac);
    Frac *= rand() % 7 + 1;
  } while (Frac <= A_BIG_NUMBER);

  // 3. 设置子线程和主线程分离,
  // 这里子线程的返回值拿不到也不会在这里堵塞等到子线程执行完 继续主线程的任务
  pthread_detach(tid);

  // 执行一些主线程的任务...

  // 4. 让主线程自己退出即可
  pthread_exit(NULL);

  // 5. 释放分配的内存
  free(stu1);
  return EXIT_SUCCESS;
}
