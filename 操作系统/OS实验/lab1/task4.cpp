#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

// Shared variable
int shared_var = 0;

// Mutex to synchronize access to shared_var
std::mutex mutex;

// Function for the child thread
void decrement() {
    while (true) {
        {
            std::lock_guard<std::mutex> lock(mutex);
            shared_var--;
            std::cout << "Child Thread: Decremented, shared_var = " << shared_var << std::endl;
        }

        // Sleep for 0.5 seconds
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main() {
    // Create a child thread
    std::thread childThread(decrement);

    // Main thread: increase shared_var
    while (true) {
        {
            std::lock_guard<std::mutex> lock(mutex);
            shared_var++;
            std::cout << "Main Thread: Incremented, shared_var = " << shared_var << std::endl;
        }

        // Sleep for 0.5 seconds
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    // The program will never reach this point in practice
    return 0;
}

