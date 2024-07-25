#include <iostream>
#include <queue>
using namespace std;
int dx[] = {-2,-1,1,2,2,1,-1,-2},dy[] = {1,2,2,1,-1,-2,-2,-1};
const int N = 160;
struct point {
    int x,y,step;
};
int n,m;
int sx,sy,ex,ey;
int g[N][N];
int bfs () {
    queue <point> q;
    q.push ({sx,sy,0});
    while (!q.empty ()) {
        point t = q.front ();
        q.pop ();
        if (t.x == ex && t.y == ey) return t.step;
        for (int i = 0;i < 8;i++) {
            int x = t.x+dx[i],y = t.y+dy[i];
            if (x < 1 || x > n || y < 1 || y > m) continue;
            if (g[x][y]) continue;
            q.push ({x,y,t.step+1});
            g[x][y] = 1;
        }
    }
    return -1;
}
int main () {
    cin >> m >> n;
    for (int i = 1;i <= n;i++) {
        for (int j = 1;j <= m;j++) {
            char ch;
            cin >> ch;
            if (ch == '*') g[i][j] = 1;
            else if (ch == 'K') sx = i,sy = j;
            else if (ch == 'H') ex = i,ey = j;
        }
    }
    cout << bfs () << endl;
    return 0;
}