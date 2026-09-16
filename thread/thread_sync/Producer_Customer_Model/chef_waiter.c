#define _DEFAULT_SOURCE

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define COUNTER_CAPACITY 4 // 出餐台最多放 4 盘菜
#define TOTAL_ORDERS 12    // 才亭今天总共只做 12 道菜

// 菜品信息
typedef struct {
  int order_id;
  char name[32];
  int chef_id;
} Dish;

// 出餐台（临界资源与同步原语）
typedef struct {
  Dish table[COUNTER_CAPACITY]; // 环形缓冲区
  int head;                     // 服务员取菜位置
  int tail;                     // 厨师放菜位置
  int count;                    // 台面上当前菜品数

  int produced_count; // 已制作总数
  int served_count;   // 已上菜总数

  pthread_mutex_t lock;     // 保护出餐台的互斥锁
  pthread_cond_t not_full;  // 出餐台未满（通知厨师上菜）
  pthread_cond_t not_empty; // 出餐台非空（通知服务员端菜）
} ServingCounter;

ServingCounter g_counter;

const char *MENU[] = {"北京烤鸭", "麻婆豆腐", "宫保鸡丁", "水煮牛肉",
                      "清蒸鲈鱼"};

// ================= 厨师线程（生产者） =================
void *chef_routine(void *arg);

// ================= 服务员线程（消费者） =================
void *waiter_routine(void *arg);

// ================= 餐厅运营主入口 =================
int main() {
  // 1. 初始化出餐台与同步设施
  memset(&g_counter, 0, sizeof(g_counter));
  pthread_mutex_init(&g_counter.lock, NULL);
  pthread_cond_init(&g_counter.not_full, NULL);
  pthread_cond_init(&g_counter.not_empty, NULL);

#define CHEF_NUM 1
#define WAITER_NUM 5

  pthread_t chefs[CHEF_NUM];
  pthread_t waiters[WAITER_NUM];
  int chef_ids[CHEF_NUM];
  int waiter_ids[WAITER_NUM];
  // 根据厨师和服务员的数量分配对应的 id 号码
  for (int i = 0; i < CHEF_NUM; ++i) {
    chef_ids[i] = 10 + i;
  }

  for (int i = 0; i < WAITER_NUM; ++i) {
    waiter_ids[i] = 100 + i;
  }

  // int chef_ids[CHEF_NUM] = {1, 2};
  // int waiter_ids[WAITER_NUM] = {101, 102, 103};

  printf("=========== 🏮 餐厅开门营业 (容量: %d, 今日单量: %d) ===========\n",
         COUNTER_CAPACITY, TOTAL_ORDERS);

  // 2. 招聘并启动厨师和服务员线程
  for (int i = 0; i < CHEF_NUM; ++i) {
    pthread_create(&chefs[i], NULL, chef_routine, (void *)&chef_ids[i]);
  }

  for (int i = 0; i < WAITER_NUM; ++i) {
    pthread_create(&waiters[i], NULL, waiter_routine, (void *)&waiter_ids[i]);
  }

  // 3. 等待所有人员做完本班次并离场（回收资源）
  for (int i = 0; i < CHEF_NUM; ++i) {
    pthread_join(chefs[i], NULL);
  }

  for (int i = 0; i < WAITER_NUM; ++i) {
    pthread_join(waiters[i], NULL);
  }

  // 4. 销毁同步原语
  pthread_mutex_destroy(&g_counter.lock);
  pthread_cond_destroy(&g_counter.not_full);
  pthread_cond_destroy(&g_counter.not_empty);

  // 5.
  printf("=========== 🌙 餐厅盘点结算完成，安全关门 ===========\n");
  return 0;
}

