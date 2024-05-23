#include <iostream>

using namespace std;
const int N = 150010;

int n,m,p[N],s[N];
int d[N];

//根据题意当A和B之间有边，并且B和C之间有边时，那么A和C之间也必然需要有一条边才行，这样的图才叫有效图
//也就是说具有传递性，实际的意思就是同一个连通块中的任意俩个点之间都必须有一条边，由于题目说了没有重边
//，所以同一个连通块中的任意俩点之间有且仅有一条边。
//
//通过上述分析我们得出了一个结论：就是同一个连通块中的任意俩个点之间有且仅有一条边。
//那么我们不妨设一个连通块的大小为sz,这个连通块中每个点都会和其他点之间有一条边，
//那么连通块的中每个点的度数必然为sz-1,所以我们只需要判断每一个连通中每一个点的度数
//是否为当前连通块大小减1即可，对于这一过程，我们可以使用并查集进行维护。

//返回x所在集合的编号 + 路径压缩
int find(int x){
    //注意这里p[x] = find(p[x]) , 顺手让路上的每个父结点都指向集合编号根节点
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        p[i] = i;
        s[i] = 1;
    }
    while (m--){
        int a,b;
        cin >> a >> b;
        d[a]++; d[b]++;
        if(find(a) != find(b)){
            s[find(a)] += s[find(b)];
            p[find(b)] = find(a);
        }
    }

    for(int i = 1; i <= n; i++){
        if(d[i] != s[find(i)] - 1){
            puts("NO");
            return 0;
        }
    }
    puts("YES");
    return 0;
}