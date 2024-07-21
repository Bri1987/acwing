#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> PII;

const int N=110,M=10110;
int n,k;
int h[N],e[M],w[M],ne[M],idx;
int level[N];//等级数组
int dist[N];//最短距离
bool st[N];

void add(int a,int b,int c)
{
    e[idx]=b,w[idx]=c,ne[idx]=h[a],h[a]=idx++;
}

int dijkstra(int l,int r)
{
    memset(dist,0x3f,sizeof dist);
    memset(st,0,sizeof st);

    priority_queue<PII,vector<PII>,greater<PII>> heap;

    dist[0]=0;
    heap.push({0,0});
    while(heap.size())
    {
        PII t=heap.top();
        heap.pop();

        int u=t.second;
        if(st[u])continue;
        st[u]=true;

        for(int i=h[u];~i;i=ne[i])
        {
            int j=e[i];
            // 不在区间内的边不能走
            if(level[j]>r||level[j]<l)
                continue;
            if(dist[j]>dist[u]+w[i])
            {
                dist[j]=dist[u]+w[i];
                heap.push({dist[j],j});
            }
        }
    }

    return dist[1];
}
int main()
{
    cin>>k>>n;

    memset(h,-1,sizeof h);

    for(int i=1;i<=n;i++)
    {
        int p,l,m;
        cin>>p>>l>>m;
        // 所有直接购买的 都视为从0节点出发
        add(0,i,p);
        level[i]=l;

        for(int j=0;j<m;j++)
        {
            int u,v;
            cin>>u>>v;
            add(u,i,v);
        }
    }

    int res=1e9;
    // 枚举所有包含1节点等级的区间，注意不能直接枚举最大区间
    // 比如酋长（原点1）的等级为5，等级限制为2，如果直接用最大的区间求，那么dijkstra函数里更新最小值的时候，所有等级为3-7之间的就都能交换了，3与7能交换就与等级限制为2矛盾了
    // 3-5,4-6,5-7这样
    for(int i=level[1]-k;i<=level[1];i++)
        res=min(res,dijkstra(i,i+k));

    printf("%d",res);

    return 0;
}