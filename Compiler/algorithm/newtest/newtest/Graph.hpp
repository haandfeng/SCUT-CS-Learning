////
////  Graph.hpp
////  newtest
////
////  Created by 谭演锋 on 2023/3/30.
////
//
//#ifndef Graph_hpp
//#define Graph_hpp
//
//#include <stdio.h>
//#include <list>
//
//class Edge{
//    int vert,wt;
//public:
//    Edge(){vert =-1; wt =-1;}
//    Edge(int v, int w){vert =v; wt =w;}
//    int vertex(){return vert;}
//    int weight(){return wt;}
//};
//
//
//template <typename T>
//class Graph{
//public:
//    Graph( int numVert, std::list<Edge>** v){
//        Init(numVert);
//        vertex=v;
// 
//    }
//    ~Graph(){
//       delete []mark;
//        for(int i =0;i<numVertex;i++){delete [] vertex[i];}
//        delete []vertex;
//   }
//
//    
//    void Init(int n){
//        numVertex =n;
//        numEdge =0;
//        mark =new int [n];
//        for(int i =0;i<numVertex;i++){mark[i]=0;}
//        vertex =(std::list<Edge>**) new std::list<Edge> * [numVertex];
//        for(int i =0;i<numVertex;i++){
//            vertex[i] = new std::list<Edge>();
//        }
//        
//    }
//    int n(){return numVertex;}
//    int e(){return numEdge;}
//    int first(int v)
//    {
//        if(vertex[v]->size()==0) return numVertex;
////        vertex[v]->begin();
//        Edge it = vertex[v][0];
//        return it.vertex();
//    }
//    int next(int v, int w)
//    {
//        Edge it;
//    }
//
//private:
//    std:: list<Edge> ** vertex;
//    int numVertex, numEdge;
//    int *mark;
//    
//};
//
//#endif /* Graph_hpp */
//
//
//
//
//
////template<typename T>
////class node{
////public:
////node(T a, node *next1 =NULL){
////        elem =a;
////        next_node =next1;
////}
////node* next(){
////    return next_node;
////}
////private:
////    node *next_node =NULL;
////    T elem;
////
////};
