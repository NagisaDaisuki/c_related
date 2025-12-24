#ifndef BUFFER_H
#define BUFFER_H

#include <queue>
#include <mutex>
#include <condition_variable>

class Buffer{
  public: 
    void addItem(int item);
    int removeItem();
  private:
    std::queue<int> items;
    std::mutex mutex;
    std::condition_variable cond;
};

#endif
