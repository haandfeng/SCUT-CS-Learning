#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<stdlib.h>
char* get_time(){
	time_t tt = time(NULL);
    tm* t=localtime(&tt);
    char *buffer = (char*)calloc(80,sizeof(char));
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", t);
    return buffer;
}

int main(){
	if(fork() == 0){
		char *v[] = {  (char *) 0 };
		execv("./child.out",v);
	}
	else{
		while(true){
		    printf("The parent is talking at %s.\n",get_time());
		    sleep(1);
	    }
	}
	
}
