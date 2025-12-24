#include "producer.h"
#include <iostream>

Producer::Producer(Buffer& buffer) : buffer(buffer) {}

void Producer::produce()
{
  for(int i = 0;i < 10;++i)
  {
    int data = i + 1;
    buffer.addItem(data);
    std::cout << "Produced: " << data << std::endl;
  }
}
