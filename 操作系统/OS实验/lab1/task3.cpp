#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>

void print_message() {
    while (true) {
        auto now = std::chrono::system_clock::now();
        auto time_t_now = std::chrono::system_clock::to_time_t(now);

        // Get thread ID
        std::thread::id this_id = std::this_thread::get_id();

        // Print Thread ID and System Time
        std::cout << "[" << this_id << "] " << std::ctime(&time_t_now);

        // Sleep for 1 second
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    // Create a child thread
    std::thread child_thread(print_message);

    // Main thread also calls the print_message function
    print_message();

    // Join the child thread (wait for it to finish)
    child_thread.join();

    return 0;
}
