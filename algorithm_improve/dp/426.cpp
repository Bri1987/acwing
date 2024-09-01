#include <iostream>
#include <cstdio>
using namespace std;
const int N = 3e4 + 10,M = 30;
int v[M], w[M];
int f[M][N];
int n, m;

int main() {
    cin >> m >> n;
    for(int i = 1; i <= n; i++)
        cin >> v[i] >> w[i];
    for(int i = 1; i <= n; i++)
    {
        for(int j = 0; j <= m; j++)
        {
            f[i][j] = f[i-1][j];
            if(j>=v[i]) f[i][j] = max(f[i][j], f[i-1][j-v[i]]+v[i]*w[i]);
        }
    }
    cout << f[n][m] << endl;
    return 0;
}