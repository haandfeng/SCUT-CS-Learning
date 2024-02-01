#include <iostream>
#include <thread>
#include <semaphore.h>
#include <vector>
#include <chrono>

using namespace std;

const int MAX_READERS = 100;
const int MAX_WRITERS = 100;

int num_processes;
int read_count = 0;
int write_count = 0;
int priority;

sem_t mutex1, write_mutex;
sem_t reader_wait,writer_wait;
void down(sem_t &x) {
    sem_wait(&x);
}

void up(sem_t &x) {
    sem_post(&x);
}

void reader(int id, int start_time, int duration) {
    std::this_thread::sleep_for(std::chrono::seconds(start_time));
//    std::cout<<"reader " << id <<start_time<<" "<<duration<<endl;
//    if (priority == 1) {
//        down(writer_wait);
//    }
    //--------------
//    int reader_wait_value, mutex_value;
//    sem_getvalue(&reader_wait, &reader_wait_value);
//    sem_getvalue(&mutex1, &mutex_value);
//    cout << "reader " << id << " starts to read (reader_wait: " << reader_wait_value << ", mutex: " << mutex_value << ")" << endl;
//
    //---------------------
    down(reader_wait);
    down(mutex1);
    cout << "reader " << id << " waiting to read" << endl;
    read_count++;
    if (read_count == 1) {
        down(write_mutex);
    }
    up(mutex1);
    up(reader_wait);

    // Reading
    cout << "reader " << id << " starts to read" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(duration));
    cout << "reader " << id << " ends reading" << endl;

    down(mutex1);
    read_count--;
//    if (read_count == 0 && priority == 1) {
//        up(writer_wait);
//    }
    if (read_count == 0){
        up(write_mutex);
    }
    up(mutex1);
}

void writer(int id, int start_time, int duration) {
    std::this_thread::sleep_for(std::chrono::seconds(start_time));
    cout << "writer " << id << " waiting to write" << endl;
//    down(writer_wait);
    down(write_mutex);
    if (priority == 2) {
        down(reader_wait);
    }
    write_count++;

    cout << "writer " << id << " starts to write" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(duration));
    cout << "writer " << id << " ends writing" << endl;

    write_count--;
    if (priority == 2 && write_count == 0) {
        up(reader_wait);
    }
//    up(writer_wait);
    up(write_mutex);
}

int main() {
    cin >> priority >> num_processes;

    sem_init(&mutex1, 0, 1);
    sem_init(&write_mutex, 0, 1);
//    sem_init(&read_mutex, 0, 1);
    sem_init(&reader_wait, 0, 1);
    sem_init(&writer_wait, 0, 1);

    vector<thread> threads;
    for (int i = 0; i < num_processes; ++i) {
        int id, start_time, duration;
        char type =' ';
        std::cin >> id >> type >> start_time >> duration;
        
        if (type == 'R') {
            threads.emplace_back(reader, id, start_time, duration);
        } else {
            threads.emplace_back(writer, id, start_time, duration);
        }
    }
//
//    for (int i = 1; i <= num_readers; ++i) {
//        int reader_start, reader_duration;
//        cin >> reader_start >> reader_duration;
//        threads.emplace_back(reader, i, reader_start, reader_duration);
//    }
//
//    for (int i = 1; i <= num_writers; ++i) {
//        int writer_start, writer_duration;
//        cin >> writer_start >> writer_duration;
//        threads.emplace_back(writer, i, writer_start, writer_duration);
//    }

    for (auto &thread : threads) {
        thread.join();
    }

    sem_destroy(&mutex1);
    sem_destroy(&write_mutex);
//    sem_destroy(&read_mutex);
    sem_destroy(&reader_wait);
    sem_destroy(&writer_wait);

    return 0;
}
