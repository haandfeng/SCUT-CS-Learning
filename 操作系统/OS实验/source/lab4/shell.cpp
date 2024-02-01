#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<vector>
#include<string.h>
#include<string>
#include<sys/wait.h>
#include<errno.h>
#define MAX_STRING_LIST_COUNT 65535
#define HISTORY_MAX 10
#define MAX_PATH_LENGTH 1024
using namespace std;
vector<string> history;

char** split(char* str, const char* spliters){

    char** results = new char* [MAX_STRING_LIST_COUNT];
    int i = 0;
    char* p = strtok(str,spliters);
    while(p){
        results[i++] = p;
        p = strtok(NULL,spliters);
    }
    results[i] == NULL;
    return results;
}

int main(){
    char** paths = split(getenv("PATH"),":");
    char buf[1024] = {};
    char cwd_buf[MAX_PATH_LENGTH] = {};
    while(true)
    {
        memset(buf, 0, sizeof(buf));
        memset(cwd_buf,0,sizeof(cwd_buf));
        printf("%s> ",getcwd(cwd_buf,MAX_PATH_LENGTH));
        //printf("asdfasdf\n");
        
        while(scanf("%[^\n]%*c", buf) == 0){
            printf("%s> ",getcwd(cwd_buf,MAX_PATH_LENGTH));
            while(getchar() != '\n');
        }
        history.push_back(buf);
        if(history.size() > HISTORY_MAX)
            history.erase(history.begin());
        char** argv = split(buf," ");
        if(!strcmp(argv[0],"exit")) exit(0);
        else if(!strcmp(argv[0],"cd")){
            int result;
            char *cwd = getcwd(cwd_buf,MAX_PATH_LENGTH);
            if(!strcmp(argv[1],"..")){
                for (int i = strlen(cwd) - 1; i > 0; i--)
                {
                    if(cwd[i] == '/') {cwd[i+1] = '\0';break;}
                }
                if(cwd[0] == '\0'){cwd[0] = '/';cwd[1] = '\0';}
            }
            else if(!strcmp(argv[1],".")){ /*do nothing*/ }
            else if(argv[1][0] == '/'){ cwd = argv[1]; }
            else{
                cwd = strcat(strcat(cwd,"/"),argv[1]);
            }
            result = chdir(cwd);
            if(result!=0){
                //printf("return code: %d\n",result);
                //printf("error code:%d\n",errno);
                if(errno == ENOENT){
                    printf("No such directory: %s\n",argv[1]);
                }
                else if(errno == EPERM){
                    printf("Permission denied: %s\n",argv[1]);
                }
                else{
                    printf("Unknown error with errno=%d for directory: %s\n",errno,argv[1]);
                }
                delete[] argv;
            }
        }
        else if(!strcmp(argv[0],"history")){
            for (int i = 0; i < history.size(); i++)
            {
                printf("%d\t%s\n",i+1,history[i].c_str());
            }
        }
        else{
            int a = 0;
            if(fork() == 0){
                bool flag = false;
                string path_prefix;
                string wd = getcwd(cwd_buf,MAX_PATH_LENGTH);
                if(!access((wd + "/" + argv[0]).c_str(),F_OK)){
                    path_prefix = wd + "/";
                    flag = true;
                }else{
                    for (int i = 0; paths[i] != NULL; i++)
                    {
                        string i_path = paths[i];
                        path_prefix = i_path + "/";
                        if(!access((path_prefix+argv[0]).c_str(),F_OK)){flag = true; break;}
                    }
                }
                if(flag){
                    int result = execve((path_prefix+argv[0]).c_str(),argv,NULL);
                    if(result!=0){
                        if(errno == ENOENT){
                            printf("No such file: %s\n",argv[0]);
                        }
                        else if(errno == EPERM){
                            printf("Permission denied: %s\n",argv[0]);
                        }
                        else{
                            printf("Unknown error with errno=%d for file: %s\n",errno,argv[0]);
                        }
                    }

                }else{
                    printf("No such file: %s\n",argv[0]);
                }
                delete[] argv;
                exit(1);
            }else{
                wait(NULL);
                //printf("Child process has exited!\n");
            }
        }
    }

}