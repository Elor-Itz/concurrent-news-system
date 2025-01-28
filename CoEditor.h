#ifndef COEDITOR_H
#define COEDITOR_H

#include "BoundedBuffer.h"
#include <thread>

class CoEditor {
public:
    CoEditor(UnBoundedBuffer& inputQueue, BoundedBuffer& outputQueue);
    void edit();

private:
	UnBoundedBuffer& inputQueue_;
    BoundedBuffer& outputQueue_;
};

#endif // COEDITOR_H