#include <iostream>
#include <cstring>

using namespace std;

const int N = 510;

int n;
int g[N][N];        // 邻接矩阵，存储所有边
int dist[N];        // 存储其他点到当前最小生成树的距离
bool st[N];     // 存储每个点是否已经在生成树中

int prim(){
    int res = 0;
    for(int i = 0; i < n; i++){
        int t = -1;
        //2. 找到集合外距离最近的点
        for(int j = 1; j <= n ;j++){
            if(!st[j] && (t == -1 || dist[j] < dist[t]))
                t = j;
        }

        if (i && dist[t] == 0x3f3f3f3f) return 0x3f3f3f3f;

        if (i) res += dist[t];
        st[t] = true;

        //3. 用t来更新其他点到生成树的距离
        for(int j = 1; j <= n ;j++){
            if(!st[j] && dist[j] > g[t][j])
                dist[j] = g[t][j];
        }
    }
    return res;
}

int main(){
    int m;
    cin >> n >> m;
    //1. 初始化dist数组
    memset(dist, 0x3f, sizeof dist);

    // ! 记得初始化数组g
    memset(g, 0x3f, sizeof g);
    while (m--){
        int a,b,c;
        cin >> a >> b >> c;
        g[a][b] = g[b][a] = min(c,g[a][b]);
    }

    int res = prim();
    if(res == 0x3f3f3f3f)
        puts("impossible");
    else
        cout << res << endl;
    return 0;
}