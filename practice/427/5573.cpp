#include <iostream>
#include <cstring>

using namespace std;

const int N = 100010;
int h[N],e[N],ne[N],idx;

int n;

void add(int a,int b){
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

int dfs(int x, int del,int fa){
    //cout << x << " " << h[x] << endl;
    int res = 1;
    int mx = 1;
    for(int u = h[x]; u != -1;  u = ne[u]){
        int j = e[u];
        if(fa != j) {
            int d = dfs(j, del, x);
            mx = max(mx, d);
            res += d;
        }

    }
    if(x == del)
        return mx;
    else
        return res;
}

int main(){
    memset(h, -1, sizeof h);
    cin >> n;
    for(int i = 0; i < n-1; i++){
        int a,b;
        cin >> a >> b;
        add(a,b);
        add(b,a);
    }

    int mi = n;
    for(int i = 1; i <= n; i++){
        int res = dfs(i,i,-1);
        mi = min(res, mi);
        //cout << res << endl;
    }
    cout << mi ;
    return 0;
}