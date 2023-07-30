#ifndef CP_H
#define CP_H

// C
#ifndef _GLIBCXX_NO_ASSERT
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
 
#if __cplusplus >= 201103L
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cwchar>
#include <cwctype>
#endif
 
// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
 
#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#endif



typedef struct listele
{
 int instrno;
 struct listele *next;
}listele;

 listele* new_listele(int no)
 {
     listele* p = (listele*)malloc(sizeof(listele));
     p->instrno = no;
     p->next = NULL;
     return p;
 }


typedef struct instrlist
{
 listele *first,*last;
}instrlist;

 instrlist* new_instrlist(int instrno)
 {
     instrlist* p = (instrlist*)malloc(sizeof(instrlist));
     p->first = p->last = new_listele(instrno);
     return p;
 }

 instrlist* merge(instrlist *list1, instrlist *list2)
 {
     instrlist *p;
     if (list1 == NULL) p = list2;
     else
     {
         if (list2!=NULL)
         {
             if (list1->last == NULL)
             {
                 list1->first = list2->first;
                 list1->last =list2->last;
             }else list1->last->next = list2->first;
             list2->first = list2->last = NULL;
             free(list2);
         }
         p = list1;
     }
     return p;
 }

typedef struct node
{
  instrlist *truelist, *falselist, *nextlist;
 char addr[256];
 char lexeme[256];
 char oper[3];
 int instr;
}node;

 int filloperator(node *dst, char *src)
 {
     strcpy(dst->oper, src);
     return 0;
 }
 int filllexeme(node *dst, char *yytext)
 {
     strcpy(dst->lexeme, yytext);
     return 0;
 }
 int copyaddr(node *dst, char *src)
 {
     strcpy(dst->addr, src);
     return 0;
 }
 int new_temp(node *dst, int index)
 {
     sprintf(dst->addr, "t%d", index-100);
     return 0;
 }
 int copyaddr_fromnode(node *dst, node src)
 {
     strcpy(dst->addr, src.addr);
     return 0;
 }

typedef struct codelist
{
 int linecnt, capacity;
 int temp_index;
 char **code;
}codelist;

   codelist* newcodelist()
 {
     codelist* p = (codelist*)malloc(sizeof(codelist));
     p->linecnt = 100;
     p->capacity = 1024;
     p->temp_index = 100;
     p->code = (char**)malloc(sizeof(char*)*1024);
     return p;
 }

 int get_temp_index(codelist* dst)
 {
     return dst->temp_index++;
 }

 int nextinstr(codelist *dst) { return dst->linecnt; }
 
   int Gen(codelist *dst, char *str)
 {

     if (dst->linecnt >= dst->capacity)
     {
         dst->capacity += 1024;
         dst->code = (char**)realloc(dst->code, sizeof(char*)*dst->capacity);
         if (dst->code == NULL)
         {
             printf("short of memeory\n");
             return 0;
         }
     }
     dst->code[dst->linecnt] = (char*)malloc(strlen(str)+20);
     strcpy(dst->code[dst->linecnt], str);
     dst->linecnt++;
     return 0;
 }

 char tmp[1024];

 int gen_goto_blank(codelist *dst)
 {
     Gen(dst, tmp);
     return 0;
 }

 int gen_goto(codelist *dst, int instrno)
 {
     sprintf(tmp, "(j, -, -, %d)", instrno);
     Gen(dst, tmp);
     return 0;
 }

 int gen_if(codelist *dst, node left, char* op, node right)
 {
     sprintf(tmp, "(j%s, %s, %s,", op, left.addr, right.addr);
     Gen(dst, tmp);
     return 0;
 }

 int gen_1addr(codelist *dst, node left, char* op)
 {
     sprintf(tmp, "%s %s", left.addr, op);
     Gen(dst, tmp);
     return 0;
 }

 int gen_2addr(codelist *dst, node left, char* op, node right)
 {
     sprintf(tmp, "(%s, %s, -, %s)", op, right.addr, left.addr);
     Gen(dst, tmp);
     return 0;
 }

 int gen_3addr(codelist *dst, node left, node op1, char* op, node op2)
 {
     sprintf(tmp, "(%s, %s, %s, %s) ", op, op1.addr, op2.addr, left.addr);
     Gen(dst, tmp);
     return 0;
 }

 int gen_assignment(codelist *dst, node left, node right)
 {
     gen_2addr(dst, left, "-", right);
     return 0;
 }

 int backpatch(codelist *dst, instrlist *list, int instrno)
 {
     if (list!=NULL)
     {
         listele *p=list->first;
         char tmp[20];
     
         sprintf(tmp, " %d)", instrno);
         while (p!=NULL)
         {
             if (p->instrno < dst->linecnt)
                 strcat(dst->code[p->instrno], tmp);
             p=p->next;
         }
     }
     return 0;
 }

 int print(codelist* dst)
 {
     int i;
     
     for (i=100; i <= dst->linecnt; i++)
         printf("%5d:  %s\n", i, dst->code[i]);
     return 0;
 }

#endif
