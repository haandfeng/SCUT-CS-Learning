#include <iostream>
#include <thread>
#include <semaphore.h>
#include <unistd.h>
#include <vector>
#include <chrono>
using namespace std;

const int MAX_CUSTOMERS = 100;
int total_chairs = 0;
sem_t barber_ready, customer_ready, mutex1;

int num_customers, num_barbers, num_chairs, haircut_time, customer_count = 0;
std::vector<int> customers;

void down(sem_t &x) { sem_wait(&x); }
void up(sem_t &x) { sem_post(&x); }


void barber() {
    while (true) {
        down(customer_ready);
        down(mutex1);
        num_chairs++;
        up(barber_ready);
        up(mutex1);
        // Haircut
        std::this_thread::sleep_for(std::chrono::seconds(haircut_time));
        cout << "customer " << customers[customer_count] << " finished haircut" << endl;
        customer_count++;
    }
}

void customer(int id, int arrival_time) {

    std::this_thread::sleep_for(std::chrono::seconds(arrival_time));
    int customer_id = id;
    down(mutex1);
    if (num_chairs > 0) {
        cout << "customer " << customer_id << ": there are " << total_chairs - num_chairs << " customers in front waiting for a haircut" << endl;
        customers.push_back(id);
        num_chairs--;
        up(customer_ready);
        up(mutex1);
        down(barber_ready);

    }
    else {
        cout << "customer " << customer_id << ": no more empty chairs, customer leaves" << endl;
        up(mutex1);
    }
}

int main() {
    cin >> num_customers >> num_barbers >> num_chairs >> haircut_time;
    total_chairs = num_chairs;

    std::vector<std::pair<int, int>> customer_data;
    for (int i = 0; i < num_customers; ++i) {
        int id, arrival_time;
        cin >> id >> arrival_time;
        customer_data.emplace_back(id, arrival_time);
    }

    sem_init(&barber_ready, 0, num_barbers);
    sem_init(&customer_ready, 0, 0);
    sem_init(&mutex1, 0, 1);

    std::thread barber_thread(barber);

    std::vector<std::thread> customer_threads;
    for (const auto &data : customer_data) {
        customer_threads.emplace_back([data]() {
            customer(data.first, data.second);
        });
    }


    for (auto &thread : customer_threads) {
        thread.join();
    }
    
    barber_thread.join();
    sem_destroy(&barber_ready);
    sem_destroy(&customer_ready);
    sem_destroy(&mutex1);
    return 0;
}
