#include <iostream>
#include <queue>
#include <cstring>
#include <unordered_map>

using namespace std;
typedef pair<int, int> PII;

const int N = 50010, M = 100010;

int h[N], e[2*M], ne[2*M], w[2*M],idx;
int loc[7];

int dist[7][N];        // 存储所有点到1号点的距离
bool st[N];     // 存储每个点的最短距离是否已确定

bool check[7];


// 添加一条边a->b
void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

// 求1号点到n号点的最短距离，如果不存在，则返回-1
void dijkstra(int node,int d[])
{
    memset(st,0,sizeof st);
    d[node] = 0;
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.push({0, node});      // first存储距离，second存储节点编号

    while (heap.size())
    {
        auto t = heap.top();
        heap.pop();

        int ver = t.second, distance = t.first;

        if (st[ver]) continue;
        st[ver] = true;

        for (int i = h[ver]; i != -1; i = ne[i])
        {
            int j = e[i];
            if (d[j] > distance + w[i])
            {
                d[j] = distance + w[i];
                heap.push({d[j], j});
            }
        }
    }
}

int dfs(int cnt, int sum, int prev){
    if(cnt == 5){

        return sum;
    }

    int ans =1e9;
    for(int i = 2; i <= 6; i++){
        if(!check[i]){
            check[i] = true;
            //cout << prev << " " << loc[i] << "," << dist[prev][loc[i]]<< endl;
            ans = min(ans, dfs(cnt+1,sum + dist[prev][loc[i]], i));
            check[i] = false;
        }
    }
    return ans;
}

int main(){
    memset(h,-1,sizeof h);
    memset(dist, 0x3f, sizeof dist);
    int n,m;
    cin >> n >> m;
    loc[1] = 1;
    for(int i = 2; i <= 6; i++){
        cin >> loc[i];
    }

    while(m--){
        int a,b,c;
        cin >> a >> b >> c;
        add(a,b,c);
        add(b,a,c);
    }

    dijkstra(1,dist[1]);
    for(int i = 2; i <= 6; i++){
        dijkstra(loc[i],dist[i]);
    }

    int res = 1e9;
    for(int i = 2; i <= 6; i++){
        res = min(res, dfs(0,0,1));
    }
    cout << res;
    return 0;
}