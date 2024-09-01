#include <iostream>
#include <cstring>

using namespace std;

const int M = 1010;
int f[M][25][85];
int a[M], b[M], w[M];

int main(){
    int O,N;
    cin >> O >> N;
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i] >> b[i] >> w[i];
    }
    memset(f,0x3f,sizeof f);

    // 这里是看价值，所以初始为0，如果是看种数，就初始为1
    f[0][0][0] = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= O; j++){
            for(int k = 0; k <= N; k++){
                // 即使物品体积比j大，j - v < 0，也能选，等价于f[i - 1][0], 即一定选当前这个，那之前的就只用为0就行
                f[i][j][k] = min(f[i-1][j][k], f[i-1][max(0, j-a[i])][max(0, k-b[i])] + w[i]);
            }
        }
    }
    cout << f[n][O][N];
    return 0;
}