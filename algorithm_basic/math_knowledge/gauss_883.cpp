#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 110;
double a[N][N];
int n;
const double eps = 1e-6;

// a[N][N]是增广矩阵
int gauss()
{
    int c, r;
    for (c = 0, r = 0; c < n; c ++ )
    {
        int t = r;
        for (int i = r; i < n; i ++ )   //1. 找到绝对值最大的行
            if (fabs(a[i][c]) > fabs(a[t][c]))
                t = i;

        if (fabs(a[t][c]) < eps) continue;

        //前面的col都变成0了，从i=c开始的col就行
        for (int i = c; i <= n; i ++ ) swap(a[t][i], a[r][i]);      //2. 将绝对值最大的行换到最顶端
        //因为一直需要顶列的值来除，所以从右往左
        for (int i = n; i >= c; i -- ) a[r][i] /= a[r][c];      //3. 将当前行的首位变成1
        for (int i = r + 1; i < n; i ++ )       //4. 用当前行将下面所有的列消成0 , 消左下角
            //已经是0就不用操作了
            if (fabs(a[i][c]) > eps)
                for (int j = n; j >= c; j -- )
                    //由于当前行首位已经是1，a[i][c]是需要减的倍数，a[r][j]是处理的首行对应列的值
                    a[i][j] -= a[r][j] * a[i][c];

        r ++ ;       //顶端row后移
    }

    if (r < n)
    {
        for (int i = r; i < n; i ++ )
            //前面都被消成0了，右值若不为0就是无解
            if (fabs(a[i][n]) > eps)
                return 2; // 无解
        return 1; // 有无穷多组解
    }

    //消右上角
    for (int i = n - 1; i >= 0; i -- )
        //j为什么从i + 1开始，因为如果最终是一个完美矩阵的话，我们呈对角线分布
        for (int j = i + 1; j < n; j ++ )
            //注意这里是倒着看的，右值是最终答案
            a[i][n] -= a[i][j] * a[j][n];

    return 0; // 有唯一解
}

int main(){
    cin >> n ;
    for(int i = 0; i < n; i++)
        //注意是增广矩阵，j要多1
        for(int j = 0; j < n + 1;j ++)
            cin >> a[i][j];
    int t = gauss();
    if(t == 1){
        cout << "Infinite group solutions" << endl;
    } else if(t == 2){
        cout << "No solution" << endl;
    }else{
        for (int i = 0; i < n; i ++ )
            //注意右值是答案
            printf("%.2lf\n",a[i][n]);
    }
    return 0;
}