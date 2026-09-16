#define _DEFAULT_SOURCE

#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
临界资源（充电桩 ChargingStation）：
单枪超充桩：同一时刻只允许一辆车插入充电枪并通电。
桩上带有统计看板：累计充电次数 total_charge_times、累计输出电量
total_kwh_delivered。 充电桩内嵌一把互斥锁 pthread_mutex_t lock。

工作线程（电动汽车 ElectricVehicle）：
普通私家车（调用 pthread_mutex_lock）：无论排队多久，必须死等直到充满。
网约车/急救车（调用
pthread_mutex_trylock）：如果充电桩有人，绝不等待，直接跑去接单或绕圈重试。
*/

// ================= 结构体设计 =================
typedef struct ChargingStation {
  int station_id;             // 充电桩编号
  int is_occupied;            // 物理占用标志（0：空闲，1：占用中）
  int total_charge_times;     // 临界数据：历史累计充电次数
  double total_kwh_delivered; // 临界数据：历史累计输出电量（kWh）
  pthread_mutex_t lock;       // 保护该充电桩所有状态的互斥锁
} ChargingStation;

typedef struct ElectricVehicle {
  int car_id;                // 车辆编号
  char model[20];            // 车型
  double battery_needed_kwh; // 本次需要充入的电量
  int is_urgent;             // 是否是急救/急单车(1: 使用 trylock, 0: 使用 lock)
  ChargingStation *station;  // 目标充电桩指针
} ElectricVehicle;

void Init_ChargingStation(ChargingStation *cs, const int id, const int is_ocp,
                          const int tct, const double tkd);
void *Car_Charging_Routine(void *arg);

// ================= 主函数：调度与生命周期 =================

int main() {
  // 1. 初始化临界资源：充电桩
  ChargingStation station;
  Init_ChargingStation(&station, 888, 0, 0, 0.0);

  // 动态初始化互斥锁
  pthread_mutex_init(&station.lock, NULL);

  printf("================ ⚡ 特斯拉超级充电站 #%d 启动运营 ================\n",
         station.station_id);
// 2. 准备 5 辆车并发驶入充电站
#define CAR_NUM 5
  pthread_t tids[CAR_NUM];
  ElectricVehicle cars[CAR_NUM] = {
      {.car_id = 1,
       .model = "Model 3",
       .battery_needed_kwh = 45.0,
       .is_urgent = 0,
       .station = &station},
      {.car_id = 2,
       .model = "Model Y",
       .battery_needed_kwh = 60.0,
       .is_urgent = 0,
       .station = &station},
      {.car_id = 3,
       .model = "出租车",
       .battery_needed_kwh = 30.0,
       .is_urgent = 1,
       .station = &station}, // 紧急单
      {.car_id = 4,
       .model = "Cybertruck",
       .battery_needed_kwh = 100.0,
       .is_urgent = 0,
       .station = &station},
      {.car_id = 5,
       .model = "急救特种车",
       .battery_needed_kwh = 20.0,
       .is_urgent = 1,
       .station = &station} // 紧急单
  };

  // 3. 同时并发创建 5 个车辆线程
  for (int i = 0; i < CAR_NUM; ++i) {
    pthread_create(&tids[i], NULL, Car_Charging_Routine, (void *)&cars[i]);
  }

  // 4. 主线程等待所有车辆离场
  for (int i = 0; i < CAR_NUM; ++i) {
    pthread_join(tids[i], NULL);
  }

  // 5. 验证最终数据准确性
  printf("\n================ 营业结束结算 ================\n");
  printf("充电站最终看板:\n");
  printf("  * 最终累计服务车辆: %d 次\n", station.total_charge_times);
  printf("  * 最终累计输送电量: %.1f kWh\n", station.total_kwh_delivered);

  // 6. 销毁互斥锁
  pthread_mutex_destroy(&station.lock);

  return EXIT_SUCCESS;
}

void Init_ChargingStation(ChargingStation *cs, const int id, const int is_ocp,
                          const int tct, const double tkd) {
  if ((id < 0 || id >= 100000) || (is_ocp != 0 && is_ocp != 1))
    return;
  cs->station_id = id;
  cs->is_occupied = is_ocp;
  cs->total_charge_times = tct;
  cs->total_kwh_delivered = tkd;
  fprintf(stdout, "初始化充电桩成功。\n");
}
void *Car_Charging_Routine(void *arg) {
  ElectricVehicle *ev = (ElectricVehicle *)arg;
  ChargingStation *cs = ev->station;

  printf("[车辆 %02d (%s)]到达充电站，准备充电（需求：%.1f kWh）...\n",
         ev->car_id, ev->model, ev->battery_needed_kwh);

  if (ev->is_urgent) {
    // 场景 A：急躁的车辆，使用 trylock，忙就不等
    int retry_count = 0;
    while (1) {
      int ret = pthread_mutex_trylock(&cs->lock);
      if (ret == 0) {
        // 成功抢到锁
        printf("[车辆 %02d (紧急)]成功抢到空闲充电枪！\n", ev->car_id);
      } else if (ret == EBUSY) {
        // 桩被占领，非阻塞返回
        retry_count++;
        printf("[车辆 %02d (紧急)]发现桩被占用！不排队，绕圈巡游第 %d 次...\n",
               ev->car_id, retry_count);
        usleep(500000); // 绕圈 500 毫秒后再回来看看
        if (retry_count >= 3) {
          printf("[车辆 %02d (紧急)]放弃本地充电，驶向其他充电站！\n",
                 ev->car_id);
          pthread_exit(NULL);
        }
      }
    }
  } else {
    // 场景 B：普通私家车，使用 lock 阻塞死等，直到前面的车拔枪
    printf("[车辆 %02d (%s)]进入排队序列，挂起等待...\n", ev->car_id,
           ev->model);
    pthread_mutex_lock(&cs->lock);
    printf("[车辆 %02d (%s)]排到自己了，成功插枪！\n", ev->car_id, ev->model);
  }

  // ---------------- 临界区开始 (Critical Section) ----------------
  // 此时硬件和内存状态完全受互斥锁保护，任何其他车辆进不来

  cs->is_occupied = 1;

  // 模拟充电物理耗时(微秒)
  usleep(2000000); // 2s

  // 关键统计数据更新（杜绝竞态条件 Data Race）
  cs->total_charge_times++;
  cs->total_kwh_delivered += ev->battery_needed_kwh;
  printf("[车辆 %02d (%s)] 充电完毕！拔枪离开。(当前桩累计充了 %d"
         " 辆车，累计送电 %.1f kWh。)\n",
         ev->car_id, ev->model, cs->total_charge_times,
         cs->total_kwh_delivered);
  cs->is_occupied = 0;
  pthread_mutex_unlock(&cs->lock);
  // ---------------- 临界区结束 ----------------

  pthread_exit(NULL);
}
