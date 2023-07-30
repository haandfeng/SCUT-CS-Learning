//
//  yufa.cpp
//  mannual
//
//  Created by 谭演锋 on 2023/6/13.
//

#include "yufa.hpp"


using namespace std;
#define MAX 100
#define Identifier_MAX 100

string reservedword[] = { "program","begin","end","var","integer","real","while","if","then","else","do" };
extern string Identifier[Identifier_MAX];
typedef struct siyuanshi
{
    int N;
    int Class;
    int opt1_class;
    double opt1_index;
    int opt2_class;
    double opt2_index;
    int res_class;
    int res_index;
}siyuanshi;
typedef struct QUEUE
{
    int M;
    siyuanshi* sys, * p;
}QUEUE;
typedef struct BinaryType
{
    int Class;
    double index;
}BinaryType;
typedef struct Statement
{
    int m;
    BinaryType* state, * p;
}Statement;
typedef struct R         //关系表达式的TC与FC
{
    int TC;
    int FC;
}R;

siyuanshi noIF = { 0,26,0,0,0,0,5,0 };

QUEUE S;                 //保存四元式
Statement optr, opnd;             //保存某条语句
int t_num = 1;             //中间变量t的数目
int S_num = 1;          //四元式的数量

R r;
int R_t, flag;
int Chaim;
void InitQUEUE()        //初始化队列
{
    S.M = MAX;
    S.sys = (siyuanshi*)malloc(sizeof(siyuanshi) * MAX);
    S.p = S.sys;
}
void InitStatement(Statement* s)
{
    if (s->state)
        free(s->state);
    s->m = MAX;
    s->state = (BinaryType*)malloc(sizeof(BinaryType) * MAX);
    s->p = s->state;
}
void push(Statement* s, int num, double index = 0)
{
    s->p->Class = num;
    s->p->index = index;
    (s->p)++;
}
void push(siyuanshi e)
{
    S.p->Class = e.Class;
    S.p->N = e.N;
    S.p->opt1_class = e.opt1_class;
    S.p->opt1_index = e.opt1_index;
    S.p->opt2_class = e.opt2_class;
    S.p->opt2_index = e.opt2_index;
    S.p->res_class = e.res_class;
    S.p->res_index = e.res_index;
    (S.p)++;
}
void pop(Statement* s, int* num = 0, double *index = 0)
{
    (s->p)--;
    (*num) = s->p->Class;
    if ((*num) <= 5)
        (*index) = s->p->index;
    s->p->Class = 0;
    s->p->index = 0;
}
void pop(siyuanshi& e)       //队列输出
{
    e.Class = S.p->Class;
    e.N = S.p->N;
    e.opt1_class = S.p->opt1_class;
    e.opt1_index = S.p->opt1_index;
    e.opt2_class = S.p->opt2_class;
    e.opt2_index = S.p->opt2_index;
    e.res_class = S.p->res_class;
    e.res_index = S.p->res_index;
    (S.p)++;
}
int GetTop(Statement s)
{
    return (s.p - 1)->Class;
}
void print(fstream& outfile, int num, double index = 0)
{
    switch (num)
    {
    case 0:outfile << " "; break;
    case 1:outfile << "T" << index; break;
    case 3:outfile << reservedword[int(index)- 1]; break;
    case 4:outfile << Identifier[int(index) - 1]; break;
    case 5: {outfile << index; break; }
    case 10:outfile << "="; break;
    case 11:outfile << "+"; break;
    case 12:outfile << "-"; break;
    case 13:outfile << "*"; break;
    case 14:outfile << "/"; break;
    case 15:outfile << "j<"; break;
    case 16:outfile << "j<="; break;
    case 17:outfile << "j<>"; break;
    case 18:outfile << "j>"; break;
    case 19:outfile << "j>="; break;
    case 20:outfile << "j="; break;
    case 26:outfile << "j"; break;
    }
}
void Print(fstream& outfile)
{
    S.p = S.sys;
    for (int i = 0; i < S_num - 1; i++)
    {
        siyuanshi e = { 0 };
        pop(e);
        outfile << e.N << ". ("; print(outfile, e.Class); outfile << ", "; print(outfile, e.opt1_class, e.opt1_index); outfile << ", ";
        print(outfile, e.opt2_class, e.opt2_index); outfile << ", "; print(outfile, e.res_class, e.res_index); outfile << ")" << endl;
    }
    outfile << S_num << ". (ret, , ,0)" << endl;
}
char Precede(int a, int b)
{
    if (a == 11 && (b == 11 || b == 12 || b == 25 || b == 0))  return '>';
    if (a == 12 && (b == 11 || b == 12 || b == 25 || b == 0))  return '>';
    if (a == 13 && (b == 11 || b == 12 || b == 13 || b == 14 || b == 25 || b == 0))  return '>';
    if (a == 14 && (b == 11 || b == 12 || b == 13 || b == 14 || b == 25 || b == 0))  return '>';
    if (a == 24 && b == 25)  return '=';
    if (a == 25)   return '>';
    if (a == 0 && b == 0)  return '=';
    return '<';
}
void BackPatch(int p, int t)          ///回填
{
    int q = p;
    while (q)
    {
        int q1 = S.sys[q - 1].res_index;
        S.sys[q - 1].res_index = t;
        q = q1;
    }
}
int Merge(int p1, int p2)        //拉链
{
    int p;
    if (!p1)
        return p2;
    else
    {
        p = p2;
        while (S.sys[p - 1].res_index)
            p = S.sys[p - 1].res_index;
        S.sys[p - 1].res_index = p1;
        return p2;
    }
}
int getClass(fstream& infile, double& index)              //读取二元式
{
    char line[180];
    char Class[10];
    int i = 1, j = 0, num = 0;
    infile >> line;
    while (1)
    {
        if (line[i] >= '0' && line[i] <= '9')
            Class[j++] = line[i++];
        else
            break;
    }
    Class[j] = NULL;
    num = atoi(Class);

    if (num == 3 || num == 4 || num == 5)
    {
        int flag = 0;
        i++;
        j = 0;
        while (1)
        {
            if ((line[i] >= '0' && line[i] <= '9') || line[i] == '.')
            {
                if (line[i] == '.') flag = 1;
                Class[j++] = line[i++];
            }
            else
                break;
        }
        Class[j] = NULL;
        
        if (flag == 1) {
            index = atof(Class);
            
        }
        
        else {
            index = atoi(Class);
            
        }
    }
    else
        index = 0;
    //cout << num <<" "<< index<<"! ";
    return  num;
}
int GrammaticAlanalysis(fstream& infile, fstream& outfile)            //语法分析函数
{
    int num;
    double index;
    InitQUEUE();
    num = getClass(infile, index);
    if (!isBlock(infile, num, index, outfile))
        return 0;
    noIF.N = S_num;
    Print(outfile);
    return 1;
}
int isBlock(fstream& infile, int& num, double& index, fstream& outfile)      //判断是不是分程序
{
    if (!isVarList(infile, num, index))
        return 0;

    if (!isStatementList(infile, num, index, outfile))
        return 0;
    
    return 1;
}

