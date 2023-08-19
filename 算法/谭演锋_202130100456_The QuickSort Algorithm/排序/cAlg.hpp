//
//  cAlg.hpp
//  newtest
//
//  Created by 谭演锋 on 2023/3/23.
//

#ifndef cAlg_hpp
#define cAlg_hpp

#include <stdio.h>
using namespace  std;
template <class T>

class cAlg {
private:
    int N;
    T fD[20005];
    void swap(int n, int  m)
    {
        T temp = fD[n];
        fD[n]=fD[m];
        fD[m]= temp;
    }
    int partition(int l,int r,int pivot)
    {
        do {
            while(fD[++l]<pivot){}
            while((r!=0) && (fD[--r]>pivot)){}
            swap(l, r);

        }while(l<r);
        swap(l, r);
        return l;
    }
    void Merge(T * arr,int low,int mid ,int high)
    {
           int i=low,j=mid+1,k=0;
           T *temp=new T[high-low+1];
           if(!temp){
               return;
           }
           while(i<=mid&&j<=high){
               if(arr[i]<=arr[j])
                   temp[k++]=arr[i++];
               else
                   temp[k++]=arr[j++];
           }
           while(i<=mid)
               temp[k++]=arr[i++];
           while(j<=high)
               temp[k++]=arr[j++];
           for(i=low,k=0;i<=high;i++,k++)
               arr[i]=temp[k];
           delete []temp;
    }
public:
    cAlg(int _N, T *_fD){
        N =_N;
        _fD = fD;
    }
    ~cAlg(void){
        
    }
    void Initialization(){
        
    }
    
    
    void quickSort(int i,int j ){
        if (j<=i) return;
        int mid = (i+j)/2;
        swap(mid, j);
        int k = partition(i-1,j,fD[mid]);
        swap(k, j);
        quickSort(i,k-1);
        quickSort(k+1,j);
        
    }
    
    void stright_selectionSort(int n){
        for (int i = 0; i < n; i++)
            {
                int index = i;
                for (int j = i + 1; j < n; j++)
                {
                    if (fD[index] > fD[j]){
                        index = j;
                    }
                }
                swap(i,index);
            }
    }
    
    
    void insertSort(int n){
        for (int i=1; i<n; i++)
            {
                int j =i;
                for(;(j>0)&&(fD[j]>fD[j-1]);j--)
                {
                    swap(j, j-1);
                }
            }

            
    }
    
    
    void bubbleSort(int n){
        for (int i = 0; i < n - 1; i++)
            {
                for (int j = 0; j < n - i - 1; j++)
                {
                    if (fD[j] > fD[j + 1])
                        {
                            swap(j, j+1);
                        }
                }
            }

            
    }
    
    
 
    void MergeSort(T arr[],int low,int high){
        if(low<high){
            int mid=(low+high)/2;
            MergeSort(arr,low,mid);
            MergeSort(arr,mid+1,high);
            Merge(arr,low,mid,high);
        }
    }

    T *get_fD(){
        return fD;
    }
    
    
    void Set_fD(int _N, T * _fD){
        for(int i = 0; i<N;i++)
        {
            fD[i] =_fD[i];
        }

    }

    
};
#endif /* cAlg_hpp */
