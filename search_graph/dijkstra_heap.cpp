#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;
const int N = 1500010;

typedef pair<int, int> PII;

int n,m;      // 点的数量
int h[N], w[N], e[N], ne[N], idx;       // 邻接表存储所有边
int dist[N];        // 存储所有点到1号点的距离
bool st[N];     // 存储每个点的最短距离是否已确定

// 添加一条边a->b
void add(int a, int b, int c){
    // 有重边也不要紧，假设1->2有权重为2和3的边，再遍历到点1的时候2号点的距离会更新两次放入堆中
    // 这样堆中会有很多冗余的点，但是在弹出的时候还是会弹出最小值2+x（x为之前确定的最短路径），
    // 并标记st为true，所以下一次弹出3+x会continue不会向下执行。
    w[idx] = c;
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

// 求1号点到n号点的最短距离，如果不存在，则返回-1
int dijkstra()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    //相当于一个小根堆
    //第一个是元素类型，第二个是Type of underlying sequence, defaults to vector_Tp>.
    //第三个是比较函数
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.push({0, 1});      // first存储距离，second存储节点编号

    while (heap.size())
    {
        //弹出最小元素，也就是当前点d的最小距离点t(到1点的最小距离)
        auto t = heap.top();
        heap.pop();

        int ver = t.second, distance = t.first;

        //可能是重复副本，重复的话就不处理 (可能是后面又Push进了更小的，原来这个就不用再处理了)
        if (st[ver]) continue;
        st[ver] = true;

        //3. 获得t的信息，更新所有可能的到最小值
        //h[ver]是对应的idx
        for (int i = h[ver]; i != -1; i = ne[i]){
            int j = e[i];
            if (dist[j] > distance + w[i]){
                dist[j] = distance + w[i];
                heap.push({dist[j], j});
            }
        }
    }

    if (dist[n] == 0x3f3f3f3f) return -1;
    return dist[n];
}

int main(){
    cin >> n >> m;
    memset(h, -1 ,sizeof h);

    for(int i = 0; i < m; i++){
        int a,b,c;
        cin >> a >> b >> c;
        add(a,b,c);
    }

    cout << dijkstra() << endl;
}