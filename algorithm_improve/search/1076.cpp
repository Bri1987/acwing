#include <iostream>
#include <queue>
#include <cstring>

using namespace std;
const int N = 1010;
int a[N][N];
pair<int,int> prev_[N][N];
int d[N][N];

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};

int main(){
    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> a[i][j];

    memset(d,-1,sizeof d);
    d[0][0] = 0;
    queue<pair<int,int>> q;
    q.push({0,0});
    while(q.size()) {
        auto [row, col] = q.front();
        q.pop();

        for(int i = 0; i < 4 ;i++){
            int x = row + dx[i], y = col + dy[i];
            if(x >= 0 && x < n && y >= 0 && y < n && a[x][y] != 1 && d[x][y] == -1){
                d[x][y] = d[row][col] + 1;
                prev_[x][y] = {row, col};
                q.push({x,y});

                if(x == n-1 && y == n-1){
                    break;
                }
            }
        }
    }
    auto [row, col] = prev_[n-1][n-1];
    vector<pair<int,int>> vec;
    vec.emplace_back(n-1,n-1);
    while(!(row == 0 && col == 0)){
        vec.emplace_back(row,col);
        auto [tmp1, tmp2] = prev_[row][col];
        row = tmp1, col = tmp2;
    }
    cout << 0 << " " << 0 << endl;
    for(int i = vec.size()-1; i >= 0; i--){
        cout << vec[i].first << " " << vec[i].second << endl;
    }
    return 0;
}