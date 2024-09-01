#include <iostream>
#include <vector>

using namespace std;
const int N = 14, S = 1 << N, MOD = 1e8;
int g[N][N];
int m,n;

// 每一行的合法state
vector<int> states[S];
vector<int> trans[N][S];

long long f[N][S];

// 判定一个state是不是合法状态, 即不能有相邻1, 并且都在好的土壤
bool check(int row, int state){
    if(((state << 1) & state) != 0)
        return false;
    if(row >= 1){
        for(int i = 0; i < n; i++){
            if((state >> i) & 1 && g[row][i+1] == 0)
                return false;
        }
    }
    return true;
}

int main(){
    cin >> m >> n;
    for(int i = 1; i <= m; i++)
        for(int j = 1; j <= n; j++)
            cin >> g[i][j];

    // 预处理每一行允许的状态

    for(int i = 0; i <= m; i++){
        for(int j = 0; j < 1 << n; j++){
            if(check(i,j)){
                states[i].push_back(j);
            }
        }
    }
    // 每一行的哪个状态能由什么状态转移而来
    for(int i = 1; i <= m; i++) {
        for(int j = 0; j < states[i].size(); j++){
            for(int k = 0; k < states[i-1].size(); k++){
                int a = states[i][j], b = states[i-1][k];
                if((a & b) == 0)
                    trans[i][j].push_back(k);
            }
        }
    }

    f[0][0] = 1;
    for(int i = 1; i <= m+1; i++){
        for(int j = 0; j < states[i].size(); j++){
            for(auto b : trans[i][j]){
                f[i][j] = (f[i][j] + f[i-1][b]) % MOD;
            }
        }
    }

    long long res = 0;
    for(int i = 0; i < states[m].size(); i++){
        res = (res + f[m][i]) % MOD;
    }
    cout << res;
    return 0;
}