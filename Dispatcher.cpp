#include "Dispatcher.h"
#include <iostream>
#include <sstream>

// Dispatcher constructor
Dispatcher::Dispatcher(std::vector<std::unique_ptr<BoundedBuffer>>& producerQueues, std::vector<std::unique_ptr<UnBoundedBuffer>>& dispatcherQueues) : 
	producerQueues_(producerQueues), dispatcherQueues_(dispatcherQueues)
{}

// Dispatcher thread function
void Dispatcher::dispatch() {
	size_t doneCount = 0;
    while (true) {
		// Going round robin
        for (size_t i = 0; i < producerQueues_.size(); ++i) {			
			// Because of the requirement: "The Dispatcher does not block when the queues are empty."
			// Check if the queue is empty before calling remove which blocks
			if (producerQueues_[i]->empty()) {
				continue;
			}

            std::string item = producerQueues_[i]->remove();
            if (item == "DONE") {				
				++doneCount;

				if (doneCount == producerQueues_.size()) {
					// All producers are done, send done to all editors
					for (size_t j = 0; j < dispatcherQueues_.size(); ++j) {
						dispatcherQueues_[j]->insert("DONE");
					}
					return;
				}; 
				continue;
            }

			std::istringstream str(item);
			std::string producerStr, type;
			int producerId = 0, alreadyProduced = 0;
			str >> producerStr >> producerId >> type >> alreadyProduced;
			
			int index = 0;
			if (type == "SPORTS") {
				index = 0;
			}
			else if (type == "NEWS") {
				index = 1;
			}
			else if (type == "WEATHER") {
				index = 2;
			}
			else {
				std::cerr << "Invalid message type: " << item << std::endl;
				continue; // Skip inserting if invalid type
			}

            dispatcherQueues_[index]->insert(item);
        }
    }
}
