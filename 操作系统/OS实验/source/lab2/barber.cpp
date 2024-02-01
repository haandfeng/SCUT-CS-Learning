#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<unistd.h>

const int SEAT_MAX = 6;
const int CUSTOMER_MAX = 20;
void down(sem_t &x){sem_wait(&x);}
void up(sem_t &x){sem_post(&x);}

sem_t barber_ready,cust_ready,mutex;
int free_seat;

void init(){
    sem_init(&barber_ready,0,1);
    sem_init(&cust_ready,0,0);
    sem_init(&mutex,0,1);
    free_seat = SEAT_MAX;
}

void* _barber(void* arg){
    while(true){
        down(cust_ready);
        down(mutex);
        free_seat++;
        up(mutex);
        sleep(5);
        printf("Barber has finished work from one customer!\n");
        up(barber_ready);
    }
}

void* _customer(void* arg){
    down(mutex);
    if(free_seat>0){
        free_seat--;
        printf("Customer whose id = %d has sit down! Free seat = %d\n",*((int*)arg),free_seat);
        up(mutex);
        up(cust_ready);
        down(barber_ready);
    }else{
        up(mutex);
        printf("Customer whose id = %d has gone away!\n",*((int*)arg));
    }
}

int main(){
    init();
    pthread_t barber_thread;
    pthread_t customer_threads[CUSTOMER_MAX];
    int customer_id[CUSTOMER_MAX];
    pthread_create(&barber_thread,NULL,_barber,NULL);
    for (int i = 0; i < CUSTOMER_MAX; i++)
    {
        //sleep(rand()%10);
        usleep((rand()%10)*500000);
        //sleep(1);
        customer_id[i] = i;
        pthread_create(&customer_threads[i],NULL,_customer,&customer_id[i]);
    }
    pthread_join(barber_thread,NULL);
    for (int i = 0; i < CUSTOMER_MAX; i++)
    {
        pthread_join(customer_threads[i],NULL);
    }
    
    
}