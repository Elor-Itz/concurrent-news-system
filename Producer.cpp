#include "Producer.h"
#include <iostream>
#include <random>

// Producer constructor
Producer::Producer(int id, int numProducts, BoundedBuffer& buffer)
    : id_(id), numProducts_(numProducts), buffer_(buffer) {}

// Producer thread function
void Producer::produce() {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 2);
	
	size_t alreadyProduced[3] = { 0 };
    for (int j = 0; j < numProducts_; ++j) {
        // Randomly select the type
		size_t typeIndex = dis(gen);
        std::string type;
        switch (typeIndex) {
            case 0:
                type = "SPORTS";
                break;
            case 1:
                type = "NEWS";
                break;
            case 2:
                type = "WEATHER";
                break;
		}

        // Construct the product string
        std::string product = "Producer " + std::to_string(id_) + " " + type + " " + std::to_string(alreadyProduced[typeIndex]);
        buffer_.insert(product);

		++alreadyProduced[typeIndex];
    }
    buffer_.insert("DONE");
}