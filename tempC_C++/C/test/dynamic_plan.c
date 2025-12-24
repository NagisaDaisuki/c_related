#include <stdio.h>

#define MAX_SIZE 105

// 全局变量定义
int R, C;
int matrix[MAX_SIZE][MAX_SIZE]; // 存储高度
int dp[MAX_SIZE][MAX_SIZE]; // 记忆化数组，dp[i][j] 存储从 (i,j)出发的最大长度

// 方向数组：上下左右
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

// 辅助函数：求最大值
inline int max(int a, int b) { return a > b ? a : b; }

// 记忆化搜索函数
int dfs(int x, int y) {

  // 1. 如果已经计算过(不为0)直接返回缓存的结果
  if (dp[x][y] != 0)
    return dp[x][y];

  // 2. 默认长度为1 （如果四周都不能走，就是自己这一格）
  int max_len = 1;

  // 3. 遍历上下左右四个方向
  for (int i = 0; i < 4; i++) {
    int nx = x + dx[i];
    int ny = y + dy[i];

    // 检查边界
    if (nx >= 0 && nx < R && ny >= 0 && ny < C) {
      // 检查高度条件：必须向下滑行（邻居高度 < 当前高度）
      if (matrix[nx][ny] < matrix[x][y]) {
        // 状态转移：当前最大长度 = max (已知最大长度,1 + 邻居能走的最大长度)
        max_len = max(max_len, 1 + dfs(nx, ny));
      }
    }
  }

  dp[x][y] = max_len;
  return max_len;
}

int main() {
  // 输入行和列
  if (scanf("%d %d", &R, &C) != EOF) {
    // 读取矩阵高度
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        scanf("%d", &matrix[i][j]);
        // 初始化dp数组为0，表示尚未计算
        dp[i][j] = 0;
      }
    }

    int global_max = 0;

    // 遍历每一个点作为起点，寻找整个地图中的最大值
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        // 更新全局最大值
        global_max = max(global_max, dfs(i, j));
      }
    }

    // 输出结果
    printf("%d\n", global_max);
  }

  return 0;
}
