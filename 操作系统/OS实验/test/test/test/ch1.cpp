#include<unistd.h>
#include<stdio.h>
#include <sys/wait.h>  // 添加此行


int main()
{
    int i, pid, status;
    for(int i = 1; i <= 4; i ++)
    {
        if((pid = fork())== 0)
            printf("In child %d. \n",i);
        else
        {
            wait(&status);
        }
    }
    
}
