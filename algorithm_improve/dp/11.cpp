#include <iostream>

using namespace std;
const int N = 1010, MOD = 1e9 + 7;
int f[N][N];
// 记录最优方案数, 记录f是走的哪一边, 不选i, g就继承g[i-1][j]; 选i, g就继承g[i-1][j-v_[i]];
// 如果都相同，就说明都是最优的, g就等于两者相加
int g[N][N];
int v_[N], w_[N];

int main(){
    int n,v;
    cin >> n >> v;
    for(int i = 1; i <= n; i++)
        cin >> v_[i] >> w_[i];
    // 注意初始化, 在前0个物品中选, 无论v是多少, 最优方案数都是不选为1
    for(int i = 0; i <= v; i++){
        g[0][i] = 1;
    }
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= v; j++){
            g[i][j] = g[i-1][j];
            f[i][j] = f[i-1][j];
            if(j >= v_[i]) {
                int value;
                value = f[i-1][j-v_[i]] + w_[i];
                if(f[i-1][j] < value){
                    g[i][j] = g[i-1][j-v_[i]];
                    f[i][j] = f[i-1][j-v_[i]] + w_[i];
                } else if(f[i-1][j] == value){
                    g[i][j] = (g[i-1][j] + g[i-1][j-v_[i]]) % MOD;
                }
            }
        }
    }
    cout << g[n][v];
    return 0;
}