#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
pthread_t thread1;

char* get_time(){
	time_t tt = time(NULL);
    tm* t=localtime(&tt);
    char *buffer = (char*)calloc(80,sizeof(char));
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", t);
    return buffer;
}

void *child_thread(void* arg){
    while(true){
	    printf("%lu %s\n",pthread_self(),get_time());
        sleep(1);
    }
}

int main(){
	int i = pthread_create(&thread1,NULL,child_thread,NULL);
	if(i == 0){
        while(true){
		    printf("%lu %s\n",pthread_self(),get_time());
            sleep(1);
        }
	}
}
