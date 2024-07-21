#include <iostream>
#include <cstring>
#include <queue>
#include <sstream>

using namespace std;

typedef pair<int,int> PII;
const int N = 510, M = 510*510;
int h[N],e[N],ne[N],w[N],idx;
bool st[N];
int d[N];

void add(int a,int b,int c){
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

int main(){
    memset(h,-1,sizeof h);
    memset(d,0x3f,sizeof d);

    int m,n;
    cin >> m >> n;
    m ++;
    while(m--){
        string s;
        getline(cin, s);
        stringstream s_(s);
        int num;
        vector<int> vec;
        while (s_ >> num) {
            vec.push_back(num);
        }
        for(int i = 0; i < vec.size(); i++)
            for(int j = i+1; j < vec.size(); j++)
                add(vec[i],vec[j],1);
    }

    priority_queue<PII,vector<PII>,greater<>> q;
    q.push({0,1});
    d[1] = 0;
    while(q.size()){
        auto [dis,t] = q.top();
        q.pop();

        if(st[t])   continue;
        st[t] = true;

        for(int i = h[t]; i != -1; i = ne[i]){
            int j = e[i];
            if(d[j] > w[i] + dis){
                d[j] = w[i] + dis;
                q.push({d[j],j});
            }
        }
    }

    if(d[n] > 0x3f3f3f3f / 2)   cout << "NO";
    else    cout << d[n]-1;
    return 0;
}