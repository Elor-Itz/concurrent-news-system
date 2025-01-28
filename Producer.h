#ifndef PRODUCER_H
#define PRODUCER_H

#include "BoundedBuffer.h"
#include <string>
#include <thread>

class Producer {
public:
    Producer(int id, int numProducts, BoundedBuffer& buffer);
    void produce();

private:
    int id_;
    int numProducts_;
    BoundedBuffer& buffer_;
};

#endif // PRODUCER_H