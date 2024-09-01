#include <iostream>
#include <cstring>
#include <unordered_map>

using namespace std;

const int N = 50010;
int h[N], e[N*2], ne[N*2], idx;
int n;
int sum[N];
int d1[N], d2[N], res;

void add(int a,int b){
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

void dfs(int root, int p){
    if(d1[root])
        return ;
    d1[root] = d2[root] = 0;
    for(int i = h[root]; i != -1; i = ne[i]){
        int j = e[i];
        if(j != p){
            dfs(j,root);
            if(d1[root] <= d1[j] + 1){
                d2[root] = d1[root];
                d1[root] = d1[j] + 1;
            } else if(d2[root] < d1[j] + 1)
                d2[root] = d1[j] + 1;
        }
    }
    res = max(res, d1[root] + d2[root]);
}

void cal(){
    //通过筛法求出1到n的所有约数之和
    for(int i = 1;i <= n;i ++)
    {
        for(int j = 2;j <= n / i;j ++)
        {
            sum[i * j] += i;
        }
    }
}

int main(){
    cin >> n;
    cal();

    memset(h,-1,sizeof h);
    for(int i = 2;i <= n;i ++)
    {
        if(sum[i] < i){
            add(sum[i],i);
            // add(i,sum[i]);
        }
    }

    // 这个记忆化还是有点小问题的, 加边的时候只能走一次, 否则可能重复计数, 上一次算d1的时候有值了, 就直接重复了
    for(int i = 1; i <= n; i++){
        dfs(i,-1);
    }
    cout << res;
    return 0;
}