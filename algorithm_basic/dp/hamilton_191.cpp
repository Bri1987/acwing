#include <iostream>
#include <cstring>

using namespace std;
const int N = 21, M = 1 << 21;
//1. 哪些点被用过（第一维）i
//2. 现在在哪个点上（第二维）j
int f[M][N];
int w[N][N];

int main(){
    int n;
    cin >> n;
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < n; j++){
            cin >> w[i][j];
        }
    }

    memset(f, 0x3f, sizeof f);
    //起点为0
    f[0][0] = 0;
    for(int i = 0; i < (1 << n); i++){
        for(int j = 0; j < n; j++){
            //先保证当前待着的点是已经被用过的
            if((i >> j) & 1){
                for(int k = 0; k < n; k++){
                    //要保证中间状态是走过的，走过才能算main
                    if((i >> k) & 1){
                        f[i][j] = min(f[i][j], f[i - (1 << j)][k] + w[k][j]);
                    }
                }
            }
        }
    }
    //所有点都走过，当前即结尾为n-1
    cout << f[(1 << n)-1][n-1] << endl;
    return 0;
}