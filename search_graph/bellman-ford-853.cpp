#include <iostream>
#include <cstring>

using namespace std;

const int N = 510, M = 10010;

int n, m ,k;
int dist[N] , backup[N];        // dist[x]存储1到x的最短路距离

struct Edge     // 边，a表示出点，b表示入点，w表示边的权重
{
    int a, b, w;
}edges[M];

// 求1到n的最短路距离，如果无法从1走到n，则返回-1。
void bellman_ford()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;

    // 如果第n次迭代仍然会松弛三角不等式(**即最短路径大于n条边**)，就说明存在一条长度是n+1的最短路径，由抽屉原理，路径中至少存在两个相同的点，说明图中存在负权回路。
    //           b
    //      a
    //
    // 点1                  相当于意思就是最终如果都能找到最短路径，则一定构成三角形
    //即最终dist[b] <= dist[a] + w
    for (int i = 0; i < k; i ++ ) {
        //需要备份dist数组 backup
        //更新了一个点b，然后dist[b]变了，新的dist[b]+w 可能用这个新结果顺手继续更新了另一个点c，但是c的这一次更新本来在这次是不应该被更新到的
        // 所以只用上一次更新后的dist结果迭代这一次的距离
        memcpy(backup,dist,sizeof dist);
        for (int j = 0; j < m; j ++ ) {
            int a = edges[j].a, b = edges[j].b, w = edges[j].w;
            if (dist[b] > backup[a] + w)
                dist[b] = backup[a] + w;
        }
    }
}

int main(){
    cin >> n >> m >> k;
    for(int i = 0; i < m ;i++){
        int x,y,z;
        cin >> x >> y >> z;
        edges[i] = {x,y,z};
    }

    bellman_ford();
    //不能用dist[n] == 0x3f3f3f3f判断，比如正无穷走负权 把另一个正无穷更新成小于正无穷的某个数了
    //但是也不会负权太多，权还是有范围的，所以大于0x3f3f3f3f / 2就行
    if(dist[n]>0x3f3f3f3f/2) puts("impossible");
    else printf ("%d",dist[n]);
    return 0;
}