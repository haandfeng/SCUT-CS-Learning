#include<iostream>
#include<fstream>
#include<string>
#include"cifa.hpp"
#include"yufa.hpp"
using namespace std;

int main()
{
    fstream cinfile,coutfile;
//    char filename[30];
//    cout<<"Please input the name of file:"<<endl;
//    cin>>filename;
    cinfile.open("code.txt");
    coutfile.open("BinaryType.txt",ios::out);
    if(!cinfile)
    {
        cerr<<"File open or create error!"<<endl;
        exit(1);
    }

    LexicAlanalysis(cinfile,coutfile);          //词法分析函数

    fstream infile,outfile;
    infile.open("BinaryType.txt");
    outfile.open("Type.txt",ios::out);
    if(!infile)
    {
        cerr<<"File open or create error!"<<endl;
        exit(1);
    }
    
    if(GrammaticAlanalysis(infile,outfile))             //语法分析函数
        cout<<"程序语法正确"<<endl;
    else
        cout<<"程序语法错误"<<endl;

    outfile.close();
    infile.close();
}
