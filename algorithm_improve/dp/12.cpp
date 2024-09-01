#include <iostream>
#include <vector>

using namespace std;
const int N = 1010, MOD = 1e9 + 7;
int f[N][N];
int v_[N], w_[N];

int n,v;

vector<int> vec;

// 注意这个和之前1013的区别是不是每一个元素都必须被选, 外面还要套一层选i的for循环
void dfs(int i, int mx, int cur_v) {
    if(cur_v == 0){
        return;
    }

    for(int j = i; j <= n; j++){
        for(int k = 0; k <= min(cur_v,cur_v-v_[j]); k++){
            if(f[j+1][k] + w_[j] == mx){
                mx -= w_[j];
                vec.push_back(j);
                dfs(j+1, mx, k);
                return;
            }
        }
    }
}

int main(){
    cin >> n >> v;
    for(int i = 1; i <= n; i++)
        cin >> v_[i] >> w_[i];

    // 因为后续dfs要从1开始, 所以这里是i是选从后往前数多少个元素
    for(int i = n; i >= 1; i--){
        for(int j = 0; j <= v; j++) {
            f[i][j] = f[i+1][j];
            if(j >= v_[i])
                f[i][j] = max(f[i][j], f[i+1][j-v_[i]] + w_[i]);
        }
    }

    // cout << f[1][v] << endl;
    dfs(1,f[1][v],v);

    for(int i = 0; i < vec.size(); i++)
        cout << vec[i] << " ";
    return 0;
}
