////
////  MST_Alg.cpp
////  newtest
////
////  Created by 谭演锋 on 2023/3/30.
////
//
////#include "MST_Alg.hpp"
//#include <iostream>
//#include <cstdlib>
//#include <time.h>
//
//// A C++ program for Prim's Minimum
//// Spanning Tree (MST) algorithm. The program is
//// for adjacency matrix representation of the graph
// 
//using namespace std;
// 
//// Number of vertices in the graph
//#define V 6
// 
//// A utility function to find the vertex with
//// minimum key value, from the set of vertices
//// not yet included in MST
//class MST_Alg {
//private:
//    int ** graph;
//public:
//    int minKey(int key[], bool mstSet[])
//    {
//        // Initialize min value
//        int min = INT_MAX, min_index;
//        
//        for (int v = 0; v < V; v++)
//            if (mstSet[v] == false && key[v] < min)
//                min = key[v], min_index = v;
//        
//        return min_index;
//    }
//    
//    // A utility function to print the
//    // constructed MST stored in parent[]
//    void printMST(int parent[], int graph[V][V])
//    {
//        cout << "Edge \tWeight\n";
//        for (int i = 1; i < V; i++)
//            cout << parent[i]+1 << " - " << i+1 << " \t"
//            << graph[i][parent[i]] << " \n";
//    }
//    
//    // Function to construct and print MST for
//    // a graph represented using adjacency
//    // matrix representation
//    void primMST(int graph[V][V])
//    {
//        // Array to store constructed MST
//        int parent[V];
//        
//        // Key values used to pick minimum weight edge in cut
//        int key[V];
//        
//        // To represent set of vertices included in MST
//        bool mstSet[V];
//        
//        // Initialize all keys as INFINITE
//        for (int i = 0; i < V; i++)
//            key[i] = INT_MAX, mstSet[i] = false;
//        
//        // Always include first 1st vertex in MST.
//        // Make key 0 so that this vertex is picked as first
//        // vertex.
//        key[0] = 0;
//        
//        // First node is always root of MST
//        parent[0] = -1;
//        int k =0;
//        // The MST will have V vertices
//        cout << "Edge \tWeight\n";
//        for (int count = 0; count < V - 1; count++) {
//            
//            // Pick the minimum key vertex from the
//            // set of vertices not yet included in MST
//            int u = minKey(key, mstSet);
//            
//            // Add the picked vertex to the MST Set
//            mstSet[u] = true;
//            if (count!=0) {
//                cout << k+1 <<  " - " << u+1 << " \t"
//                << graph[k][u] << " \n";
//                k=u;
//            }
//            
//            // Update key value and parent index of
//            // the adjacent vertices of the picked vertex.
//            // Consider only those vertices which are not
//            // yet included in MST
//            for (int v = 0; v < V; v++)
//                
//                // graph[u][v] is non zero only for adjacent
//                // vertices of m mstSet[v] is false for vertices
//                // not yet included in MST Update the key only
//                // if graph[u][v] is smaller than key[v]
//                if (graph[u][v] && mstSet[v] == false
//                    && graph[u][v] < key[v])
//                {
//                    parent[v] = u, key[v] = graph[u][v];
//                }
//        }
//        
//        // Print the constructed MST
//        //    printMST(parent, graph);
//    }
//    
//    
//    void findMin(int graph[V][V],bool mstSet[],int indices[2])
//    {
//        int min = INT_MAX;
//        for (int i=0;i<V;i++){
//            for(int j =0;j<V;j++){
//                if((mstSet[i] ==false ||mstSet[j]==false)&&graph[i][j]&& graph[i][j]<min){
//                    min =graph[i][j];
//                    indices[0]=i;
//                    indices[1]=j;
//                }
//            }
//        }
//        mstSet[indices[0]]=true;
//        mstSet[indices[1]]=true;
//    }
//    
//    
//    void KruskalMST(int graph[V][V])
//    {
//        // Array to store constructed MST
//        //    int addEdge[V][V];
//        
//        // Key values used to pick minimum weight edge in cut
//        //    int key[V];
//        
//        int indices[2]={};
//        // To represent set of vertices included in MST
//        bool mstSet[V];
//        // Initialize all keys as INFINITE
//        for (int i = 0; i < V; i++){
//            mstSet[i] = false;
//            //        key[i] = INT_MAX;
//        }
//        
//        // Always include first 1st vertex in MST.
//        // Make key 0 so that this vertex is picked as first
//        // vertex.
//        //    key[0] = 0;
//        cout << "Edge \tWeight\n";
//        for (int count = 0; count < V - 1; count++) {
//            findMin(graph, mstSet, indices);
//            
//            cout << indices[0]+1 << " - " << indices[1]+1 << " \t"
//            << graph[ indices[0]][ indices[1]] << " \n";
//        }
//    }
//};
// //Driver's code
//int main()
//{
//    MST_Alg a;
//    int graph[V][V] = { { 0, 10, 0, 30, 45, 0 },
//                        { 10, 0, 50, 0, 40, 25 },
//                        { 0, 50, 0, 0, 35, 15 },
//                        { 30, 0, 0, 0, 0, 20 },
//                        { 45, 40, 35, 0, 0, 55 },
//                        { 0, 25, 15, 20, 55, 0 } };
//    int graph1[V][V] = { { 0, 10, 0, 30, 45, 0 },
//                        { 10, 0, 50, 0, 40, 25 },
//                        { 0, 50, 0, 0, 35, 15 },
//                        { 30, 0, 0, 0, 0, 20 },
//                        { 45, 40, 35, 0, 0, 55 },
//                        { 0, 25, 15, 20, 55, 0 } };
//    cout<<"Use Kruskal's algorithm to find minimal spaning tree "<<endl;
////    MST_Alg  myMST_Alg(V);
//    a.KruskalMST(graph1);
//    cout<<endl<<"Use Prim's algorithm to find minimal spaning tree"<<endl;
//      a.primMST(graph);
//    // Print the solution
////    myMST_Alg.KruskalMST(graph);
// 
//    return 0;
//}
// 
