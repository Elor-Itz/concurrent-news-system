#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "BoundedBuffer.h"
#include <thread>

class ScreenManager {
public:
    explicit ScreenManager(BoundedBuffer& outputQueue, size_t expectedDones);
    void display();

private:
    BoundedBuffer& outputQueue_;
	size_t expectedDones_;
};

#endif // SCREENMANAGER_H