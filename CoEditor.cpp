#include "CoEditor.h"
#include <iostream>

// CoEditor constructor
CoEditor::CoEditor(UnBoundedBuffer& inputQueue, BoundedBuffer& outputQueue)
    : inputQueue_(inputQueue), outputQueue_(outputQueue) {}

// CoEditor edit function
void CoEditor::edit() {
    while (true) {
        std::string item = inputQueue_.remove();
        if (item == "DONE") {
            outputQueue_.insert("DONE");
            return;
        }

		// Simulate editing by blocking for 0.1 second
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

        outputQueue_.insert(item);
    }
}