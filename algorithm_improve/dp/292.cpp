#include <iostream>
#include <vector>

using namespace std;
int n,m;
const int N = 110, M = 12, S = 1 << M;
char g[N][M];

vector<int> states[N];
int cnt[S];
int f[2][S][S];    // 做了前i行，i行的状态是j, i-1行状态是k, 能放下多少个

// 判定一个state是不是合法状态, 即不能有相邻2, 并且都在好的土壤
bool check(int row, int state){
    if(((state << 1) & state) != 0)
        return false;
    if(((state << 2) & state) != 0)
        return false;
    if(row >= 1){
        for(int i = 0; i < m; i++){
            if((state >> i) & 1 && g[row][i+1] == 'H')
                return false;
        }
    }
    return true;
}

int low_bit(int x){
    return x & -x;
}
int popCount(int x){
    int res = 0;
    while(x){
        res++;
        x -= low_bit(x);
    }
    return res;
}

int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            cin >> g[i][j];

    for(int i = 0; i <= n; i++){
        for(int j = 0; j < 1 << m; j++){
            if(check(i, j)){
                states[i].push_back(j);
                cnt[j] = popCount(j);
            }
        }
    }

    int res = 0;
    for(int i = 1; i <= n; i++){
        // 第i行状态
        for(int j = 0; j < states[i].size(); j++){
            if(i == 1){
                // 不用看一定合法
                f[1][j][0] = cnt[states[1][j]];
                res = max(res, f[1][j][0]);
            } else {
                // 第i-1行状态
                for(int k = 0; k < states[i-1].size(); k++){
                    // 如果是第2行, 就只看ab
                    int a = states[i][j], b = states[i-1][k];
                    if(i == 2){
                        if((a & b) != 0)
                            continue;
                        f[i & 1][j][k] = cnt[states[2][j]] + cnt[states[1][k]];
                        res = max(res, f[i&1][j][k]);
                    } else {
                        for(int h = 0; h < states[i-2].size(); h++){
                            int c = states[i-2][h];
                            if((a & b) != 0 || (a & c) != 0 || (b & c) != 0)
                                continue;
                            f[i&1][j][k] = max(f[i&1][j][k], f[(i-1)&1][k][h] + cnt[states[i][j]]);
                            res = max(res, f[i&1][j][k]);
                        }
                    }
                }
            }
        }
    }
    cout << res;
    return 0;
}