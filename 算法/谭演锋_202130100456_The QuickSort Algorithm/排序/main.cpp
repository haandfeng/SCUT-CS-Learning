
  main.cpp
  newtest
  五个时间 输出到文件去
  Created by 谭演锋 on 2023/3/23.


#include <iostream>
#include <cstdlib>
#include "cAlg.hpp"
#include <time.h>

using namespace std;
int main(int argc, const char * argv[]) {
    int iNum =2005,iS;
    float fRandom[2005];
    double t1,t2,t3,t4,t5;
    cAlg <float> MycAlg(iNum,fRandom);
//    cout<<tt1<<endl;
    for(int i=1;i<=10;i++)
    {
        iS = i*200;
        int n = iS;
        for(int j =1;j<= iS;j++)
        {
            fRandom[j]= rand()%iS;
//            cout<<fRandom[j]<<" ";
        }
        cout<<endl;

        clock_t tt1;
        clock_t tt2;

        MycAlg.Set_fD(iS, fRandom);
        tt1 =clock();
        MycAlg.quickSort(0,iS-1);
        tt2 =clock();
        t1 = tt2- tt1;

        MycAlg.Set_fD(iS, fRandom);
        tt1 =clock();
        MycAlg.stright_selectionSort(iS);
        tt2 =clock();
        t2 = tt2- tt1;

        MycAlg.Set_fD(iS, fRandom);
        tt1 =clock();
        MycAlg.insertSort(iS);
        tt2 =clock();
        t3 = tt2- tt1;

        MycAlg.Set_fD(iS, fRandom);
        tt1 =clock();
        MycAlg.bubbleSort(iS);
        tt2 =clock();
        t4 = tt2- tt1;


        MycAlg.Set_fD(iS, fRandom);
        tt1 =clock();
        MycAlg.MergeSort(fRandom,0,iS-1);
        tt2 =clock();
        t5 = tt2- tt1;

        cout<<iS<<endl;
        cout<<t1<<" "<<t2<<" "<<t3<<" "<<t4<<" "<<t5<<" "<<endl;



    }
//    cout<<tt2<<endl;
//    cout<<tt2-tt1<<endl;
}
