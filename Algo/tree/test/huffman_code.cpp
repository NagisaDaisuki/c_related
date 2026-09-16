#include <cstddef>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <string>
#include <vector>

// 1. 节点定义
struct HuffmanNode {
  int weight;
  char symbol; // 内部节点统一用 '\0' 表示
  HuffmanNode *left;
  HuffmanNode *right;

  HuffmanNode(int w, char s = '\0', HuffmanNode *l = nullptr,
              HuffmanNode *r = nullptr)
      : weight(w), symbol(s), left(l), right(r) {}
};

// 2. 优先队列比较器 (小堆顶)
struct CompareNode {
  bool operator()(const HuffmanNode *a, const HuffmanNode *b) const {
    if (a->weight == b->weight) {
      // 当权重相同时的“僵局打破策略”(Tie-breaker)。
      // 为了尽量生成与图中样例一致的树形结构（D和E结合，B和C结合），
      // 我们利用字符的 ASCII 码或特定规则进行稳定排序。
      // 实际 OJ 中若只考查最终带权路径长度(WPL)，此策略可简略。
      return a->symbol > b->symbol;
    }
    return a->weight > b->weight;
  }
};

class HuffmanTree {
private:
  // 核心架构：Arena
  // 内存池。这里独占所有动态分配的内存，析构时自动且无情地清理一切。
  std::vector<std::unique_ptr<HuffmanNode>> nodes_arena_;
  HuffmanNode *root_ = nullptr;
  std::map<char, std::string> huffman_codes_;

  // 内部工厂方法：在池中捏出节点交出观测指针。
  HuffmanNode *createNode(int weight, char symbol = '\0',
                          HuffmanNode *left = nullptr,
                          HuffmanNode *right = nullptr) {
    nodes_arena_.push_back(
        std::make_unique<HuffmanNode>(weight, symbol, left, right));
    return nodes_arena_.back().get();
  }

  // DFS 遍历生成最终编码
  void generateCodes(HuffmanNode *node, const std::string &code) {
    if (!node)
      return;

    // 遇到真实的叶子节点，记录编码
    if (node->symbol != '\0') {
      huffman_codes_[node->symbol] = code;
    }

    // 左 0 右 1
    generateCodes(node->left, code + "0");
    generateCodes(node->right, code + "1");
  }

public:
  void build(const std::vector<int> &weights) {
    std::priority_queue<HuffmanNode *, std::vector<HuffmanNode *>, CompareNode>
        pq;

    // 步骤一：初始化所有叶子节点并入队
    char current_char = 'A';
    for (int w : weights) {
      pq.push(createNode(w, current_char++));
    }

    // 步骤二：不断取最小的两个节点合并，直到只剩根节点
    while (pq.size() > 1) {
      HuffmanNode *left = pq.top();
      pq.pop();
      HuffmanNode *right = pq.top();
      pq.pop();

      // 新节点的权重是左右子树之和
      // 注意：通常约定左子树权重较小
      HuffmanNode *parent =
          createNode(left->weight + right->weight, '\0', left, right);
      pq.push(parent);
    }

    // 步骤三：保存根节点，开启深搜生成代码
    if (!pq.empty()) {
      root_ = pq.top();
      generateCodes(root_, "");
    }
  }

  // 现代 C++ 规范：警告调用者不要忽略查询的返回值
  [[nodiscard]] std::string getCode(char symbol) const {
    auto it = huffman_codes_.find(symbol);
    return (it != huffman_codes_.end()) ? it->second : "";
  }
};

int main() {
  // 极限压榨 I/O 性能，解除与 C 风格 I/O的同步绑定
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  if (!(std::cin >> n))
    return 0;

  std::vector<int> weights(n);
  for (int i = 0; i < n; i++)
    std::cin >> weights[i];

  HuffmanTree huffman;
  huffman.build(weights);

  // 严格按照输入顺序 (A, B, C...) 打印最终二进制编码
  for (int i = 0; i < n; i++) {
    char symbol = 'A' + i;
    std::cout << huffman.getCode(symbol) << "\n";
  }
  return 0;
}
