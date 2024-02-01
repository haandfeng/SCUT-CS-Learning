#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>

int main() {
    while (true) {
        auto now = std::chrono::system_clock::now();
        auto time_t_now = std::chrono::system_clock::to_time_t(now);
        std::cout << "The child is talking at " << std::ctime(&time_t_now);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