int isVarList(fstream& infile, int& num, double& index)         //判断变量说明表
{
    if (!isForm(infile, num, index))
        return 0;
    num = getClass(infile, index);

    if (!isVariableList(infile, num, index))
        return 0;
    
    if (num == 6)
    {
        num = getClass(infile, index);
        isVarList(infile, num, index);
    }
    return 1;
}
int isForm(fstream& infile, int& num, double& index)            //判断类型
{
    if (num != 3 || (index != 5 && index != 6))
        return 0;
    return 1;
}
int isVariableList(fstream& infile, int& num, double& index)     //判断变量表
{
    if (num != 4)
        return 0;
    num = getClass(infile, index);
    if (num == 7)
    {
        num = getClass(infile, index);
        isVariableList(infile, num, index);
    }
    return 1;
}

int isStatementList(fstream& infile, int& num, double& index, fstream& outfile)   //判断语句表
{
    Chaim = 0;
    if (!isState(infile, num, index, outfile))
        return 0;
    if (num == 6)
    {
        Chaim = 0;
        num = getClass(infile, index);
        if (num == 0||(num==3&&index==3)) return 1;
        if (!isStatementList(infile, num, index, outfile))
            return 0;
    }
    return 1;
}
int isState(fstream& infile, int& num, double& index, fstream& outfile)       //判断语句
{
    if ((!isStatement(infile, num, index, outfile))
        && (!isIfState(infile, num, index, outfile))
        && (!isWhileState(infile, num, index, outfile))
        && (!isCompoundState(infile, num, index, outfile)))
        return 0;
    return 1;
}
int isStatement(fstream& infile, int& num, double& index, fstream& outfile)                //判断是不是赋值语句
{
    InitStatement(&optr);
    InitStatement(&opnd);
    push(&optr, 0);
    siyuanshi e = { 0 };
    if (num != 4)
        return 0;
    e.res_class = num;
    e.res_index = index;
    num = getClass(infile, index);
    if (num != 10)
        return 0;
    e.Class = num;
    num = getClass(infile, index);
    if (!isExpression(infile, num, index))
        return 0;
    pop(&opnd, &e.opt1_class, &e.opt1_index);
    e.N = S_num++;
    push(e);
    return 1;
}
int isIfState(fstream& infile, int& num, double& index, fstream& outfile)     //判断条件语句
{
    int chaim;
    if (num != 3 || index != 8)        //IF
        return 0;
    InitStatement(&optr);
    InitStatement(&opnd);
    push(&optr, 0);
    r.TC = r.FC = 0;
    flag = 0;

    num = getClass(infile, index);
    if (!isRelationalExpression(infile, num, index, outfile))
        return 0;
    BackPatch(r.TC, S_num);    //回填IF TC
    chaim = S_num - 1;
    if (Chaim != 0)
        Chaim = Merge(Chaim, S_num - 1);
    else
        Chaim = chaim;
    num = getClass(infile, index);
    if (!isState(infile, num, index, outfile))
        return 0;
    if (num == 3 && index == 10)      //ELSE
    {

        //       noIF.res_index=Merge(Chaim,S_ num-1);
        noIF.res_index = 0;
        noIF.N = S_num++;
        Chaim = chaim = Merge(Chaim, S_num - 1);
        push(noIF);
        BackPatch(r.FC, S_num);    //回填IF FC
        num = getClass(infile, index);
        if (!isState(infile, num, index, outfile))
            return 0;
        BackPatch(chaim, S_num);
    }
    else if (num == 6)
        BackPatch(chaim, S_num);
    return 1;
}
int isWhileState(fstream& infile, int& num, double& index, fstream& outfile)     //判断WHILE语句
{
    if (num != 3 || index != 7)
        return 0;
    int chaim;
    r.TC = r.FC = 0;
    int _while = S_num;
    flag = 0;
    num = getClass(infile, index);
    if (!isRelationalExpression(infile, num, index, outfile))
        return 0;

    //   Chaim=chaim=Merge(Chaim,S num-1);
    chaim = S_num - 1;
    
    BackPatch(r.TC, S_num);
    num = getClass(infile, index);
    if (!isState(infile, num, index, outfile))
        return 0;
    noIF.N = S_num++;
    noIF.res_index = _while;
    push(noIF);
    if (Chaim != 0)
    {
        //    Chaim=Merge(Chaim,S_num-1);
        BackPatch(Chaim, _while);
    }
    BackPatch(chaim, S_num);
    return 1;
}
int isCompoundState(fstream& infile, int& num, double& index, fstream& outfile)     //判断复合语句
{
    if (num != 3 || index != 2)
        return 0;
    num = getClass(infile, index);
    if (!isStatementList(infile, num, index, outfile))
        return 0;
    if (num != 3 || index != 3)
        return 0;
    num = getClass(infile, index);
    return 1;
}
int isExpression(fstream& infile, int& num, double& index)             ///判断是不是算术表达式
{
    siyuanshi e = { 0 };
    if (!isItem(infile, num, index))
        return 0;
    if (num != 6 && (!(num >= 15 && num <= 23)) && num != 3&&num!=25)
    {
        if (GetTop(optr) != 0)
            switch (Precede(GetTop(optr), num))
            {
            case '<':push(&optr, num); break;
            case '=':pop(&optr); break;
            case '>':
                pop(&optr, &e.Class);
                pop(&opnd, &e.opt2_class, &e.opt2_index);
                pop(&opnd, &e.opt1_class, &e.opt1_index);
                e.res_class = 1; e.res_index = t_num++;
                e.N = S_num++;
                push(&opnd, e.res_class, e.res_index);
                push(e);
                push(&optr, num);
                break;
            }
        else push(&optr, num);
        num = getClass(infile, index);
        if ((!isExpression(infile, num, index)))
            return 0;
    }
    else
        while (GetTop(optr) != 0)
        {
            pop(&optr, &e.Class);
            pop(&opnd, &e.opt2_class, &e.opt2_index);
            pop(&opnd, &e.opt1_class, &e.opt1_index);
            e.res_class = 1; e.res_index = t_num++;
            e.N = S_num++;
            push(&opnd, e.res_class, e.res_index);
            push(e);
        }
    //if (num == 25) cout << "yes";
    return 1;
}

