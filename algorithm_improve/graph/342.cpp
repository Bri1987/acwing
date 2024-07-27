#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
using namespace std;

typedef pair<int,int> PII;

const int N = 25010, M = 150010, INF = 0x3f3f3f3f;
int h[N], e[M], ne[M], w[M], idx;
int dist[N];
bool st[N];

int n, mr, mp, s;
//id:点所在的连通块号, bcnt:连通块数量
int id[N], bcnt;
//连通块的入度数组
int deg[N];
vector<int> block[N];

int q[N], hh, tt = -1;

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
}

void dfs(int u)
{
    block[bcnt].push_back(u);
    id[u] = bcnt;

    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(!id[j]) dfs(j);
    }
}

void dijkstra(int block_id)
{
    priority_queue<PII, vector<PII>, greater<PII>> heap;

    //取出该连通块所有的点, 入堆
    for(int u : block[block_id])
    {
        heap.push({dist[u], u});
    }

    while(heap.size())
    {
        PII t = heap.top();
        heap.pop();
        int u = t.second;

        if(st[u]) continue;
        st[u] = true;

        for(int i = h[u]; i != -1; i = ne[i])
        {
            int j = e[i];
            if(dist[j] > dist[u] + w[i])
            {
                // dijkstra算法不能有负权边，所以更新时只能把正权边入堆。而遇到负权边时，也能更新dist数组，但不入堆
                dist[j] = dist[u] + w[i];
                if(id[j] == block_id) heap.push({dist[j], j});
            }

            if(id[j] != block_id && --deg[id[j]] == 0)
                q[++tt] = id[j];
        }

    }
}

void topoSort()
{
    //dist赋初值
    memset(dist, 0x3f, sizeof dist);
    // 保证dist记录的起点
    dist[s] = 0;

    //入度为0的连通块入队列
    for(int i = 1; i <= bcnt; i++)
    {
        if(!deg[i]) q[++tt] = i;
    }

    while(hh <= tt)
    {
        int t = q[hh++];
        dijkstra(t);
    }
}

int main()
{
    scanf("%d%d%d%d", &n, &mr, &mp, &s);
    memset(h, -1, sizeof h);
    for(int i = 0; i < mr; i++)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c), add(b, a, c);
    }

    //建立所有的连通块
    for(int i = 1; i <= n; i++)
    {
        if(!id[i]) {
            ++bcnt;
            dfs(i);
        }
    }
    //在连通块之间建边
    for(int i = 0; i < mp; i++)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c), deg[id[b]]++;
    }

    //算法开始
    topoSort();

    for(int i = 1; i <= n; i++)
    {
        if(dist[i] > INF / 2) puts("NO PATH");
        else printf("%d\n", dist[i]);
    }

    return 0;
}