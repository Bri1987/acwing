#include <iostream>
#include <algorithm>

using namespace std;
const int N = 2 * 100010;
int p[N];

int n, m;
int cnt;       //看看连了多少次了，即已经有多少个点加入了生成树

//! 由于kruskal是按边来遍历，所以之前的图存储其实不是很方便!
struct Edge     // 存储边
{
    int a, b, w;

    bool operator< (const Edge &W)const
    {
        return w < W.w;
    }
}edges[N];

//并查集思想
//返回x所在集合的编号 + 路径压缩
int find(int x){
    //注意这里p[x] = find(p[x]) , 顺手让路上的每个父结点都指向集合编号根节点
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

void kruskal(){
    //对所有边排序
    std::sort(edges,edges + m);

    int res = 0;
    for(int i = 0; i < m; i++){
        int a = edges[i].a, b = edges[i].b, w = edges[i].w;

        a = find(a), b = find(b);
        if (a != b)     // 如果两个连通块不连通，则将这两个连通块合并
        {
            res += w;
            p[a] = b;
            cnt ++;
        }
    }

    if(cnt < n - 1)
        puts("impossible");
    else
        cout << res << endl;
}

int main(){
    cin >> n >> m;

    //一共有 n个数，编号是 1∼n，最开始每个数各自在一个集合中
    for(int i = 1; i <= n; i++)
        p[i] = i;

    for(int i = 0 ; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edges[i].a = a; edges[i].b = b;
        edges[i].w = c;
    }

    kruskal();
    return 0;
}