int isItem(fstream& infile, int& num, double& index)                     //判断是不是项
{
    siyuanshi e = { 0 };
    if (!isFactor(infile, num, index))
        return 0;
    if (num == 4 || num == 5)
        push(&opnd, num, index);
    num = getClass(infile, index);
    if (num == 11 || num == 12 || num == 6 || num == 25 || (num >= 15 && num <= 23) || num == 3)
    {
        //if (num == 25) cout << "yes";
        if (num == 11 || num == 12)
        {
            if (GetTop(optr) != 0)
                switch (Precede(GetTop(optr), num))
                {
                case '<':push(&optr, num); break;
                case '=':pop(&optr); break;
                case '>':
                    pop(&optr, &e.Class);
                    pop(&opnd, &e.opt2_class, &e.opt2_index);
                    pop(&opnd, &e.opt1_class, &e.opt1_index);
                    e.res_class = 1; e.res_index = t_num++;
                    e.N = S_num++;
                    push(&opnd, e.res_class, e.res_index);
                    push(e);
                    break;
                }
        }
        return 1;
    }
    if (num != 13 && num != 14)
        return 0;
    if (GetTop(optr) != 0)
        switch (Precede(GetTop(optr), num))
        {
        case '<':push(&optr, num); break;
        case '=':pop(&optr); break;
        case '>':
            pop(&optr, &e.Class);
            pop(&opnd, &e.opt2_class, &e.opt2_index);
            pop(&opnd, &e.opt1_class, &e.opt1_index);
            e.res_class = 1; e.res_index = t_num++;
            e.N = S_num++;
            push(&opnd, e.res_class, e.res_index);
            push(e);
            break;
        }
    num = getClass(infile, index);
    if (!isItem(infile, num, index))
        return 0;
    return 1;
}
int isFactor(fstream& infile, int& num, double& index)                 //判断是不是因式
{
    siyuanshi e = { 0 };
    if (num == 24)
    {
        if (GetTop(optr) != 0)
            switch (Precede(GetTop(optr), num))
            {
            case '<':push(&optr, num); break;
            case '=':pop(&optr); break;
            case '>':
                pop(&optr, &e.Class);
                pop(&opnd, &e.opt2_class, &e.opt2_index);
                pop(&opnd, &e.opt1_class, &e.opt1_index);
                e.res_class = 1; e.res_index = t_num++;
                e.N = S_num++;
                push(&opnd, e.res_class, e.res_index);
                push(e);
                break;
            }
        else push(&optr, num);
        num = getClass(infile, index);
        if (!isExpression(1, infile, num, index))
            return 0;
    }
    if ((num != 4 && num != 5 && num != 24 && num != 25))
        return 0;
    return 1;
}
int isRelationalExpression(fstream& infile, int& num, double& index, fstream& outfile)  ///判断关系表达式
{
    siyuanshi e;

    if (num != 24)
        return 0;
    num = getClass(infile, index);
    if (num == 23)
        num = getClass(infile, index);
    //cout<<"yes1";
    if (!isExpression(infile, num, index))
    {
        //cout << "no";
        return 0;
    }
    //cout<<"yes1";
    pop(&opnd, &e.opt1_class, &e.opt1_index);

    if (!isEelationCharacter(infile, num, index))
        return 0;
    e.Class = num;

    InitStatement(&optr);
    InitStatement(&opnd);
    push(&optr, 0);
    num = getClass(infile, index);
    if (!isExpression(infile, num, index))
        return 0;


    pop(&opnd, &e.opt2_class, &e.opt2_index);
    if (!flag)
    {
        r.TC = S_num;
        e.N = S_num++;
        e.res_class = 5;
        e.res_index = 0;
        r.FC = S_num;
        noIF.N = S_num++;
    }
    else if (flag == 21)       //&&
    {
        BackPatch(r.TC, S_num);
        e.res_class = 5;
        e.res_index = 0;
        r.TC = S_num;
        e.N = S_num++;
        noIF.res_index = r.FC;
        r.FC = S_num;
        noIF.N = S_num++;
    }
    else if (flag == 22)      //||
    {
        BackPatch(r.FC, S_num);
        e.res_class = 5;
        e.res_index = r.TC;
        r.TC = S_num;
        e.N = S_num++;
        //        noIF.res_index=r.FC;
        r.FC = S_num;
        noIF.res_index = 0;
        noIF.N = S_num++;
    }

    push(e);
    push(noIF);

    if (num == 21 || num == 22)
    {
        flag = num;
        num = getClass(infile, index);
        if (!isRelationalExpression(infile, num, index, outfile))
            return 0;
    }
    if (num == 25)
    {
        //cout << "yes2";
        return 1;
    }
    return 1;
}
int isEelationCharacter(fstream& infile, int& num, double& index)  ///判断关系符
{
    if (!(num >= 15 && num <= 20))
        return 0;
    return 1;
}
int isExpression(int flag, fstream& infile, int& num, double& index)             //判断是不是算术表达式
{
    siyuanshi e = { 0 };
    if (!isItem(infile, num, index))
        return 0;
    if (num != 25)
    {
        num = getClass(infile, index);
        if (!isExpression(1, infile, num, index))
            return 0;
    }
    else pop(&optr, &e.Class);
    return 1;
}
