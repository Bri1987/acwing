#include <iostream>
#include <cstring>

using namespace std;

const int N = 1000010;
int n;
// 对于每个点k，开一个单链表，存储k所有可以走到的点。h[k]存储这个单链表的头结点
int h[N], e[N], ne[N], idx;
//标记是否被访问过
bool st[N];
//记录每个点的子树节点数，包含自己
int child[N];
int ans = N;

// 添加一条边a->b
void add(int a, int b){
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void dfs(int u){
    st[u] = true; // st[u] 表示点u已经被遍历过
    int res = 0;

    //由于子树包含自己，先初始化为1
    child[u] = 1;
    //走完这个for就是处理完一个结点
    for (int i = h[u]; i != -1; i = ne[i])
    {
        //e[i]就是当前u结点能指向的结点
        int j = e[i];
        if (!st[j]) {
            dfs(j);
            child[u] += child[j];
            res = max(child[j],res);   //一个点的每一个子结点单独树的连通图结点数，相当于就是把当前点删了的结果
        }
    }

    //在达到结点u之前，总有一个结点(并且一定是一个)是已经走过了的(dfs的第一个点的话，此处算出的n-child[u]就是0), 要把来处结点的(剪去u整个子树分支)的图节点数也算一下
    res = max(res, n - child[u]); // 选择u节点为重心，最大的 连通子图节点数
    //一个结点处理完毕，更新一下ans
    ans = min(res, ans); //遍历过的假设重心中，最小的最大联通子图的 节点数
}

int main(){
    cin >> n;
    memset(h,-1, sizeof h);
    int a,b;
    for(int i = 0; i < n - 1; i++){
        cin >> a >> b;
        add(a,b);
        //注意是无向图，必须存2次，如果按有向图存的话，dfs的第一个点必须是根结点才能对，但这里无法保证！！
        add(b,a);
    }
    dfs(1);
    cout << ans << endl;
    return 0;
}