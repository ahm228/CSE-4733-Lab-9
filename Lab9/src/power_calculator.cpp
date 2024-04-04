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





}

    // TODO (part 1):
    // 1. Create an instance of std::random_device
    // 2. Create an instance of std::mt19937
    // 3. Create a uniform integer distribution for the integer values (1 - 100).
    //    Use the std::uniform_int_distribution.
    // 4. Create a uniform integer distribution for the power value (1-10).
    //    Use the std::uniform_int_distribution.
    // 5. Set the time limit to 50 microseconds
    // 6. Capture the start time using std::chrono
    // 7. Create elapsed time variable using std::chrono::duration
    // 8. WHILE (true)
    //    a. Create an instance of std::lock_guard
    //    b. Get a random value from the uniform int distribution
    //    c. Get a random power value from the uniform int distribution
    //    d. Add random value and random power to the queue
    //    e. Calculate elapsed time from now to start time
    //    f. If elapsed time exceeds the limit then break out of while loop.
    // 7. Set is_running to false.


    // End TODO (part 1)

// Pulls the number pairs from the queue, calculates the base raised to the power, and prints the result
void PowerCalculator::thread2_task() {




}

}

    // TODO (part 2):
    // 1. While the is_running is true and the queue is not empty
    //    a. Create an instance of std::lock_guard
    //    b. IF the queue is not empty, THEN grab the integer value and power value from the queue
    //    c. IF the integer value and power value are not zero THEN
    //       1) calculate the power value
    //       2) Write power results to the console (e.g. Power of 2 raised to the 2 is 4)


    // End TODO (part 2)