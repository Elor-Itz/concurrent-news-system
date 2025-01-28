#include "BoundedBuffer.h"
#include "Producer.h"
#include "Dispatcher.h"
#include "CoEditor.h"
#include "ScreenManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>

// Main program
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./main <input_file>" << std::endl;
        return 1;
    }

    // Open input file
    std::ifstream inputFile(argv[1]);
    if (!inputFile) {
        std::cerr << "Error: Unable to open input file." << std::endl;
        return 1;
    }    

    std::vector<std::unique_ptr<BoundedBuffer>> producerQueues;
    std::vector<Producer> producers;
    int bufferSize = 0;

    std::string line;    
    int producerId, numProducts, queueSize;
    while (inputFile >> producerId) {           
        inputFile >> numProducts;        
        if (inputFile.eof()) { // Reached the end of the file, then it's co-editor queue size
            bufferSize = producerId;
            if (bufferSize <= 0) {
                std::cerr << "Error: Cannot create an empty buffer queue!" << std::endl;
                return 1;   
            }            
        } else {
            inputFile >> queueSize;
            if (queueSize <= 0) {
                std::cerr << "Error: Cannot create an empty queue!" << std::endl;
                return 1;   
            }
            producerQueues.emplace_back(std::make_unique<BoundedBuffer>(queueSize));            
            producers.emplace_back(producerId, numProducts, *producerQueues.back());
        }
    }    
	
	const size_t numberOfTypes = 3;
    // Create dispatcher queues
    std::vector<std::unique_ptr<UnBoundedBuffer>> dispatcherQueues;	
	for (size_t i = 0; i < numberOfTypes; ++i) {
		dispatcherQueues.emplace_back(std::make_unique<UnBoundedBuffer>());
	}

    // Start Producer Threads
    std::vector<std::thread> producerThreads;
    for (auto& producer : producers) {
        producerThreads.emplace_back([&producer] { producer.produce(); });
    }

    // Start Dispatcher Thread
    Dispatcher dispatcher(producerQueues, dispatcherQueues);
    std::thread dispatcherThread([&dispatcher] { dispatcher.dispatch(); });

	// Create co-editor queue
	BoundedBuffer coEditorQueue(bufferSize);

	// Create Co-Editors
	std::vector<CoEditor> coEditors;
	for (size_t i = 0; i < dispatcherQueues.size(); ++i) {
		coEditors.emplace_back(*dispatcherQueues[i], coEditorQueue);
	}
	
    // Start Co-Editor Threads
	std::vector<std::thread> coEditorThreads;
	for (auto& coEditor : coEditors) {
		coEditorThreads.emplace_back([&coEditor] { coEditor.edit(); });
	}

	// Start Screen Manager Thread
    ScreenManager screenManager(coEditorQueue, coEditors.size());
    std::thread screenManagerThread([&screenManager] { screenManager.display(); });

    // Join Producer Threads
    for (auto& thread : producerThreads) {
        thread.join();
    }

    // Join Dispatcher Thread
    dispatcherThread.join();

    // Join Co-Editor Threads
	for (auto& thread : coEditorThreads) {
		thread.join();
	}

    // Join Screen Manager Thread
    screenManagerThread.join();

    return 0;
}