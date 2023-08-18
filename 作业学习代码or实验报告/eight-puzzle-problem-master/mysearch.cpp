#include "mysearch.h"

MySearch::MySearch()
{

}

MySearch::MySearch(string init_state,string goal_state){
    this->init_state = init_state;
    this->goal_state = goal_state;
}


void MySearch::searchHelp(int type){
    visit.clear();
    step = 0;
    clock_t startTime = clock();
    switch (type) {
        case 0:
            bfs();
            break;
        case 1:
            dfs(init_state,0);
            break;
        case 2:
            best_first();
            break;
        case 3:
            branchAndBound(init_state,0);
            break;
        default:
            break;
    }
    clock_t endTime = clock();
    run_time = (double)(endTime - startTime) / CLOCKS_PER_SEC*1000.0;
}

double MySearch::getSearchTime(){
    return run_time;
}

int MySearch::getSearchStep(){
    return step;
}

void MySearch::setInitState(string init_state){
    this->init_state = init_state;
}

void MySearch::setGoalState(string goal_state){
    this->goal_state = goal_state;
}

int MySearch::reserseNum(string& s){
    int sum = 0;
    for(int i = 1;i<9;i++){
        for(int j = 0;j<i;j++){
            if(s[i] == '0') continue;
            if(s[j]>s[i]) {
                sum++;
            }
        }
    }
    return sum%2;
}

bool MySearch::isHavingSolution(string& s1,string& s2){
    return reserseNum(s1) == reserseNum(s2);
}

string MySearch::move(string s1,int pos,int swap_pos){
    char tmp = s1[pos];
    s1[pos] = s1[swap_pos];
    s1[swap_pos] = tmp;
    if(visit.count(s1) == 0) return s1;
    return "";
}

bool MySearch::cmp(string& s1,string& s2){
    string goal_state ="123456780";
    int sum1 = 0,sum2 = 0;
    for(int i = 0;i<9;i++) {
        sum1 += (s1[i] != goal_state[i]);
        sum2 += (s2[i] != goal_state[i]);
    }
    return sum1 > sum2;
}


void MySearch::bfs(){
    queue<string>qu;
    qu.push(init_state);
    visit.insert(init_state);
    while(!qu.empty()){
        string current = qu.front();
        qu.pop();
        step++;
        if(current == goal_state){
            qDebug()<<"bfs steps: "<<step<<endl;
            return;
        }
        int pos = current.find('0');
        for(int i : shifts[pos]){
            string next = move(current,pos,i);
            if(next == "") continue;
            qu.push(next);
            visit.insert(next);
        }
    }
    qDebug()<<"search fail\n";
}


void MySearch::dfs(string current,int depth){
   step++;
   if(depth > lowerBound) return;
   if(current == goal_state){
       qDebug()<<"dfs steps: "<<step<<endl;
       return;
   }
   int pos = current.find('0');
   for(int i:shifts[pos]){
       string next = move(current,pos,i);
       if(next == "") continue;
       visit.insert(next);
       dfs(next,depth+1);
   }
}

void MySearch::best_first(){
    vector<string>qu;
    qu.push_back(init_state);
    visit.insert(init_state);
    while(!qu.empty()){
        string current = qu[qu.size()-1];
        qu.pop_back();
        step++;
        if(current == goal_state){
            qDebug()<<"best_first steps: "<<step<<endl;
            return;
        }
        int pos = current.find('0');
        for(int i : shifts[pos]){
            string next = move(current,pos,i);
            if(next == "") continue;
            qu.push_back(next);
            visit.insert(next);
        }
        sort(qu.begin(),qu.end(),cmp);
    }
    qDebug()<<"search fail\n";
}

void MySearch::branchAndBound(string current,int depth){
   step++;
   if(depth > lowerBound) return;
   if(current == goal_state){
       qDebug()<<"branch and bound steps: "<<step<<endl;
       lowerBound = min(lowerBound,depth);
       return;
   }
   int pos = current.find('0');
   for(int i:shifts[pos]){
       string next = move(current,pos,i);
       if(next == "") continue;
       visit.insert(next);
       branchAndBound(next,depth+1);
   }
}
