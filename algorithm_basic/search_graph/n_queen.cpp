#include <iostream>
using namespace std;
const int N = 20;

// bool数组用来判断搜索的下一个位置是否可行
// col列，dg对角线，udg反对角线
// g[N][N]用来存路径

int n;
char g[N][N];
bool col[N], dg[N], udg[N];

//u代表当前行
void dfs(int u) {
    // u == n 表示已经搜了n行，故输出这条路径
    if (u == n) {
        for (int i = 0; i < n; i ++ ) puts(g[i]);   // 等价于cout << g[i] << endl;
        puts("");  // 换行
        return;
    }

    // 枚举u这一行，搜索合法的列
    int x = u;
    for (int y = 0; y < n; y ++ )
        // 剪枝(对于不满足要求的点，不再继续往下搜索)
        //!! 对角线是通过截距唯一确定的
        //udg : y = -x + b  => b = x + y
        //dg : y = x + b => b = y - x ,但是可能是负数，于是+n保证为正
        if (!col[y] && !dg[y - x + n] && !udg[y + x]) {
            col[y] = dg[y - x + n] = udg[y + x] = true;
            g[x][y] = 'Q';
            dfs(x + 1);
            g[x][y] = '.';  // 恢复现场
            col[y] = dg[y - x + n] = udg[y + x] = false;
        }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i ++ )
        for (int j = 0; j < n; j ++ )
            g[i][j] = '.';

    dfs(0);

    return 0;
}