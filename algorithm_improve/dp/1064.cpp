#include <iostream>
#include <vector>

using namespace std;
int n,k;

const int N = 12, K = 150, S = 1 << N;
// 前i行放j个国王，第i行的状态是s
long long f[N][K][S];
vector<int> states;
int cnt[S];   // 每个合法状态包含1(国王)的个数
vector<int> trans[S];

// 判定一个state是不是合法状态, 即不能有相邻1
bool check(int state){
    if(((state << 1) & state) != 0)
        return false;
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
    cin >> n >> k;

    // 预处理
    // 1. 所有合法的状态, 计算这个状态包含国王的数量
    for(int i = 0; i < 1 << n; i++){
        if(check(i)){
            states.push_back(i);
            cnt[i] = popCount(i);
        }
    }

    // 2. 计算这个状态a可以由哪些状态b转移到
    for(int i = 0; i < states.size(); i++){
        for(int j = 0; j < states.size(); j++){
            int a = states[i], b = states[j];
            // a & b : 上下两行没有在同一个index的国王
            // check(a | b) : 上下两行没有错位相邻的
            if((a & b) == 0 && check(a | b)){
                // 注意这里是用的下标, 因为后面也用的下标
                trans[i].push_back(j);
            }
        }
    }

    // 3. 正式dp
    f[0][0][0] = 1;
    for(int i = 1; i <= n+1; i++){
        for(int j = 0; j <= k; j++){
            for(int h = 0; h < states.size(); h++){
                int cntH = cnt[states[h]];
                if(j >= cntH){
                    // 看这个state能由哪些state转移而来
                    for(auto preState : trans[h])
                        f[i][j][h] += f[i-1][j-cntH][preState];
                }
            }
        }
    }
    // 多算一层, 我们假设存在第n+1行，但是第n+1行完全没有摆, 这样就不用算和
    cout << f[n+1][k][0] << endl;
    return 0;
}