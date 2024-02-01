#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<pthread.h>
pthread_t thread1;
int shared_var = 0; 

void *child_thread(void* arg){
    while(true){
	    printf("%d ",--shared_var);
        fflush(stdout);
        sleep(1);
    }
}

int main(){
	int i = pthread_create(&thread1,NULL,child_thread,NULL);
	if(i == 0){
        while(true){
		        printf("%d ",++shared_var);
                fflush(stdout);
                sleep(2);
            }
		
	}
}
