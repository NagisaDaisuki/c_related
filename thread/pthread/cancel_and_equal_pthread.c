#define _POSIX_C_SOURCE 200112L
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 全局记录子线程  1 的 ID，方便线程 2 做比较验证
pthread_t g_tid1;

// ---------------- 子线程 1：耗时任务（将被主线程取消） ----------------

void *worker_long_job(void *arg) {
  (void)arg;
  pthread_t my_id = pthread_self();
  printf("[线程1]启动，ID: %ld\n", (long)my_id);
  for (int i = 1; i <= 10; ++i) {
    printf("[线程1]正在执行批处理任务 (%d/10)...\n", i);
    // sleep() 是一个标准的 POSIX 取消点 (Cancellation Point)
    sleep(1);
  }

  printf("[线程1]任务全部完成并且正常退出。\n");
  return NULL;
}

// ---------------- 子线程 2：快速计算（正常退出并返回数据） ----------------

void *worker_quick_job(void *arg) {
  int factor = *(int *)arg;
  pthread_t my_id = pthread_self();

  // 核心演示：使用pthread_equal 检查自身与全局记录的 tid1 是否不同
  if (pthread_equal(my_id, g_tid1)) {
    printf("[线程2]异常：我的ID居然和线程1相同！\n");
  } else {
    printf("[线程2]启动成功，确认自身 ID (%ld) 与线程 1 彼此独立。\n",
           (long)my_id);
  }

  // 模拟一段短平快的计算
  sleep(1);

  int *result = (int *)malloc(sizeof(int));
  *result = factor * 42;

  printf("[线程2]计算完成，调用 pthread_exit 返回结果指针...\n");
  pthread_exit((void *)result);
}

// ---------------- 主线程 ----------------
int main() {
  pthread_t g_tid2;
  int input_val = 10;

  printf("[主线程]正在创建子线程1 和子线程2...\n");

  // 1. 创建子线程 1
  pthread_create(&g_tid1, NULL, worker_long_job, NULL);

  // 2. 创建子线程 2
  pthread_create(&g_tid2, NULL, worker_quick_job, (void *)&input_val);

  // 3. 主线程等待 2.5 秒，让线程 1 跑几轮、线程2跑完
  sleep(2);
  printf("\n[主线程]检测到线程1耗时过长，准备向其发送取消信号...\n");

  // 核心演示：取消线程1
  pthread_cancel(g_tid1);

  // 4. 回收线程2 (验证正常退出的返回值)
  void *retval2 = NULL;
  pthread_join(g_tid2, &retval2);
  if (retval2 != PTHREAD_CANCELED) {
    int *ans = (int *)retval2;
    printf("[主线程]成功回收线程2，获得计算结果: %d\n", *ans);
    free(ans); // 回收堆内存
  }

  // 5. 回收线程1 （验证取消退出的标志）
  void *retval1 = NULL;
  pthread_join(g_tid1, &retval1);

  // 核心演示：判断线程是否因为 pthread_cancel 而终结
  if (retval1 == PTHREAD_CANCELED) {
    printf("[主线程]成功回收线程1:确认该线程已被成功取消(PTHREAD_CANCELED)!\n");
  } else {
    printf("[主线程]线程1正常跑完退出。\n");
  }

  printf("[主线程] 所有子线程资源回收完毕，程序安全退出。\n");
  return EXIT_SUCCESS;
}