#include<stdio.h>
#include<iostream>
#include<getopt.h>
#include<string>
#include<string.h>
#include<unistd.h>
#include <dirent.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
using namespace std;
#define MAX_PATH_LENGTH 65535
char root_path[MAX_PATH_LENGTH];
string pattern = "";
int modifiedTime = -1;

bool match(string pattern, string fileName){
    if(pattern.length() == 0 && fileName.length() == 0) return true;
    if(pattern.length() == 0 && fileName.length() > 0) return false;
    if(pattern[0] == '*' && pattern.length() > 1 && fileName.length() == 0)
        return false;
    if(pattern[0] == '?' || pattern[0] == fileName[0])
        return match(pattern.substr(1),fileName.substr(1));
    if(pattern[0] == '*')
        return match(pattern.substr(1),fileName) || match(pattern,fileName.substr(1));
    return false;
}

bool checkFile(string fileName,struct stat buf){
    if(pattern.length() == 0 || (pattern.length() != 0 && match(pattern,fileName))){
        if(modifiedTime!=-1 && (time(0) - buf.st_mtim.tv_sec)/(24*3600) > modifiedTime) return false;
        return true;
    }
    return false;

}

void find(string path){
    DIR *d;
    struct dirent *dir;
    d = opendir(path.c_str());
    if(d){
        if(strcmp(root_path,path.c_str())==0){
            printf("Target path: %s\n",root_path);
        }
        while((dir = readdir(d))!=NULL){
            string newpath;
            // memset(newpath,0,sizeof(newpath));
            newpath = path + ((path[path.length() - 1]=='/')?"":"/") + dir->d_name;
            if(dir->d_type == DT_DIR){
                if(strcmp(dir->d_name,"..") == 0 || strcmp(dir->d_name,".") == 0)
                    continue;
                find(newpath);
            }
            else{
                struct stat buf;
                if(stat(newpath.c_str(),&buf) == 0){
                    if(checkFile(dir->d_name,buf)){
                        struct tm* timeSet = gmtime(&(buf.st_mtim.tv_sec));
                        char timeString[50];
                        strftime(timeString ,50, "%Y-%m-%d %H:%M:%S::%Z", timeSet);
                        printf("%s  %s%s%s\n",timeString,path.c_str(),(path[path.length() - 1]=='/'?"":"/"),dir->d_name);
                    }
                }
                else{
                    fprintf(stderr,"Failed to get file information: %s.\nError no:%d\n",newpath.c_str(),errno);
                }
            }
            
        }
        closedir(d);
    }
    else{
        fprintf(stderr,"Failed to read directory: %s\nError no:%d\n",path.c_str(),errno);
    }

}

int main(int argc, char* argv[]){    

    static struct option opts[]={
        {"path",required_argument,NULL,'p'},
        {"name",required_argument,NULL,'n'},
        {"mtime",required_argument,NULL,'m'},
        {0,0,0,0}
    };
    int opt;

    while((opt = getopt_long(argc,argv,"p:n:m:",opts,NULL))!=-1){
        switch (opt)
        {
        case 'p':
            strcpy(root_path,optarg);
            break;
        case 'n':
            pattern = optarg;
            printf("You are looking for files whose name is/like: %s\n",pattern.c_str());
            break;
        case 'm':
            modifiedTime = atoi(optarg);
            printf("You are looking for files modified %d days before today.\n",modifiedTime);
            break;
        case '?':
            //printf("%c", optopt);
            exit(1);
        default:
            break;
        }
    }
    if(strlen(root_path) == 0){
        getcwd(root_path,MAX_PATH_LENGTH);
    }
    find(root_path);
}