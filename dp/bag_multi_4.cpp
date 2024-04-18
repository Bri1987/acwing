#include <iostream>

using namespace std;

const int N = 1010;
int f[N][N];
int v[N],w[N],s[N];

int n,m;

int main(){
    cin >> n >> m;
    //注意这里是1-n，与后面方程匹配对应
    for(int i = 1; i <= n; i++){
        cin >> v[i] >> w[i] >> s[i];
    }

    for(int i = 1; i <=n ;i++){
        for(int j = 0; j <= m;j++){
            //f[i][j] = f[i-1][j];
            //只要k从0开始，后面那个就包含了原先的f[i-1][j]
            for(int k = 0; k*v[i] <= j && k <= s[i]; k++){
                f[i][j]= max(f[i][j],f[i-1][j-k*v[i]] + k*w[i]);
            }
        }
    }
    cout << f[n][m] << endl;
    return 0;
}