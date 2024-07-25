#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
#include <unordered_map>

using namespace std;

unordered_map<string, pair<char,string>> prev_;
unordered_map<string,int> d;

string st = "12345678";

string moveA(string s){
    reverse(s.begin(),s.end());
    return s;
}

string moveB(string s){
    string ss;
    ss += s[3];
    ss += s[0];
    ss += s[1];
    ss += s[2];
    ss += s[5];
    ss += s[6];
    ss += s[7];
    ss += s[4];
    return ss;
}

string moveC(string s){
    string ss;
    ss += s[0];
    ss += s[6];
    ss += s[1];
    ss += s[3];
    ss += s[4];
    ss += s[2];
    ss += s[5];
    ss += s[7];
    return ss;
}

void bfs(const string& ed){
    queue<string> q;
    q.push(st);
    d[st] = 0;
    while(!q.empty()){
        string t = q.front();
        q.pop();

        if(t == ed)
            break;
        string getA = moveA(t);
        string getB = moveB(t);
        string getC = moveC(t);
        if(d.find(getA) == d.end()){
            q.push(getA);
            d[getA] = d[t] + 1;
            prev_[getA] = {'A',t};
        }
        if(d.find(getB) == d.end()){
            q.push(getB);
            d[getB] = d[t] + 1;
            prev_[getB] = {'B',t};
        }
        if(d.find(getC) == d.end()){
            q.push(getC);
            d[getC] = d[t] + 1;
            prev_[getC] = {'C',t};
        }
    }
}

int main(){
    string ed;
    for(int i = 0; i < 8; i++){
        int a;
        cin >> a;
        ed += a + '0';
    }
    bfs(ed);
    cout << d[ed] << endl;

    if(st != ed){
        vector<char> vec;
        while(prev_[ed].second != st){
            vec.push_back(prev_[ed].first);
            ed = prev_[ed].second;
        }
        vec.push_back(prev_[ed].first);
        for(int i = vec.size()-1; i >= 0; i--){
            cout << vec[i];
        }
    }
    return 0;
}