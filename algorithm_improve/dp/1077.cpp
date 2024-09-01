#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;


const int N = 1510;

int n;
int h[N], e[N], ne[N], idx,w[N];
int f[N][3];  // 0 : 父节点守卫, 1: 子节点守卫, 2: 自己守卫
bool st[N];


void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void dfs(int u)
{
    f[u][2] = w[u];

    int sum = 0;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        dfs(j);
        // 这个节点等着父节点解决, 后面的节点必须1 or 2解决
        f[u][0] += min(f[j][1], f[j][2]);
        // 自己解决了, 别的节点怎样都可以
        f[u][2] += min(min(f[j][0], f[j][1]), f[j][2]);
        sum += min(f[j][1], f[j][2]);
    }

    f[u][1] = 1e9;
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        // 这个节点等着子节点解决, 后面的节点必须1 or 2解决, 并且至少有一个2
        // 保证了至少有一个子节点是守卫状态, 保证了至少有一个是2
        f[u][1] = min(f[u][1], sum - min(f[j][1], f[j][2]) + f[j][2]);
    }
}


int main()
{
    cin >> n;

    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i ++ )
    {
        int id, cost, cnt;
        cin >> id >> cost >> cnt;
        w[id] = cost;
        while (cnt -- )
        {
            int ver;
            cin >> ver;
            add(id, ver);
            st[ver] = true;
        }
    }

    int root = 1;
    while (st[root]) root ++ ;

    dfs(root);

    cout << min(f[root][1], f[root][2]) << endl;

    return 0;
}
