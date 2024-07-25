#include <iostream>
#include <queue>
#include <cstring>

using namespace std;
const int N = 1010;
char a[N][N];
int d[N][N];

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};

int main(){
    int n,m;
    cin >> n >> m;
    memset(d,-1,sizeof d);
    queue<pair<int,int>> q;
    // 注意从1的位置开始发散，而不是从0 !
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++){
            cin >> a[i][j];
            if(a[i][j] == '1'){
                d[i][j] = 0;
                q.push({i,j});
            }
        }

    while(!q.empty()){
        auto [row, col] = q.front();
        q.pop();

        for(int i = 0; i < 4; i++){
            int x = row + dx[i], y = col + dy[i];
            if(x >= 1 && x <= n && y >= 1 && y <= m && d[x][y] == -1){
                d[x][y] = d[row][col] + 1;
                q.emplace(x,y);
            }
        }
    }

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cout << d[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}