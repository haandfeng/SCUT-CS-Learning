#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

char* get_time(){
	time_t tt = time(NULL);
    tm* t=localtime(&tt);
    char *buffer = (char*)calloc(80,sizeof(char));
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", t);
    return buffer;
}

int main(){
	while(true){
		printf("The child is talking at %s.\n",get_time());
		sleep(1);
	}
}
