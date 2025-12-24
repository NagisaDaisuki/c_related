#include "buffer.h"

void Buffer::addItem(int item)
{
  std::unique_lock<std::mutex> lock(mutex);
  items.push(item);
  cond.notify_all();
}

int Buffer::removeItem()
{
  std::unique_lock<std::mutex> lock(mutex);
  cond.wait(lock,[this]{ return !items.empty(); });
  int item = items.front();
  items.pop();
  return item;
}
