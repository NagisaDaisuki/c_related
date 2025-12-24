#include "producer.h"
#include "consumer.h"
#include "buffer.h"
#include <thread>

int main()
{
  Buffer buffer;
  Producer producer(buffer);
  Consumer consumer(buffer);
  
  std::thread producerThread(&Producer::produce, &producer);
  std::thread consumerThread(&Consumer::consume, &consumer);

  producerThread.join();
  consumerThread.join();

  return 0;
}
