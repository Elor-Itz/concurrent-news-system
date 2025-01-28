#include "BoundedBuffer.h"

// BoundedBuffer constructor
BoundedBuffer::BoundedBuffer(int size) : capacity(size) {}

// BoundedBuffer insert function
void BoundedBuffer::insert(const std::string& item) {
    std::unique_lock<std::mutex> lock(mtx);
    not_full.wait(lock, [this]() { return buffer.size() < capacity; });
    buffer.push_back(item);
    not_empty.notify_one();
}

// BoundedBuffer remove function
std::string BoundedBuffer::remove() {
    std::unique_lock<std::mutex> lock(mtx);
    not_empty.wait(lock, [this]() { return !buffer.empty(); });
    std::string item = buffer.front();
    buffer.pop_front();
    not_full.notify_one();
    return item;
}

// BoundedBuffer empty function
bool BoundedBuffer::empty() {
	// Check if empty without waiting until it's not
	std::unique_lock<std::mutex> lock(mtx);
	return buffer.empty();
}

UnBoundedBuffer::UnBoundedBuffer() : BoundedBuffer(INT_MAX) {}