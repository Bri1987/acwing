#include <iostream>
#include <limits>

using namespace std;

const int N = 510, INF=0x3f3f3f3f;
int f[N][N];
int w[N][N];

int n;

int main(){
    cin >> n;

    for(int i=1;i<=n;i++){
        for(int j=0;j<=i+1;j++){          //因为有负数，所以应该将两边也设为-INF
            f[i][j] = -INF;
        }
    }

    for(int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            cin >> w[i][j];
        }
    }

    //注意初始为-INF
    int res = -INF;
    //这里把第一层单独提出来的原因是，如果不提f[0][0]..默认为负无穷，在下面的max遇到f[0]时会出错，要使得之前层的f有定义才行
    f[1][1] = w[1][1];
    for(int i = 2; i <= n; i++){
        for(int j = 1; j <= i; j++){
            f[i][j] = max(f[i-1][j] , f[i-1][j-1]) + w[i][j];
            if(i == n)
                res = max(res, f[i][j]);
        }
    }
    cout << res << endl;

    //倒序,这样就只有顶这一个终点, 从最后一层开始倒着走
//    for(int i = n; i >= 1; i--){
//        for(int j = i; j >= 1; j--){
//            f[i][j] = max(f[i+1][j], f[i+1][j+1]) + f[i][j];
//        }
//    }
//    cout<<f[1][1]<<endl;
    return 0;
}