#include <cse4733/power_calculator.hpp>

#include <thread>
#include <chrono>
#include <cmath>
#include <iostream>
#include <random>

namespace cse4733 {

PowerCalculator::PowerCalculator(): is_running(true) {}

void PowerCalculator::start() {
    std::thread t1(&PowerCalculator::thread1_task, this);
    std::thread t2(&PowerCalculator::thread2_task, this);

    t1.join();
    t2.join();
}

// Generates random pairs (base, power) of numbers and pushes them to a queue
void PowerCalculator::thread1_task() {
    std::random_device rd;                              // Create an instance of std::random_device
    std::mt19937 gen(rd());                             // Create an instance of std::mt19937
    std::uniform_int_distribution<> dist(1, 100);       // Create a uniform integer distribution for the integer values (1 - 100)
    std::uniform_int_distribution<> power_dist(1, 10);  // Create a uniform integer distribution for the power value (1-10)

    auto start = std::chrono::high_resolution_clock::now(); // Capture the start time
    auto limit = std::chrono::microseconds(50);             // Set the time limit to 50 microseconds

    while (true) {
        {
            std::lock_guard<std::mutex> guard(mtx);         // Create an instance of std::lock_guard
            int value = dist(gen);                          // Get a random value
            int power = power_dist(gen);                    // Get a random power value
            data_queue.push(std::make_pair(value, power));  // Add to the queue
        } // Lock is released here

        auto now = std::chrono::high_resolution_clock::now();                              // Calculate elapsed time
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(now - start); // Calculate elapsed time from now to start time
        if (elapsed > limit) { // If elapsed time exceeds the limit
            break;
        }
    }
    is_running = false; // Set is_running to false
}

// Pulls the number pairs from the queue, calculates the base raised to the power, and prints the result
void PowerCalculator::thread2_task() {
    while (is_running && !data_queue.empty()) {
        std::pair<int, int> number_pair;
        {
            std::lock_guard<std::mutex> guard(mtx); // Create an instance of std::lock_guard
            if (!data_queue.empty()) {              // If the queue is not empty
                number_pair = data_queue.front();   // Grab the integer value and power value
                data_queue.pop();
            } 
            else {
                continue;
            }
        } // Lock is released here

        // If the integer value and power value are not zero THEN
        if (number_pair.first != 0 && number_pair.second != 0) {
            auto result = std::pow(number_pair.first, number_pair.second); // Calculate the power value
            std::cout << number_pair.first << " to the power of " << number_pair.second << " is " << result << std::endl; // Write power results to the console
        }
    }
}

}
