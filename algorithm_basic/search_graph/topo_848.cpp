#include <iostream>
#include <cstring>

using namespace std;
const int N = 1000010;

int n;
int h[N],e[N],ne[N],idx;
int hh = 0, tt = -1;
int q[N];
int d[N];     //记录每个点的入度

void add(int a, int b){
    e[idx] = b; ne[idx] = h[a]; h[a] = idx++;
    //增加一个入度
    d[b]++;
};

int main(){
    int m;
    cin >> n >> m;
    memset(h,-1,sizeof h);
    while (m--){
        int a,b;
        cin >> a >> b;
        add(a,b);
    }

    //先加入所有入度为0的点
    for (int i = 1; i <= n; i ++ )
        if (!d[i])
            q[ ++ tt] = i;

    while (hh <= tt){
        int head = q[hh ++ ];
        //当前点由于已经被摘除，它指向的所有点的入度都减1
        for (int i = h[head]; i != -1; i = ne[i]){
            int j = e[i];
            if (-- d[j] == 0)
                q[ ++ tt] = j;
        }
    }

    //!! 如果所有点都入队了，说明存在拓扑序列；否则不存在拓扑序列
    if(tt == n - 1){
        for(int i = 0; i <= n - 1; i++)
            cout << q[i] << " ";
    }else
        cout << -1 << endl;
}