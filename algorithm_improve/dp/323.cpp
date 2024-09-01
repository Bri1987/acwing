#include <iostream>
#include <cstring>

using namespace std;

const int N = 1510;
int h[N], e[N*2], ne[N*2], w[N*2], idx;
int n;
bool not_root[N];

int f[N][2];

void add(int a,int b){
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

void dfs(int root, int p){
    f[root][1] = 1;
    f[root][0] = 0;

    for(int i = h[root]; i != -1; i = ne[i]) {
        int j = e[i];
        if (j != p) {
            dfs(j, root);
            // 注意这里题目要求看到所有边, 所以如果root是0,别的点就都得是1
            f[root][0] += f[j][1];
            f[root][1] += min(f[j][1], f[j][0]);
        }
    }
}

int main(){
    // 注意这个写法
    while (~scanf("%d", &n))
    {
        memset(h, -1, sizeof h); idx = 0;
        memset(not_root, 0, sizeof not_root);
        for (int i = 0; i < n; i ++ )
        {
            int a, b, siz;
            scanf("%d:(%d) ", &a, &siz);
            while (siz -- )
            {
                scanf("%d", &b);
                // 加的单向边
                add(a, b);
                not_root[b] = true;
            }
        }
        // 道路构成树, 我们一定能选出一个root(既然是树, 一定有一个点是没有被任何边指向的)
        int root = 0;
        while (not_root[root]) root ++ ;
        dfs(root,-1);
        printf("%d\n", min(f[root][0], f[root][1]));
    }
    return 0;
}