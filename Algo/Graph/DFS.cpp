#include <iostream>

using namespace std;

#define MVNum 100
// 最大 顶点数

// 图的 邻接表
struct ArcNode {    // 边结点
  int adjvex;       // 该边所指向的 顶点的 位置
  ArcNode *nextarc; // 指向 下一条边的指针
};

struct VNode {
  char data;         // 顶点信息
  ArcNode *firstarc; // 指向第一条依附在该顶点的边的指针
};

struct ALGraph {
  VNode vertices[MVNum]; // 邻接表
  int vexnum, arcnum;    // 图的当前顶点数和边数
};

bool visited[MVNum]; // 访问标志数组，其初值为 'false'

int LocateVex(ALGraph G, char v) {
  // 确定 点 v 在 G中的位置
  for (int i = 0; i < G.vexnum; i++) {
    if (G.vertices[i].data == v)
      return i;
  }
  return -1;
}

void CreateUDG(ALGraph &G) {
  // 采用 邻接表表示法，创建无向图 G
  int i, k;

  // 请输入总顶点数，总边数，以空格隔开
  cin >> G.vexnum >> G.arcnum;
  cout << endl;

  // 输入点的名称，如a
  for (i = 0; i < G.vexnum; ++i) { // 输入各点，构造表头结点表
    // 请输入各点的 名称
    cin >> G.vertices[i].data;     // 输入顶点值
    G.vertices[i].firstarc = NULL; // 初始化表头结点的指针域为 NULL
  }
  cout << endl;

  // 输入边依附的顶点，如a b
  for (k = 0; k < G.arcnum; ++k) {
    char v1, v2;
    int i, j;
    // 请输入各个边依附的顶点
    cin >> v1 >> v2;

    // 确定 v1 和 v2 在 G G中的位置， 即顶点在 G.vertices 中的序号
    i = LocateVex(G, v1);
    j = LocateVex(G, v2);

    ArcNode *p1 = new ArcNode; // 生成一个新的 边结点 *p1
    p1->adjvex = j;            // 邻接点序号为 j
    p1->nextarc = G.vertices[i].firstarc;
    G.vertices[i].firstarc = p1;

    ArcNode *p2 = new ArcNode; // 生成一个新的 边结点 *p2
    p2->adjvex = i;            // 邻接
    p2->nextarc = G.vertices[j].firstarc;
    G.vertices[j].firstarc = p2;
  }
}

void DFS(ALGraph G, int v) {
  // 1. 访问当前顶点：打印名字，并在全局数组visited打上“true”
  cout << G.vertices[v].data << " ";
  visited[v] = true;

  // 2. 顺藤摸瓜：拿到当前顶点的 邻居链表的头指针
  // 每一个结点只有一个 firstarc 通过 firstarc形成
  // 头插单链表实现对 ArcNode 的遍历， ArcNode上记录了
  // 每个结点在G.vertices[]数组中的相对位置
  // 通过这个值i访问 G.vertice[i].data 并通过 ArcNode
  // 的 nextarc 一直遍历
  ArcNode *p = G.vertices[v].firstarc;

  // 3. 遍历所有邻居
  while (p != NULL) {
    int w = p->adjvex; // 拿到邻居在数组中的下标

    // 如果 这个邻居还没有被访问过，立马添加进去
    if (!visited[w]) {
      DFS(G, w);
    }

    // 当这个邻居挖到底退出来后，继续看下一个邻居
    p = p->nextarc;
  }
}

int main() {
  // 采用 邻接表表示图的深度优先遍历
  ALGraph G;
  CreateUDG(G);
  cout << endl;
  // 请输入 遍历连通图的起始点
  char c;
  cin >> c;

  int i;

  for (i = 0; i < G.vexnum; i++) {
    if (c == G.vertices[i].data)
      break;
  }
  cout << endl;

  while (i >= G.vexnum) {
    cout << "该点不存在，请重新输入！" << endl;
    // 请输入 遍历连通图的起始点
    cin >> c;
    for (i = 0; i < G.vexnum; i++) {
      if (c == G.vertices[i].data)
        break;
    }
  }

  // 深度优先搜索遍历图的结果
  DFS(G, i);

  return 0;
}
