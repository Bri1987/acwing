#include <iostream>

using namespace std;

const int N = 10010;
int p[N],f[N],s1[N],s2[N];
int a[N],v[N];

int c[N],d[N];

int find(int x){
    if(p[x] != x)   p[x] = find(p[x]);
    return p[x];
}

int main(){
    int n,m,w;
    cin >> n >> m >> w;
    for(int i = 1; i <= n; i++){
        int x,y;
        cin >> x >> y;
        p[i] = i;
        a[i] = x;
        v[i] = y;
        s1[i] = x;
        s2[i] = y;
    }

    while(m--){
        int x,y;
        cin >> x >> y;
        if(find(x) != find(y)){
            s1[find(x)] += s1[find(y)];
            s2[find(x)] += s2[find(y)];
            p[find(y)] = find(x);
        }
    }

    //离散化成一个数组
    int cnt = 0;
    for(int i = 1; i <= n; i++){
        if(find(i) == i){
            c[++cnt] = s1[i];
            d[cnt] = s2[i];
        }
    }

    for(int i = 1; i <= cnt; i++){
        for(int j = w; j >= c[i]; j--){
            f[j] = max(f[j],f[j-c[i]] + d[i]);
        }
    }
    cout << f[w];
    return 0;
}