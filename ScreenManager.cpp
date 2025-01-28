#include "ScreenManager.h"
#include <iostream>

// ScreenManager constructor
ScreenManager::ScreenManager(BoundedBuffer& outputQueue, size_t expectedDones) :
	outputQueue_(outputQueue), expectedDones_(expectedDones)
{}

// ScreenManager thread function
void ScreenManager::display() {
	size_t doneCount = 0;
    while (doneCount < expectedDones_) {
        std::string item = outputQueue_.remove();
        std::cout << "Displaying: " << item << std::endl;
        if (item == "DONE") {
			++doneCount;			
		}
    }
	std::cout << "DONE" << std::endl;
}