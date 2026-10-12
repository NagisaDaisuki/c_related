#include <ctype.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define ws 1e-9
#define PIPELINE_COUNT 50

typedef struct PipeLine {
  double price;
} PipeLine;

typedef struct Product {
  PipeLine num[PIPELINE_COUNT];
  char name[32];
  double sum_price; // pipeline price + 100
} Product;

// 互斥锁保护 Product 的读写；信号量在 producer 涨价完成后唤醒 consumer
pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t g_sem;

void *producer(void *arg) {
  Product *pr = (Product *)arg;

  unsigned int seed = (unsigned int)time(NULL) ^ (unsigned int)pthread_self();

  // 随机挑一条 PipeLine，涨价 2 ~ 5
  int idx = (int)(rand_r(&seed) % PIPELINE_COUNT);
  double inc = 2.0 + (double)(rand_r(&seed) % 4); // 2, 3, 4, 5

  pthread_mutex_lock(&g_mutex);
  double old_price = pr->num[idx].price;
  pr->num[idx].price += inc;
  pr->sum_price += inc;
  fprintf(stdout, "[producer] %s 的 PipeLine[%d] 原价 %.2f 涨价到 %.2f (+%.2f)\n",
          pr->name, idx, old_price, pr->num[idx].price, inc);
  pthread_mutex_unlock(&g_mutex);

  // 通知 consumer：涨价已完成
  sem_post(&g_sem);

  return NULL;
}

void *consumer(void *arg) {
  Product *pr = (Product *)arg;

  // 等待 producer 涨价完成
  sem_wait(&g_sem);

  pthread_mutex_lock(&g_mutex);
  // 独立重新统计一遍总价，验证 sum_price 被正确维护
  double total = 0.0;
  for (int i = 0; i < PIPELINE_COUNT; ++i) {
    total += pr->num[i].price;
  }
  fprintf(stdout, "[consumer] 重新统计 %s 总价: %.2f (sum_price 字段: %.2f)\n",
          pr->name, total, pr->sum_price);
  pthread_mutex_unlock(&g_mutex);

  return NULL;
}

void init_Product(Product *pr, const char *name) {
  unsigned int seed = (unsigned int)time(NULL);
  snprintf(pr->name, sizeof(pr->name), "%s", name);

  for (int i = 0; i < PIPELINE_COUNT; ++i) {
    pr->num[i].price = rand_r(&seed) % 10 + 1;
    pr->sum_price += pr->num[i].price;
  }
}

int main(int argc, char *argv[]) {

  if (argc < 2) {
    fprintf(stdout, "Usage: %s name price.\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // 用 strtod 校验 argv[2] 是否为合法数字（isdigit 只能判单个字符，
  // 且 atof 失败时返回 0.0，无法区分非法输入）
  char *end = NULL;
  double given_price = strtod(argv[2], &end);
  if (end == argv[2] || *end != '\0') {
    fprintf(stdout, "argv[2] price: %s is not a valid argument.\n", argv[2]);
    exit(EXIT_FAILURE);
  }

  // 1. 初始化 Product
  Product pr;
  memset(&pr, 0, sizeof(Product));
  init_Product(&pr, argv[1]);

  // 2. 比较总price 和传入的price的大小
  fprintf(stdout, "%s is much more. (pr: %.2f vs given: %.2f)\n",
          (pr.sum_price > given_price) ? "pr's price" : "user given price",
          pr.sum_price, given_price);

  // 3. 初始化同步原语并创建子线程任务
  if (sem_init(&g_sem, 0, 0) != 0) {
    perror("sem_init");
    exit(EXIT_FAILURE);
  }

  pthread_t tidP, tidC;
  pthread_create(&tidP, NULL, producer, (void *)&pr);
  pthread_create(&tidC, NULL, consumer, (void *)&pr);

  // 4. 回收子线程资源
  pthread_join(tidP, NULL);
  pthread_join(tidC, NULL);

  // 5. 完成子线程对pr结构体的修改，主线程输出涨价后的总价格
  fprintf(stdout, "[main] 涨价后 %s 的总价格: %.2f\n", pr.name, pr.sum_price);

  sem_destroy(&g_sem);
  pthread_mutex_destroy(&g_mutex);

  return EXIT_SUCCESS;
}
