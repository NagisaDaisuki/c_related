#define _POSIX_C_SOURCE 200112L

#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define A_BIG_NUMBER 10000000 // 改为纯整形常量

typedef struct Student {
  int age;
  char name[30];
  int64_t id; // 改为 64 位整数，杜绝溢出
} Student;

void *working(void *arg) {
  Student *stu = (Student *)arg;

  // 线程安全：使用线程专属的独立随机数种子
  // POSIX 标准
  unsigned int seed = (unsigned int)time(NULL) ^ (unsigned int)pthread_self();

  int i = 1;
  while (i < A_BIG_NUMBER) {
    fprintf(stdout, "[子线程]当前位置：%d \n", i);
    if (i >= 1000000) {
      stu->age = 20;
      snprintf(stu->name, sizeof(stu->name), "Akeboshi Himari");
      stu->id = 1145141919810LL; // LL 标识为长整型

      printf("[子线程]任务完成，数据已写入：%s, ID: %ld\n", stu->name, stu->id);
      break;
    }

    // 保证每次至少乘以 2, 避免乘以 1 原地空转
    i *= (rand_r(&seed) % 6 + 2);
  }

  // 分离线程必须自己负责释放由主线程移交过来的堆内存
  free(stu);
  pthread_exit(NULL); // 分离线程无序带回返回值
}

void print_title(const char *str) {
  fprintf(stdout, "==========================================================");
  fprintf(stdout, "\t\t\t%s\t\t\t", str);
  fprintf(stdout,
          "==========================================================\n");
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stdout, "用法：%s <标题>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  print_title(argv[1]);

  // 1. 创建子线程
  pthread_t tid;
  Student *stu1 = (Student *)calloc(1, sizeof(Student));
  pthread_create(&tid, NULL, working, (void *)stu1);

  // 2. 规范做法：创建后立即分离
  pthread_detach(tid);

  // 3. 主线程任务（使用主线程专属的 rand_r 种子）
  unsigned int main_seed = (unsigned int)time(NULL);
  uint32_t Frac = 1;
  do {
    fprintf(stdout, "[主线程]现在 Frac 状态：%u\n", Frac);
    Frac *= (rand_r(&main_seed) % 6 + 2);
  } while (Frac <= A_BIG_NUMBER);

  // 4. 主线程主动退出本身，但允许已经分离的子线程继续在后台跑完
  pthread_exit(NULL);
  return EXIT_SUCCESS;
}
