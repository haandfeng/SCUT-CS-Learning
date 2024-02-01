#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>
#include <unistd.h>


int main(){
    if(fork() == 0){
        char *v[] = {  (char *) 0 };
        execv("/root/os/lab1/child",v);
    }
    else{
        while(true){
            auto now = std::chrono::system_clock::now();
            auto time_t_now = std::chrono::system_clock::to_time_t(now);
            std::cout << "The parent is talking at " << std::ctime(&time_t_now);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    return 0;
}

