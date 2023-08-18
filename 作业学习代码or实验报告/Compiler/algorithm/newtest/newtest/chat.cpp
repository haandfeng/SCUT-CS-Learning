////
////  chat.cpp
////  newtest
////
////  Created by 谭演锋 on 2023/5/11.
////
//
//#include <stdio.h>
//#include <iostream>
//#include <vector>
//#include <queue>
//#define V 6
//
//#include <iostream>
//#include <cstring>
//
//using namespace std;
//
//const int INF = 1e9;
//
//class Prim {
//private:
//    int n;  // number of vertices
//    int graph[V][V]
//    { { 0, 10, 0, 30, 45, 0 },
//        { 10, 0, 50, 0, 40, 25 },
//        { 0, 50, 0, 0, 35, 15 },
//        { 30, 0, 0, 0, 0, 20 },
//        { 45, 40, 35, 0, 0, 55 },
//        { 0, 25, 15, 20, 55, 0 } };
//;
//    bool visited[V];
//
//    // Priority queue data structure using a simple array
//    int pq[V][2];
//    int pq_size;
//    void push(int vertex, int weight) {
//        pq[pq_size][0] = weight;
//        pq[pq_size++][1] = vertex;
//    }
//    int pop() {
//        int min_idx = 0;
//        for (int i = 1; i < pq_size; i++) {
//            if (pq[i][0] < pq[min_idx][0]) {
//                min_idx = i;
//            }
//        }
//        int vertex = pq[min_idx][1];
//        pq[min_idx][0] = pq[--pq_size][0];
//        pq[min_idx][1] = pq[pq_size][1];
//        return vertex;
//    }
//
//public:
//    Prim(int num_vertices) {
//        n = num_vertices;
//        memset(graph, 0, sizeof(graph));
//        memset(visited, false, sizeof(visited));
//    }
//
//    void add_edge(int u, int v, int w) {
//        graph[u][v] = w;
//        graph[v][u] = w;
//    }
//
//    void compute() {
//        int dist[V];
//        int parent[V];
//
//        int src = 0;
//        push(src, 0);
//        dist[src] = 0;
//        for (int i = 1; i < n; i++) {
//            dist[i] = INF;
//            parent[i] = -1;
//        }
//
//        while (pq_size > 0) {
//            int u = pop();
//            visited[u] = true;
//
//            for (int v = 0; v < n; v++) {
//                if (graph[u][v] && !visited[v] && graph[u][v] < dist[v]) {
//                    dist[v] = graph[u][v];
//                    parent[v] = u;
//                    push(v, dist[v]);
//                }
//            }
//
//            int next_vertex = pq_size > 0 ? pq[0][1] : -1;
//            if (next_vertex != -1) {
//                cout << "Selected edge: " << parent[next_vertex] << " - " << next_vertex << endl;
//            }
//        }
//    }
//};
//
//int main() {
//    Prim prim(V);
//    prim.compute();
//    return 0;
//}
