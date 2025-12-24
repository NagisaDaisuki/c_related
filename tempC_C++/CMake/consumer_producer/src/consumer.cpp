#include "consumer.h"
#include <iostream>

Consumer::Consumer(Buffer& buffer) : buffer(buffer){}

void Consumer::consume()
{
  for(int i = 0;i < 10;++i)
  {
    int data = buffer.removeItem();
    std::cout << "Consumed: " << data << std::endl;
  }
}
