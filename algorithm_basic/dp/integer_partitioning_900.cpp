#include <iostream>

using namespace std;

const int N = 1010;
int f[N];

const int mod = 1e9+7;

int main(){
    int n;
    cin >> n;

    for(int i = 0; i <= n; i++)  f[0] = 1; // 每一个都有1种解法（都不选）

    //前i个数，组成数n , 值为整数划分方法数
//    for(int i = 1; i <= n; i++)
//        for(int j = 1; j <= n; j++){
//            //k=0 : 前i-1个数就能组成 j，直接加入这么多可能, 因为此时在原先前i-1个数的基础上，再补上一个1即可
//            //k 提前减去k个i的所有可能的情况加起来
//            for(int k = 0; k * i <= j; k++) {
//                f[i][j] = (f[i][j] + f[i-1][j-k*i] % mod) % mod;
//            }
//        }

    //同完全背包的这个优化
//    for(int i = 1; i <= n; i++)
//        for(int j = 1; j <= n; j++){
//            f[i][j] = f[i-1][j] % mod;
//            if(j >= i)
//                f[i][j] = (f[i][j] + f[i][j-i] % mod) % mod;
//
//        }

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++){
            if(j >= i)
                f[j] = (f[j] + f[j-i] % mod) % mod;

        }

    cout << f[n] << endl;
    return 0;
}