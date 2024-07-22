#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

typedef pair<int,int> PII;

const int N = 1010, M = 10010;
int h[N],e[2*M],ne[2*M],w[2*M],idx;
bool st[N];
int d[N];

int n,m;

void add(int a,int b,int c){
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

bool dfs(int node,int mx, int k){
    memset(d,0x3f, sizeof d);
    memset(st,0,sizeof st);
    priority_queue<PII,vector<PII>,greater<>> q;
    q.push({0,node});
    d[node] = 0;
    while(q.size()){
        auto [dis,t] = q.top();
        q.pop();

        if(st[t])
            continue;

        for(int i = h[t]; i != -1; i = ne[i]){
            int j = e[i];
            if(!st[j]){
                // 此时最短路指的是大于mx的边的数量，不一定是和的最小值
                if(d[j] > d[t] + (w[i] > mx ? 1 : 0)){
                    d[j] = d[t] + (w[i] > mx ? 1 : 0);
                    q.push({d[j],j});
                }
            }
        }
    }

    if(d[n] > k)   return false;
    return true;
}

int main(){
    int k;
    cin >> n >> m >> k;
    memset(h,-1,sizeof h);
    while(m--){
        int a,b,c;
        cin >> a >> b >> c;
        add(a,b,c);
        add(b,a,c);
    }

    // 二分，枚举每一个可能的值，和nju有道题有点像, 直到枚举到应该的边权为止
    int l = 0,r = 1e6+1;
    int ans = -1;
    while(l < r){
        int mid = (l + r) >> 1;
        if(dfs(1,mid,k)){
            ans = mid;
            r = mid;
        } else
            l = mid + 1;
    }
    cout << ans;
    return 0;
}