#include <iostream>
#include <cstring>
#include <unordered_map>

using namespace std;

const int N = 110;
int h[N], e[N*2], ne[N*2], w[N*2], idx;
int n,k;

// 以i为根节点, 分配j个体积(允许保存j个树枝)
int f[N][N];

void add(int a,int b, int c){
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

void dfs(int root, int p){
    // 三重循环
    // 二叉: 有两个物品组, 分组背包
    // 1. 循环分组
    for(int i = h[root]; i != -1; i = ne[i]){
        int j = e[i];
        if(j != p){
            dfs(j,root);
            // 2. 循环分配给到这个root的体积数
            // ! 注意这个从大到小的顺序
            //j 是从大到小枚举的，因此一定用的是旧状态更新，肯定不会用到当前正在枚举的子树, 要用旧的f[root][a - b - 1], 不能让它先被更新
            // 这里和平常分组背包不同是因为需要的是左+右, 但是一次只能选择加左或加右, 所以姚保证这个顺序
            for(int a = k; a >= 0; a--){
                // 3. 循环决策
                //枚举体积预留一条连向父节点的边
                for(int b = 0; b <= a - 1; b++){
                    f[root][a] = max(f[root][a], f[root][a - b - 1] + f[j][b] + w[i]);
                }
            }
        }
    }
}

int main(){
    cin >> n >> k;

    memset(h,-1,sizeof h);
    for(int i = 0;i < n-1; i ++)
    {
        int a,b,c;
        cin >> a >> b >> c;
        add(a,b,c);
        add(b,a,c);
    }

    dfs(1,-1);
    // 以1为根节点的树, 分配k条边, 即k个体积
    cout << f[1][k];
    return 0;
}