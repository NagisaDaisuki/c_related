#define _DEFAULT_SOURCE

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define COUNTER_CAPACITY 4 // 出餐台最多放 4 盘菜
#define TOTAL_ORDERS 12    // 今日总单量

typedef struct {
  int order_id;
  char name[32];
  int chef_id;
} Dish;

typedef struct {
  Dish table[COUNTER_CAPACITY]; // 环形缓冲区
  int head;                     // 服务员取菜位置
  int tail;                     // 厨师放菜位置
  int count;                    // 台面上当前菜品数

  int assigned_count; // 已分配领单总数
  int served_count;   // 已送达顾客总数

  pthread_mutex_t lock; // 保护环形队列数据与计数器的互斥锁
  sem_t sem_empty;      // 空闲槽位信号量（初始为 COUNTER_CAPACITY）
  sem_t sem_full;       // 存货菜品信号量（初始为 0）
} ServingCounter;

ServingCounter g_counter;

const char *MENU[] = {"北京烤鸭", "麻婆豆腐", "宫保鸡丁", "水煮牛肉",
                      "清蒸鲈鱼"};

// ================= 厨师线程（生产者） =================
void *chef_routine(void *arg) {
  int chef_id = *(int *)arg;
  unsigned int seed = (unsigned int)pthread_self();

  while (1) {
    // 1. 领单配额检查（互斥锁保护）
    pthread_mutex_lock(&g_counter.lock);
    if (g_counter.assigned_count >= TOTAL_ORDERS) {
      pthread_mutex_unlock(&g_counter.lock);
      break; // 指标完成，不再接新单
    }
    int order_id = ++g_counter.assigned_count;
    pthread_mutex_unlock(&g_counter.lock);

    // 2. 模拟烹饪耗时（临界区外执行）
    usleep((1000 + rand_r(&seed) % 1000) * 1000); // 1.0 ~ 2.0 秒
    const char *dish_name = MENU[rand_r(&seed) % 5];

    // 3. P操作：申请出餐台空位（如果台满，在此挂起等待）
    sem_wait(&g_counter.sem_empty);

    // 4. 加互斥锁：将菜品安全摆放入环形队列
    pthread_mutex_lock(&g_counter.lock);
    Dish *d = &g_counter.table[g_counter.tail];
    d->order_id = order_id;
    d->chef_id = chef_id;
    snprintf(d->name, sizeof(d->name), "%s", dish_name);

    g_counter.tail = (g_counter.tail + 1) % COUNTER_CAPACITY;
    g_counter.count++;

    printf("  👉 [👨‍🍳 厨师 %d] 上菜: #%02d <%s> (出餐台存量: "
           "%d/%d)\n",
           chef_id, order_id, dish_name, g_counter.count, COUNTER_CAPACITY);
    pthread_mutex_unlock(&g_counter.lock);

    // 5. V操作：菜品存货 +1（唤醒等待中的服务员）
    sem_post(&g_counter.sem_full);
  }

  printf("🚪 [👨‍🍳 厨师 %d] 今日菜单制作完毕，收工！\n",
         chef_id);
  return NULL;
}

// ================= 服务员线程（消费者） =================
void *waiter_routine(void *arg) {
  int waiter_id = *(int *)arg;
  unsigned int seed = (unsigned int)pthread_self();

  while (1) {
    // 1. P操作：等待出餐台有现成菜品（如果台空，在此挂起等待）
    sem_wait(&g_counter.sem_full);

    // 2. 加互斥锁：核验指标并取出菜品
    pthread_mutex_lock(&g_counter.lock);
    if (g_counter.served_count >= TOTAL_ORDERS) {
      // 收到退出接力信号：释放锁并把信号量继续传给下一个同事，确保大家都能下班
      sem_post(&g_counter.sem_full);
      pthread_mutex_unlock(&g_counter.lock);
      break;
    }

    Dish d = g_counter.table[g_counter.head];
    g_counter.head = (g_counter.head + 1) % COUNTER_CAPACITY;
    g_counter.count--;
    g_counter.served_count++;

    printf("  ⚡ [🤵 服务员 %d] 端走: #%02d <%s> (厨师 %d 作, 剩余: %d/%d)\n",
           waiter_id, d.order_id, d.name, d.chef_id, g_counter.count,
           COUNTER_CAPACITY);

    int is_all_done = (g_counter.served_count >= TOTAL_ORDERS);
    pthread_mutex_unlock(&g_counter.lock);

    // 3. V操作：腾出出餐台空位（唤醒等待空位的厨师）
    sem_post(&g_counter.sem_empty);

    // 4. 模拟送餐耗时（临界区外执行）
    usleep((1200 + rand_r(&seed) % 800) * 1000); // 1.2 ~ 2.0 秒

    // 5. 如果自己端走的是最后一盘菜，启动打卡下班接力
    if (is_all_done) {
      sem_post(&g_counter.sem_full); // 唤醒下一个仍在阻塞的服务员
      break;
    }
  }

  printf("🏃 [🤵 服务员 %d] 所有菜品送达完毕，打卡下班！\n", waiter_id);
  return NULL;
}

// ================= 主函数 =================
int main() {
  memset(&g_counter, 0, sizeof(g_counter));

  // 初始化互斥锁
  pthread_mutex_init(&g_counter.lock, NULL);
  // 初始化信号量：空槽位初始为 4，菜品数初始为 0
  sem_init(&g_counter.sem_empty, 0, COUNTER_CAPACITY);
  sem_init(&g_counter.sem_full, 0, 0);

#define CHEF_NUM 3
#define WAITER_NUM 2

  pthread_t chefs[CHEF_NUM];
  pthread_t waiters[WAITER_NUM];
  int chef_ids[CHEF_NUM] = {1, 2, 3};
  int waiter_ids[WAITER_NUM] = {101, 102};

  printf("=========== 🏮 餐厅开门营业 (容量: %d, 今日单量: %d) ===========\n",
         COUNTER_CAPACITY, TOTAL_ORDERS);

  for (int i = 0; i < CHEF_NUM; ++i) {
    pthread_create(&chefs[i], NULL, chef_routine, (void *)&chef_ids[i]);
  }
  for (int i = 0; i < WAITER_NUM; ++i) {
    pthread_create(&waiters[i], NULL, waiter_routine, (void *)&waiter_ids[i]);
  }

  for (int i = 0; i < CHEF_NUM; ++i) {
    pthread_join(chefs[i], NULL);
  }
  for (int i = 0; i < WAITER_NUM; ++i) {
    pthread_join(waiters[i], NULL);
  }

  // 销毁同步设施
  pthread_mutex_destroy(&g_counter.lock);
  sem_destroy(&g_counter.sem_empty);
  sem_destroy(&g_counter.sem_full);

  printf("=========== 🌙 餐厅盘点结算完成，安全关门 ===========\n");
  return 0;
}
