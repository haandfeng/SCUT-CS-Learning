//
//  Greedy.cpp
//  newtest
//
//  Created by 谭演锋 on 2023/4/6.
//

#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

struct Goods //定义一个物品的信息结构体
{
    float weight;//物品的重量
    float value;// 物品的价值
    float P;// 权重=价值/重量
    float N; //物品装入背包的部分，如果全部装入则为1，装入一半为0.5
};
bool compare (Goods &a,Goods &b)//编写sort函数的比较函数
{
    return a.P>b.P; //采用升序排序
}
class Knapsack{
private:
 
    Goods *bag;
    int c;
    int n;

//    //自己编写的直接插入排序
//     void InsertSort(Goods goods[],int n){
//     int j;
//     for(int i=2;i<=n;++i)
//     if(goods[i].P>goods[i-1].P)
//     {
//     goods[0]=goods[i];
//     goods[i]=goods[i-1];
//     for(j=i-2;goods[0].P>goods[j].P;--j)
//         goods[j+1]=goods[j];
//         goods[j+1]=goods[0];
//     }
//
//     }
    
public:

    Knapsack(){
        int n;//物品的数量
        int v;//背包的容量
        cout<<"请输入背包的容量:"<<endl;
        cin>>v;
        this->c= v;
        cout<<"请输入物品的数量："<<endl;
        cin>>n;
        this->n = n;
        bag = new Goods [n];
        cout<<"请分别输入物品的重量和价值："<<endl;
        for(int i=0; i<n; i++)
        {   cin>>bag[i].weight>>bag[i].value;//输入重量和价值
            bag[i].P=bag[i].value/bag[i].weight;
            bag[i].N=0;//N置0
        }
        sort (bag,bag+n,compare);//调用C++内置的sort函数 ，当然也可以自己编写比较函数
        //InsertSort(bag,n);

    }
    void Greedy()//贪心算法
    {
        for(int i=0; i<n; i++)
        {
            if(c>bag[i].weight)//如果背包足够装下整个物品
            {
                c-=bag[i].weight;
                bag[i].N=1;//该物品全部装入记为1
            }
            else if(c>0){//如果背包不足以装下整个物品，就装入物品的一部分
                bag[i].N=c/(bag[i].weight*1.0);//计算物品装入背包的部分
                c=0;//背包容量置0
            }
        }
    }
    int get_n(){return n;}
    Goods* get_bag(){return bag;}
    int get_C(){return c;}
    void print_bag(){
        cout << "value \t Weight \t weight in bag\n";
        for (int i = 0; i < n; i++){
            cout << bag[i].value << " \t"
            << bag[i].weight << " \t"
            <<bag[i].N*bag[i].weight<<" \n";
        }
    }
};
int main()
{
    float total_value=0;
    float total_weight=0;
    Knapsack a;
    a.Greedy();
    Goods* goods =a.get_bag();
    cout<<"装入背包的物品信息"<<endl;
    for(int i=0;i<a.get_n();i++)
    {   if(goods[i].N==0.0)break;
        total_value+=(goods[i].value*goods[i].N);//装入背包的物品总价值
        total_weight+=(goods[i].weight*goods[i].N);//装入背包的物品总重量
        cout<<"weight: "<<goods[i].weight<<"  "<<"value: "<<goods[i].value<<"  the part of goods: "<<goods[i].N<<endl;//输出装入背包的物品信息
    }
//    cout<<"背包的容量为: "<<a.get_C()<<endl;//输出背包容量
    cout<<"装入背包中的物品的总重量为: "<<total_weight<<endl;//输出装入物品的总重量
    cout<<"装入背包中的物品的总价值为: "<<total_value<<endl;//输出装入物品的总价值
    return 0;
}
