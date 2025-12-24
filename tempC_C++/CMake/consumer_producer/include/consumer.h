#ifndef CONSUMER_H
#define CONSUMER_H

#include "buffer.h"
class Consumer{
public:
  Consumer(Buffer& buffer);
  void consume();
private:
  Buffer& buffer;
};

#endif
