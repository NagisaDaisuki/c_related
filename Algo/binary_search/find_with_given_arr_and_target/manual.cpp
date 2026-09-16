#include <iostream>
#include <vector>

// 返回目标值的 索引，如果没找到返回 -1
int binarySearch(const std::vector<int> &nums, int target) {
  // 工业级防御：空数组直接返回
  if (nums.empty())
    return -1;

  int low = 0;
  int high = nums.size() - 1;

  while (low <= high) {
    // 不用 (low + high) / 2 防止 int 内存溢出
    int mid = low + (high - low) / 2;

    if (nums[mid] == target) {
      return mid;
    } else if (nums[mid] < target) {
      low = mid + 1; // 目标在右侧
    } else {
      high = mid - 1; // 目标在左侧
    }
  }
  return -1; // 查找失败
}

int main(int argc, char *argv[]) {
  std::vector<int> arr = {13, 18, 24, 35, 47, 50, 62, 83, 90, 115, 134};
  int target = 90;

  int index = binarySearch(arr, target);

  if (index != -1)
    std::cout << "找到目标值 " << target << "，索引为：" << index << std::endl;
  else
    std::cout << "未找到目标值。" << std::endl;
}
