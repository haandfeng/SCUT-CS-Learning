//
//  cifa.cpp
//  mannual
//
//  Created by 谭演锋 on 2023/6/13.
//

#include "cifa.hpp"
#include <string>
#include <fstream>
using namespace std;
#define N 100

string Reservedword[] = { "program","{","}","var","int","float","while","if","then","else","do" };
string Identifier[N];
void change(char* str)             //将line中的大写字母转换成小写便于分析
{
    for (int i = 0; i < strlen(str); i++)
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
}
int isReservedword(string str)   ///判断保留字，并返回编号，不是保留字则返回-1
{
    int i = 0;
    for (i = 0; i < 11; i++)
    {
        if (!str.compare(Reservedword[i]))
            return i + 1;
    }
    return -1;
}
int isIdentifier(string str, int count)      ///判断已知标识符，并返回编号，不是保留字则返回-1
{
    int i = 0;
    for (i = 0; i < count; i++)
    {
        if (!str.compare(Identifier[i]))
            return i + 1;
    }
    return -1;
}
void addIdentifier(string str, int count)    ///添加标识符
{
    Identifier[count] = str;
}
void LexicAlanalysis(fstream& infile, fstream& outfile)
{
    char line[180];
    char str[180];
    int count = 0, flag = 1;          ///count记录标识符的个数 flag判断是不是注释
    while (infile >> line)              //读取一个字符串
    {
        int i, j, k;
        change(line);
        for (i = 0; i < strlen(line);)
        {
            if (flag == 0 && line[i] != '*') { i++; continue; }
            if (line[i] >= 'a' && line[i] <= 'z')
            {
                j = i; k = 0;
                while ((line[j] >= '0' && line[j] <= '9') || (line[j] >= 'a' && line[j] <= 'z'))
                    str[k++] = line[j++];
                str[k] = NULL;
                if (k > 0)
                {
                    if (isReservedword(str) >= 0)      ///保留字
                    {
                        outfile << "(3," << isReservedword(str) << ")" << str << endl;
                        i += strlen(str);
                        continue;
                    }
                    if (isIdentifier(str, count) >= 0)    //标识符
                    {
                        outfile << "(4," << isIdentifier(str, count) << ")" << str << endl;
                        i += strlen(str);
                        continue;
                    }
                    else
                    {
                        addIdentifier(str, count);
                        count++;
                        outfile << "(4," << count << ")" << str << endl;
                        i += strlen(str);
                        continue;
                    }
                }
            }

            j = i; k = 0;                                 // 数字
            while ((line[j] >= '0' && line[j] <= '9') || line[j] == '.')
                str[k++] = line[j++];
            str[k] = NULL;
            if (str[0] == '.' && str[1] == NULL)
            {
                outfile << "(8,.)" << endl; i++; continue;
            }
            else if (k > 0)
            {
                outfile << "(5," << str << ")" << endl;
                i += strlen(str);
                continue;
            }

            if (line[i] == ';')
            {
                outfile << "(6,;)" << endl; i++; continue;
            }
            if (line[i] == ',')
            {
                outfile << "(7,,)" << endl; i++; continue;
            }
            if (line[i] == ':')
            {
                
                    outfile << "(9,:)" << endl; i++; continue;
                
            }
            if (line[i] == '+')
            {
                outfile << "(11,+)" << endl; i++; continue;
            }
            if (line[i] == '-')
            {
                outfile << "(12,-)" << endl; i++; continue;
            }
            if (line[i] == '*')
            {
                if (line[i + 1] != NULL && line[i + 1] == '/' && flag == 0)  //处理'*/
                {
                    flag = 1; i += 2; continue;
                }
                else if (flag == 1)
                {
                    outfile << "(13,*)" << endl; i++; continue;
                }
                else
                {
                    i++; continue;
                }
            }
            if (line[i] == '/')
            {
                if (line[i + 1] != NULL && line[i + 1] == '/')
                {
                    infile.getline(line, 180); break;
                }
                else if (line[i + 1] != NULL && line[i + 1] == '*')
                {
                    flag = 0; i += 2; continue;
                }
                else
                {
                    outfile << "(14,/)" << endl; i++; continue;
                }
            }
            if (line[i] == '<')
            {
                if (line[i + 1] != NULL && line[i + 1] == '=')
                {
                    outfile << "(16,<=)" << endl; i += 2; continue;
                }
                else if (line[i + 1] != NULL && line[i + 1] == '>')
                {
                    outfile << "(17,<>)" << endl; i += 2; continue;
                }
                else
                {
                    outfile << "(15,<)" << endl; i++; continue;
                }
            }
            if (line[i] == '>')
            {
                if (line[i + 1] != NULL && line[i + 1] == '=')
                {
                    outfile << "(19,>=)" << endl; i += 2; continue;
                }
                else
                {
                    outfile << "(18,>)" << endl; i++; continue;
                }
            }
            if (line[i] == '=')
            {
                outfile << "(10,=)" << endl; i++; continue;
            }
            if (line[i] == '&')
            {
                if (line[i + 1] != NULL && line[i + 1] == '&')
                {
                    outfile << "(21,&&)" << endl; i += 2; continue;
                }
            }
            if (line[i] == '|')
            {
                if (line[i + 1] != NULL && line[i + 1] == '|')
                {
                    outfile << "(22,||)" << endl; i += 2; continue;
                }
            }
            if (line[i] == '!')
            {
                outfile << "(23,!)" << endl; i++; continue;
            }
            if (line[i] == '(')
            {
                outfile << "(24,()" << endl; i++; continue;
            }
            if (line[i] == ')')
            {
                outfile << "(25,))" << endl; i++; continue;
            }
            if (line[i] == '{')
            {
                outfile << "(3,2)" << "{" << endl; i++; continue;
                continue;
            }
            if (line[i] == '}')
            {
                outfile << "(3,3)" << "}" << endl; i++; continue;
                continue;
            }
        
            outfile << "∑«∑®◊÷∑˚" << endl;
            i++;
            continue;
        }
    }
}
