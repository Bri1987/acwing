#include <iostream>

using namespace std;

int n;
const int N = 210;
int d[N][N];

//多源汇最短路
void floyd()
{
    for (int k = 1; k <= n; k ++ )
        for (int i = 1; i <= n; i ++ )
            for (int j = 1; j <= n; j ++ )
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}

int main(){
    int m,k;
    int x,y,z;

    cin >> n >> m >> k;
    //初始化
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            if(i == j) d[i][j] = 0;
            else d[i][j] = 0x3f3f3f3f;

    while(m--) {
        cin >> x >> y >> z;
        //! 注意保存最小的边
        //直接存入d数组
        d[x][y] = min(d[x][y], z);
    }

    floyd();

    while(k--) {
        cin >> x >> y;
        if(d[x][y] > 0x3f3f3f3f/2) puts("impossible");
            //由于有负权边存在所以约大过INF/2也很合理
        else cout << d[x][y] << endl;
    }
    return 0;
}