#include <iostream>

using namespace std;

const int N = 310;
int g[N][N], f[N][N];
bool st[N][N];

int n,m;
int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};

int dp(int x,int y){
    if(st[x][y])
        return f[x][y];
    st[x][y] = true;
    f[x][y] = 1;
    // 不知道哪个状态会先出来，以递归计算的形式存储下已经考虑计算过的dp
    // 这里用递归比循环方便，因为计算的顺序是不定的
    for(int i = 0; i < 4; i++){
        if(x + dx[i] <= n && x + dx[i] >= 1 && y + dy[i] <= m && y + dy[i] >= 1 && g[x][y] < g[x+dx[i]][y+dy[i]]){
            f[x][y] = max(f[x][y],dp(x+dx[i],y+dy[i]) + 1);
        }
    }
    return f[x][y];
}

int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            cin >> g[i][j];
    //从任何起点出发都有可能
    int mx = 0;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            mx = max(mx,dp(i,j));
    cout << mx;
    return 0;
}