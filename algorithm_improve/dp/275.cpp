#include <iostream>

using namespace std;

const int N = 55;

int w[N][N], f[N][N][N];

/*
走两遍路线，求最大和
可以看作两个人一起从头走到尾，求最大和
走过的路的数可以被取走，为求最大值，视作必须取走

我们将i1，j1，i2，j2四维状态存储dp数组。
利用之前的观察，我们只需要记录步数k(k = i + j， 要保证同步，即i1+j1始终= i2+j2)与i坐标，就可以推出j坐标
so 可以把dp数组降维为k,i1,i2的三维状态

怎么处理数被取走不重复取？ dp如果去改变原地图，会很复杂
观察发现：
因为只能走右 or 走下， 则甲和乙到达ij时，步数必然相同
so，判断路线交叉，只需要在dp时，判断甲和乙的i坐标是否重叠
因为i如果重叠，j一定重叠
反之亦然，如果i不重叠，j一定不重叠。一定不重叠
*/

int main()
{
    int m,n;
    cin >> m >> n;
    for(int i = 1; i <= m; i++)
        for(int j = 1; j <= n; j++)
            cin >> w[i][j];

    // 初始f状态就是全为0
    for (int i1 = 1; i1 <= m; i1 ++ )
        for (int j1 = 1; j1 <= n; j1 ++ )
            for (int i2 = 1; i2 <= m; i2 ++ )
            {
                int j2 = i1 + j1 - i2;
                if (j2 >= 1 && j2 <= n)
                {
                    // 这一步是 1要右2要下，1右2右
                    int tmp = max(f[i1 - 1][j1][i2], f[i1 - 1][j1][i2 - 1]);
                    // 1下2下
                    tmp = max(tmp, f[i1][j1 - 1][i2]);
                    // 1下2右
                    tmp = max(tmp, f[i1][j1 - 1][i2 - 1]);
                    // 前面上一步的状态算完max之后，再加上当次的状态
                    f[i1][j1][i2] = tmp + w[i1][j1] + w[i2][j2];
                    // i1=i2则一定走到重复点了, 减去一次重复计算
                    if (i1 == i2) f[i1][j1][i2] -= w[i1][j1];
                }
            }

    cout << f[m][n][m] << endl;

    return 0;
}