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
    std::random_device rd; // 1. Create an instance of std::random_device
    std::mt19937 gen(rd()); // 2. Create an instance of std::mt19937
    std::uniform_int_distribution<> dist(1, 100); // 3. Create a uniform integer distribution for the integer values (1 - 100)
    std::uniform_int_distribution<> power_dist(1, 10); // 4. Create a uniform integer distribution for the power value (1-10)

    auto start = std::chrono::high_resolution_clock::now(); // 6. Capture the start time
    auto limit = std::chrono::microseconds(50); // 5. Set the time limit to 50 microseconds

    while (true) { // 8. WHILE (true)
        {
            std::lock_guard<std::mutex> guard(mtx); // a. Create an instance of std::lock_guard
            int value = dist(gen); // b. Get a random value
            int power = power_dist(gen); // c. Get a random power value
            data_queue.push(std::make_pair(value, power)); // d. Add to the queue
        } // Lock is released here

        auto now = std::chrono::high_resolution_clock::now(); // e. Calculate elapsed time
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(now - start); // e. Calculate elapsed time from now to start time
        if (elapsed > limit) { // f. If elapsed time exceeds the limit
            break;
        }
    }
    is_running = false; // 9. Set is_running to false
}

    // TODO (part 1):
    // 7. Create elapsed time variable using std::chrono::duration

// Pulls the number pairs from the queue, calculates the base raised to the power, and prints the result
void PowerCalculator::thread2_task() {
    while (is_running || !data_queue.empty()) { // 1. While is_running is true and the queue is not empty //FIXME
        std::pair<int, int> number_pair;
        {
            std::lock_guard<std::mutex> guard(mtx); // a. Create an instance of std::lock_guard
            if (!data_queue.empty()) { // b. If the queue is not empty
                number_pair = data_queue.front(); // Grab the integer value and power value
                data_queue.pop();
            } else {
                continue;
            }
        } // Lock is released here

        // c. If the integer value and power value are not zero THEN
        if (number_pair.first != 0 && number_pair.second != 0) {
            auto result = std::pow(number_pair.first, number_pair.second); // 1) Calculate the power value
            std::cout << number_pair.first << " to the power of " << number_pair.second << " is " << result << std::endl; // 2) Write power results to the console
        }
    }
}

}

    // TODO (part 2):
    // 1. While the is_running is true and the queue is not empty
