#include <iostream>
#include <queue>
using namespace std;
const int N = 110;

//记录迷宫点位0 1的二维数组，其中走过的点在后面会被逐渐标为1(即走过的点不能再走),
// 因为是bfs，一定是距离从小到大搜的，所以如果走到之前被搜过置为1的点的话，那么!!**之前第一次走到这的，一定是最小或与当前相等长的路径**
int maze[N][N];
//记录与起点的距离, !!注意也是用数组
int d[N][N];
int n,m;
queue<pair<int,int>> q;

int main(){
    cin >> n >> m;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> maze[i][j];
    //将初始点位放入队列
    q.emplace(0,0);
    //!!注意可以用数组模拟左右上下
    int dx[4]={-1,1,0,0};
    int dy[4]={0,0,-1,1};
    while (!q.empty()){
        auto [x,y] = q.front();
        q.pop();
        if(x == n - 1 && y == m - 1){
            cout << d[n-1][m-1];
            return 0;
        } else{
            for(int i = 0; i < 4; i++){
                if(x + dx[i] >=0 && x + dx[i] <= n-1 && y + dy[i] >= 0 && y + dy[i] <= m-1 && maze[x + dx[i]][y + dy[i]] == 0){
                    q.emplace(x + dx[i],y + dy[i]);
                    maze[x + dx[i]][y + dy[i]] = 1;
                    d[x + dx[i]][y + dy[i]] = d[x][y] + 1;
                }
            }
        }
    }
}