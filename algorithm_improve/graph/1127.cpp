#include <iostream>
#include <queue>
#include <cstring>

// 对每个牧场做迪杰斯特拉，加上堆优化，时间复杂度比floyd小

using namespace std;

const int P = 810, N = 510, M = 1460;

typedef pair<int,int> PII;

int h[P],e[2*M],ne[2*M],w[2*M],idx;
int d[P];
int loc[N];
bool st[P];

void add(int a,int b,int c){
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

void dij(int node){
    memset(d,0x3f,sizeof d);
    memset(st,0,sizeof st);
    priority_queue<PII,vector<PII>,greater<>> q;
    q.push({0,node});
    d[node] = 0;
    while(q.size()){
        auto [dis, t] = q.top();
        q.pop();

        if(st[t])   continue;

        st[t] = true;
        for(int i = h[t]; i!=-1; i = ne[i]){
            int j = e[i];
            if(d[j] > d[t] + w[i]){
                d[j] = d[t] + w[i];
                q.push({d[j],j});
            }
        }
    }
}

int main(){
    int n,p,m;
    cin >> n >> p >> m;
    memset(h,-1,sizeof h);
    for(int i = 1; i <= n; i++)
        cin >> loc[i];
    while(m--){
        int a,b,c;
        cin >> a >> b >> c;
        add(a,b,c);
        add(b,a,c);
    }

    int res = 1e9;
    bool find_one = true;
    for(int i = 1; i <= p; i++){
        find_one = true;
        dij(i);
        int ans = 0;
        for(int j = 1; j <= n; j++){
            if(d[loc[j]] > 0x3f3f3f3f / 2){
                find_one = false;
                break;
            } else {
                ans += d[loc[j]];
            }
        }
        if(find_one)
            res = min(res, ans);
    }
    cout << res ;
    return 0;
}