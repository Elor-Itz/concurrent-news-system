#ifndef BOUNDEDBUFFER_H
#define BOUNDEDBUFFER_H

#include <string>
#include <deque>
#include <mutex>
#include <condition_variable>

class BoundedBuffer {
private:
    std::deque<std::string> buffer;
    int capacity;
    std::mutex mtx;
    std::condition_variable not_full;
    std::condition_variable not_empty;

public:
    explicit BoundedBuffer(int size);  // Explicit constructor

    void insert(const std::string& item);
    std::string remove();

	// Check if empty without waiting until it's not
	bool empty();
};

class UnBoundedBuffer : public BoundedBuffer {
public:
	UnBoundedBuffer();
};

#endif // BOUNDEDBUFFER_H