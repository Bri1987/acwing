#include <iostream>
#include <cstring>

using namespace std;

const int N = 6010;
int h[N], e[N], ne[N],idx;
int f[N][2];
int w[N];
bool has_father[N];

void add(int a, int b){
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

void dfs(int root){
    //如果选当前节点，就可以把f[root,1]先怼上他的高兴度
    f[root][1] = w[root];
    for(int i = h[root]; i != -1; i = ne[i]){
        int j = e[i];
        //dfs，得从最小慢慢往上算
        dfs(j);
        //当 f[i][1]时表示选 i号节点。
        //那么很明显 i号节点的快乐值需要算上
        //然后我们知道，如果选了这个点，它的所有字节点都是不能选的，所以我们应该给它加上 f[j][0]
        //
        //当 f[i][0]时表示不选 i号节点。
        //这时我们不需要加上 i号点的快乐值
        //如果不选这个点，它的子节点可以选也可以不选，所以我们应该给它加上 max f[j][0],f[j][1]
        f[root][1] += f[j][0];
        f[root][0] += max(f[j][1], f[j][0]);
    }
}

int main(){
    int n;
    cin >> n;
    memset(h, -1, sizeof h);
    for(int i = 1; i <= n; i++)
        cin >> w[i];

    int m = n - 1;
    while (m--) {
        int a, b;
        cin >> a >> b;
        has_father[a] = true;
        add(b, a);
    }

    int root = 0;
    for(int i = 1; i <= n; i++){
        if(!has_father[i]){
            root = i;
            break;
        }
    }
    //从根结点开始往下走
    dfs(root);
    return 0;
}