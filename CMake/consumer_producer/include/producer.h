#ifndef PRODUCER_H
#define PRODUCER_H

#include "buffer.h"

class Producer
{
public:
    Producer(Buffer& buffer);
    void produce();
private:
    Buffer& buffer;
};

#endif
