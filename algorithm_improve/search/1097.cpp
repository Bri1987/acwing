#include <iostream>

using namespace std;
const int N = 1010;

int n,m;
char a[N][N];

int dx[8] = {1,0,-1,0,1,1,-1,-1};
int dy[8] = {0,1,0,-1,1,-1,-1,1};

void dfs(int row, int col){
    for(int i = 0; i < 8; i++){
        if(row + dx[i] >= 1 && row+dx[i] <= n && col+dy[i] >= 1 && col+dy[i] <= m){
            if(a[row + dx[i]][col+dy[i]] == 'W'){
                // flood fill, 直到走到找不到W为止
                a[row + dx[i]][col+dy[i]] = '.';
                dfs(row + dx[i],col+dy[i]);
            }
        }
    }
}

int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cin >> a[i][j];
        }
    }

    int res = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(a[i][j] == 'W'){
                dfs(i,j);
                res++;
            }
        }
    }
    cout << res;
    return 0;
}