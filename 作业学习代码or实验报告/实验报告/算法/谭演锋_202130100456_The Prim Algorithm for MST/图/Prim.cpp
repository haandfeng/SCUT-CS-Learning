

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <queue>

using namespace std;

#define V 6
class UF {
    private:
    //A tree’s “weight”
    int *size;
//    Number of connected node
    int count;
//    Recording a tree
    int *parent;
    
public:
    // n 为图中节点的个数
    UF(int n) {
        count = n;
        parent = new int[n];
        size = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    // Connect two node into one tree and balance them
    void Union(int p, int q) {
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP == rootQ)
            return;

        // 小树接到大树下面，较平衡
        if (size[rootP] > size[rootQ]) {
            parent[rootQ] = rootP;
            size[rootP] += size[rootQ];
        } else {
            parent[rootP] = rootQ;
            size[rootQ] += size[rootP];
        }
        // 两个连通分量合并成一个连通分量
        count--;
    }

    // Evaluate whether two nodes are connected 
    bool connected(int p, int q) {
        int rootP = find(p);
        int rootQ = find(q);
        return rootP == rootQ;
    }

    // Return the parent node and compress the route
 int find(int x) {
        while (parent[x] != x) {
            // 进行路径压缩
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    // return the data member count
   int Count() {
        return count;
    }
};

class MST_Alg {
    
public:
    int minKey(int key[], bool mstSet[])
    {

        int min = INT_MAX, min_index;

        for (int v = 0; v < V; v++)
            if (mstSet[v] == false && key[v] < min)
                min = key[v], min_index = v;

        return min_index;
    }




    void printMST(int p[],int parent[], int graph[V][V])
    {
        cout << "Edge \tWeight\n";
        for (int i = 1; i < V; i++)
        {   int a= p[i];
            int b =parent[a-1];
            cout << b+1 << " - " << a  << " \t"
            << graph[b][a-1] << " \n";
        }
    }




    void primMST(int graph[V][V])
    {

        int parent[V];

        int key[V];
        int * p = new int[V];
        bool mstSet[V];
        int last_v=-1;
        int last_u=-1;
        for (int i = 0; i < V; i++)
            key[i] = INT_MAX, mstSet[i] = false;


        key[0] = 0;
        
        parent[0] = -1;
        int k =0;
        clock_t tt1;
        clock_t tt2;
        tt1 = clock();
        for (int count = 0; count < V - 1; count++) {
            int u = minKey(key, mstSet);
            mstSet[u] = true;
            for (int v = 0; v < V; v++){
                if (graph[u][v] && mstSet[v] == false
                    && graph[u][v] < key[v])
                {   //if(last_u!=u){
                    //                    cout<<u+1<<"-"<<v+1<<endl;
                    //                    }
                    //                    cout<<u+1<<"-"<<v+1<<endl;
//                    last_u=u;
//                    last_v=v;
                    parent[v] = u, key[v] = graph[u][v];}
            }
//            cout<<u+1;
            p[count]=u+1;
        }
        tt2 = clock();
        int u = minKey(key, mstSet);
        p[V-1]=u+1;
       printMST(p, parent,graph);
        cout<<"Running time: "<<tt2-tt1<<endl;
    }

    void findMin(int graph[V][V],UF mst,int indices[2])
    {
        int min = INT_MAX;
        for (int i=0;i<V;i++){
            for(int j =0;j<V;j++){
                if(graph[i][j]&& graph[i][j]<min&& !mst.connected(i, j)){
                    min =graph[i][j];
                    indices[0]=i;
                    indices[1]=j;
                }
            }
        }
        mst.Union(indices[0], indices[1]);
    }

    void KruskalMST(int graph[V][V])
    {
        
        int indices[2]={};

        bool mstSet[V];
        UF mst(V);
        for (int i = 0; i < V; i++){
            mstSet[i] = false;
        }
        cout << "Edge \tWeight\n";
        clock_t tt1;
        clock_t tt2;
        clock_t tt3=0;
        tt1 = clock();
        for (int count = 0; count < V - 1; count++) {
            tt1 = clock();
            findMin(graph, mst, indices);
            tt2 = clock();
            tt3 += tt2-tt1;
            cout << indices[0]+1 << " - " << indices[1]+1 << " \t"
                    << graph[ indices[0]][ indices[1]] << " \n";
        }
        cout<<"Running time: "<<tt3<<endl;
    }

};




int main()
{
    int graph[V][V] = { { 0, 10, 0, 30, 45, 0 },
                        { 10, 0, 50, 0, 40, 25 },
                        { 0, 50, 0, 0, 35, 15 },
                        { 30, 0, 0, 0, 0, 20 },
                        { 45, 40, 35, 0, 0, 55 },
                        { 0, 25, 15, 20, 55, 0 } };
    int graph1[V][V] = { { 0, 10, 0, 30, 45, 0 },
                        { 10, 0, 50, 0, 40, 25 },
                        { 0, 50, 0, 0, 35, 15 },
                        { 30, 0, 0, 0, 0, 20 },
                        { 45, 40, 35, 0, 0, 55 },
                        { 0, 25, 15, 20, 55, 0 } };
    
    MST_Alg m;
    clock_t tt1;
    clock_t tt2;
    cout<<"Prim's algorithm:"<<endl;
//    cout<<"Minimum spanning tree: ";
    tt1 = clock();
    m.primMST(graph);
    tt2 =clock();
//    cout<<"Running time: "<<tt2-tt1<<endl;
    
    cout<<"Kruskal's algorithm:"<<endl;
    tt1 = clock();
    m.KruskalMST(graph1);
    tt2 =clock();
//    cout<<"Running time: "<<tt2-tt1<<endl;
    
    return 0;
}

