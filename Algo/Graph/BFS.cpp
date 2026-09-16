#include <iostream>
using namespace std;

#define MVNum 20    // 最大顶点数
#define MAXQSIZE 20 // 最大队列长度

bool visited[MVNum]; // 访问标志数组，初值为 "false"

// 图的 邻接矩阵存储表示
struct Graph {
  int vexs[MVNum];        // 顶点表
  int arcs[MVNum][MVNum]; // 边表
  int vexnum, arcnum;     // 数量
};

// 队列 的定义以及操作
struct sqQueue {
  int *base; // 初始化的动态分配存储空间
  int front; // 头指针，若队列不为空，指向队头元素
  int rear;  // 尾指针，若队列不为空，指向队尾元素的下一个位置
};

void InitQueue(sqQueue &Q) {
  // 构造一个空队列 Q
  Q.base = new int[MAXQSIZE];
  if (!Q.base)
    cout << "存储分配失败";
  Q.front = Q.rear = 0;
}

void EnQueue(sqQueue &Q, int e) {
  // 插入元素 e 为 Q 的新的队尾元素
  if ((Q.rear + 1) % MAXQSIZE == Q.front)
    return;

  Q.base[Q.rear] = e;
  Q.rear = (Q.rear + 1) % MAXQSIZE;
}

bool QueueEmpty(sqQueue Q) {
  // 判断是否为空队列
  if (Q.rear == Q.front)
    return true;
  return false;
}

void DeQueue(sqQueue &Q, int &u) {
  // 队头元素出队并置为u
  u = Q.base[Q.front];
  Q.front = (Q.front + 1) % MAXQSIZE;
}

int LocateVex(Graph G, int v) {
  // 确定点v在G中的位置
  for (int i = 0; i < G.vexnum; i++) {
    if (G.vexs[i] == v)
      return i;
  }
  return -1;
}

void CreateUDN(Graph &G) {
  // 采用邻接矩阵表示法，创建无向网G
  int i, j, k;
  // 输入总顶点数，总边数，以空格隔开
  cin >> G.vexnum >> G.arcnum; // 输入总顶点数，总边数
  // 输入点的名称，如a
  for (i = 0; i < G.vexnum; ++i) {
    // 请输入各个点的名称
    cin >> G.vexs[i]; // 依次输入点的信息
  }
  for (i = 0; i < G.vexnum; ++i) // 初始化邻接矩阵，边的权值均置为极大值MaxInt
    for (j = 0; j < G.vexnum; ++j)
      G.arcs[i][j] = 0;
  // 输入边依附的顶点，如a  b
  for (k = 0; k < G.arcnum; ++k) { // 构造邻接矩阵
    int v1, v2;
    // 输入各个边依附的顶点
    cin >> v1 >> v2; // 输入一条边依附的顶点
    i = LocateVex(G, v1);
    j = LocateVex(G, v2);        // 确定v1和v2在G中的位置，即顶点数组的下标
    G.arcs[i][j] = 1;            // 边<v1,  v2>的权值置为w
    G.arcs[j][i] = G.arcs[i][j]; // 置<v1,  v2>的对称边<v2,  v1>的权值为w
  } // for
}
int FirstAdjVex(Graph G, int v) {
  // 返回v的第一个邻接点
  int i;
  for (i = 0; i < G.vexnum; ++i) {
    if (G.arcs[v][i] == 1 && visited[i] == false)
      return i;
  }
  return -1;
} // FirstAdjVex

int NextAdjVex(Graph G, int v, int w) {
  // 返回v相对于w的下一个邻接点
  int i;
  for (i = w + 1; i < G.vexnum; ++i) {
    if (G.arcs[v][i] == 1 && visited[i] == false)
      return i;
  }
  return -1;
} // NextAdjVex

void BFS(Graph G, int v) {
  // 1. 访问起点，打印并打上“已访问”的思想钢印
  cout << G.vexs[v] << " ";
  visited[v] = true;

  // 2. 初始化战术队列，并将起点入队
  sqQueue Q;
  InitQueue(Q);
  EnQueue(Q, v);

  // 3. 只要队列不空，雷达就持续扫描！
  while (!QueueEmpty(Q)) {
    int u;
    DeQueue(Q, u); // 队头元素出队，u 成为当前正在释放波纹的“中心辐射点”

    // 4. 暴力扫荡当前中心点 u 的所有直接邻居！
    // 利用封装好的 FirstAdjVex 和 NextAdjVex，在邻接矩阵里横向巡逻
    for (int w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w)) {

      // 只要遇到没被访问过的邻居
      if (!visited[w]) {
        cout << G.vexs[w] << " "; // 发现新大陆，立刻打印！
        visited[w] = true;        // 烙上钢印，防止别人重复找他
        EnQueue(Q, w); // 塞入队列末尾，他将成为下一波（下一层级）的辐射中心
      }
    }
  }
}

int main() {
  Graph G;
  CreateUDN(G);

  // 输入遍历连通图的 起始点
  int c;
  cin >> c;

  int i;
  for (i = 0; i < G.vexnum; ++i) {
    if (c == G.vexs[i])
      break;
  }

  if (i >= G.vexnum)
    cout << "error!";
  // 广度优先搜索遍历连通图结果
  BFS(G, i);

  cout << endl;
  return 0;
}
