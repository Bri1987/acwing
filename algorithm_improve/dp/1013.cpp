#include <iostream>
#include <vector>

using namespace std;

const int N = 12,  M =17;
int a[N][M], f[N][M];
int n,v;

vector<pair<int,int>> vec;

// i : 1-n
// 状态转移，从后往前推, 因为可以分0, 所以可以一个一个推
// 当前关注的物品idx, 剩的价值, 最大的还可以分配的物品数
void dfs(int i, int mx, int cur_v) {
    if(i == 0)
        return;
    for(int k = 0; k <= cur_v; k++){
        if(f[i-1][k] + a[i][cur_v-k] == mx){
            mx -= a[i][cur_v-k];
            vec.push_back({i,cur_v-k});
            dfs(i-1, mx, k);
            return;
        }
    }
}


int main(){
    cin >> n >> v;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= v; j++){
            cin >> a[i][j];
        }
    }

    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= v; j++){
            for(int k = 0; k <= j; k++){
                f[i][j] = max(f[i][j], f[i-1][j]);
                f[i][j] = max(f[i][j], f[i-1][j-k]+a[i][k]);
                // cout << i << " "<< j << " " << k <<"," << f[i][j] << endl;
            }
        }
    }
    cout << f[n][v] << endl;

    dfs(n,f[n][v],v);
    for(int i = vec.size()-1; i >= 0; i--){
        cout << vec[i].first << " " << vec[i].second << endl;
    }
    return 0;
}