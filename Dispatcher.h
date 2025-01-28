#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "BoundedBuffer.h"
#include <vector>
#include <thread>
#include <memory>

class Dispatcher {
public:
    Dispatcher(std::vector<std::unique_ptr<BoundedBuffer>>& producerQueues, std::vector<std::unique_ptr<UnBoundedBuffer>>& dispatcherQueues);
    void dispatch();

private:
	std::vector<std::unique_ptr<BoundedBuffer>>& producerQueues_;
    std::vector<std::unique_ptr<UnBoundedBuffer>>& dispatcherQueues_;
};

#endif // DISPATCHER_H