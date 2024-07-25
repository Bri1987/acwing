#include <iostream>

using namespace std;

const int N = 55;

int a[N][N];
bool st[N][N];

int n,m;
// 对应墙，西北东南
int dx[4] = {-1,0,1,0};
int dy[4] = {0,-1,0,1};

int dfs(int row,int col){
    st[row][col] = true;
    int ssize = 1;
    for(int i = 0; i < 4; i++){
        if((a[row][col] >> i) & 1)
            continue;
        int x = row + dy[i], y = col + dx[i];
        if(x >= 1 && x <= n && y >= 1 && y <= m && !st[x][y]){
            ssize += dfs(x,y);
        }
    }
    return ssize;
}

int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            cin >> a[i][j];

    int res1 = 0, res2 = 1;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++){
            if(!st[i][j]){
                res2 = max(res2, dfs(i,j));
                res1++;
            }
        }
    cout << res1 << endl;
    cout << res2 << endl;
    return 0;
}