// ================= 厨师线程（生产者） =================
void *chef_routine(void *arg) {
  int chef_id = *(int *)arg;
  unsigned int seed = (unsigned int)pthread_self();

  while (1) {
    // 1. 在临界区外烹饪（耗时 I/O 或计算绝不能占锁）
    usleep((200 + rand_r(&seed) % 150) * 10000); // 模拟炒菜 2000 - 3500 ms
    const char *dish_name = MENU[rand_r(&seed) % 5];

    pthread_mutex_lock(&g_counter.lock);

    // 检查当日指标是否已全部出完
    if (g_counter.produced_count >= TOTAL_ORDERS) {
      pthread_mutex_unlock(&g_counter.lock);
      break;
    }

    // 2. 出餐台满了，厨师必须端着盘子等待
    while (g_counter.count == COUNTER_CAPACITY) {
      printf("[👨‍🍳 厨师 %d] 槽位已满 "
             "(%d/%d)，暂停出餐，等待空位...\n",
             chef_id, g_counter.count, COUNTER_CAPACITY);
      pthread_cond_wait(&g_counter.not_full, &g_counter.lock);
    }

    // 醒来后第一件事：重新严密核对是否已达标（防止被其他厨师捷足先登）
    if (g_counter.produced_count >= TOTAL_ORDERS) {
      // 唤醒可能还卡在 not_full 的其他厨师，一起下班！
      pthread_cond_broadcast(&g_counter.not_full);
      pthread_mutex_unlock(&g_counter.lock);
      break;
    }

    // 3. 将菜品放在出餐台上
    int current_id = ++g_counter.produced_count;
    Dish *d = &g_counter.table[g_counter.tail];
    d->order_id = current_id;
    d->chef_id = chef_id;
    strncpy(d->name, dish_name, sizeof(d->name) - 1);

    g_counter.tail = (g_counter.tail + 1) % COUNTER_CAPACITY;
    g_counter.count++;

    printf(
        "  👉 [👨‍🍳 厨师 %d] 上菜: #%02d <%s> (出餐台存量: "
        "%d/%d)\n",
        chef_id, current_id, dish_name, g_counter.count, COUNTER_CAPACITY);

    // 4. 叮铃！按响叫餐铃，通知服务员来端菜
    pthread_cond_signal(&g_counter.not_empty);
    // 如果这是最后一道菜，广播唤醒所有可能还在等的厨师
    if (g_counter.produced_count >= TOTAL_ORDERS) {
      pthread_cond_broadcast(&g_counter.not_full);
    }

    pthread_mutex_unlock(&g_counter.lock);
  }
  printf("[👨‍🍳 厨师 %d] 今日份菜单已做完，打烊收工！\n",
         chef_id);
  return NULL;
}

// ================= 服务员线程（消费者） =================
void *waiter_routine(void *arg) {
  int waiter_id = *(int *)arg;
  unsigned int seed = (unsigned int)pthread_self();

  while (1) {
    pthread_mutex_lock(&g_counter.lock);

    // 1. 出餐台是空的，服务员等待叫餐
    while (g_counter.count == 0) {
      // 如果所有菜品都已经上完，服务员直接下班
      if (g_counter.served_count >= TOTAL_ORDERS) {
        pthread_mutex_unlock(&g_counter.lock);
        goto finish;
      }
      printf("[🤵 服务员 %d] 正在等餐中...\n", waiter_id);

      pthread_cond_wait(&g_counter.not_empty, &g_counter.lock);
    }
    // 2. 从出餐台取走菜品
    Dish d = g_counter.table[g_counter.head];
    g_counter.head = (g_counter.head + 1) % COUNTER_CAPACITY;
    g_counter.count--;
    g_counter.served_count++;
    printf("⚡ [🤵 服务员 %d] 端走: #%02d <%s> (由 厨师%d 制作, 剩余: %d/%d)\n",
           waiter_id, d.order_id, d.name, d.chef_id, g_counter.count,
           COUNTER_CAPACITY);

    // 3. 通知等待中的厨师：出餐位有空位了！
    pthread_cond_signal(&g_counter.not_full);

    // 如果全部菜品都端完了，唤醒可能仍在沉睡的其他服务员一起下班
    if (g_counter.served_count >= TOTAL_ORDERS) {
      pthread_cond_broadcast(&g_counter.not_empty);
    }

    pthread_mutex_unlock(&g_counter.lock);

    // 4. 端到顾客桌上（临界区外耗时模拟）
    usleep((150 + rand_r(&seed) % 150) * 10000); // 模拟送餐 1500 ~ 3000 ms
  }

finish:
  printf("🏃[🤵 服务员 %d] 所有菜品送达完毕，打烊收工！\n", waiter_id);
  return NULL;
}