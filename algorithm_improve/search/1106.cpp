#include <iostream>

using namespace std;
const int N = 1010;
int n;

int a[N][N];
bool st[N][N];

int dx[8] = {1,0,-1,0,1,1,-1,-1};
int dy[8] = {0,1,0,-1,1,-1,-1,1};

// 不是很懂为什么作为全局变量ok，但是作为引用传参会超内存
// 本题递归调用太多，还是建议用队列bfs
bool is_high,is_low;

void dfs(int row, int col){
    for(int i = 0; i < 8; i++){
        int x = row + dx[i], y = col + dy[i];
        if(x >= 1 && x <= n && y >= 1 && y <= n){
            if(a[row][col] < a[x][y])
                is_high = false;
            else if(a[row][col] > a[x][y])
                is_low = false;
            else {
                if(!st[x][y]){
                    st[x][y] = true;
                    dfs(x,y);
                }
            }
        }
    }
}

int main(){
    cin >> n;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            cin >> a[i][j];
    int high = 0, low = 0;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++){
            if(!st[i][j]){
                is_high = true, is_low = true;
                st[i][j] = true;
                dfs(i,j);
                if(is_high) high++;
                if(is_low)  low++;
            }
        }
    cout << high << " " << low << endl;
    return 0;
}