#ifndef MYSEARCH_H
#define MYSEARCH_H
#include<vector>
#include<string>
#include <unordered_set>
#include <queue>
#include<QDebug>
using namespace std;

class MySearch
{
private:
    const vector<vector<int>>shifts = {{1,3},{0,2,4},{1,5},{0,4,6},{1,3,5,7},{2,4,8},{3,7},{4,6,8},{5,7}};
    unordered_set<string>visit;
    string init_state = "";
    string goal_state = "123456780";
    int step = 0;
    int lowerBound = 100;
    double run_time = 0;

public:
    MySearch();
    MySearch(string,string);

public:
    bool isHavingSolution(string&,string&);
    void searchHelp(int);
    double getSearchTime();
    int getSearchStep();
    void setInitState(string);
    void setGoalState(string);
private:
    void bfs();
    void dfs(string,int);
    void best_first();
    void branchAndBound(string,int);
private:
    int reserseNum(string&);
    string move(string,int,int);
    static bool cmp(string&,string&);
};

#endif // MYSEARCH_H
