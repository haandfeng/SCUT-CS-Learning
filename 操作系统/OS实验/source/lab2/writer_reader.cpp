#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<unistd.h>

#include<vector>
#include<algorithm>
#include<random>
#include<chrono>

const int WRITER_MAX = 10;
const int READER_MAX = 10;
const int IS_READER = 0;
const int IS_WRITER = 1;
const int WRITER_WORKING_TIME = 1;
const int READER_WORKING_TIME = 6;

void down(sem_t &x){sem_wait(&x);}
void up(sem_t &x){sem_post(&x);}

sem_t mutex,wmutex;
int reader_count;

void init(){
    sem_init(&mutex,0,1);
    sem_init(&wmutex,0,1);
    reader_count = 0;
}

void* _reader(void *arg){
    down(mutex);
    if(reader_count == 0) down(wmutex);
    reader_count++;
    up(mutex);
    sleep(READER_WORKING_TIME);
    printf("Reader whose id = %d has finished reading!\n",*((int*)arg));
    down(mutex);
    reader_count--;
    if(reader_count == 0) up(wmutex);
    up(mutex);
}

void* _writer(void *arg){
    down(wmutex);
    sleep(WRITER_WORKING_TIME);
    printf("Writer whose id = %d has finished writing!\n",*((int*)arg));
    up(wmutex);
}

std::vector<int> get_order(){
    std::vector<int> reader_order(READER_MAX,IS_READER);
    std::vector<int> writer_order(WRITER_MAX,IS_WRITER);
    writer_order.insert(writer_order.end(),reader_order.begin(),reader_order.end());
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(writer_order.begin(),writer_order.end(),std::default_random_engine(seed));
    return writer_order;
}

int main(){
    
    init();
    pthread_t reader_threads[READER_MAX];
    int reader_id[READER_MAX];
    pthread_t writer_threads[WRITER_MAX];
    int writer_id[WRITER_MAX];
    std::vector<int> order = get_order();
    printf("Reading time for a single reader is %d second(s).\n",READER_WORKING_TIME);
    printf("Writing time for a single writer is %d second(s).\n",WRITER_WORKING_TIME);
    printf("\n");

    for (int i = 0,j = 0; i + j < order.size();)
    {
        sleep(1);
        if(order.at(i+j) == IS_WRITER){
            writer_id[i]=i;
            pthread_create(&writer_threads[i],NULL,_writer,&writer_id[i]);
            i++;
        } else if(order.at(i+j) == IS_READER){
            reader_id[j]=j;
            pthread_create(&reader_threads[j],NULL,_reader,&reader_id[j]);
            j++;
        }
    }
    
    for (int i = 0; i < WRITER_MAX; i++)
    {
        pthread_join(writer_threads[i],NULL);
    }
    for (int i = 0; i < READER_MAX; i++)
    {
        pthread_join(reader_threads[i],NULL);
    }
    
    
    
}