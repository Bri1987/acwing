#include <iostream>
#include <cstring>

using namespace std;

const int N = 22;
int n,m;
char g[N][N];
int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
bool st[N][N];

// m * n
int dfs(int row, int col) {
    int res = 1;
    st[row][col] = true;
    for(int i = 0; i < 4; i++){
        int x = row + dx[i], y = col + dy[i];
        if(x >= 1 && x <= m && y >= 1 && y <= n && !st[x][y] && g[x][y] == '.'){
            res += dfs(x,y);
        }
    }
    return res;
}

int main() {
    while(cin >> n >> m, n || m) {
        memset(st,0,sizeof st);
        int st_row, st_col;
        for(int i = 1; i <= m; i++)
            for(int j = 1; j <= n; j++) {
                cin >> g[i][j];
                if(g[i][j] == '@'){
                    st_row = i, st_col = j;
                }
            }
        cout << dfs(st_row,st_col) << endl;
    }
    return 0;
}