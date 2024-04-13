#include <iostream>

using namespace std;
typedef long long LL;

int p;

int qmi(int a, int k, int pp)    // 快速幂模板
{
    int res = 1;
    while (k)
    {
        if (k & 1) res = (LL)res * a % pp;
        a = (LL)a * a % pp;
        k >>= 1;
    }
    return res;
}

int C(int a, int b)  // 通过定理求组合数C(a, b)
{
    if (a < b) return 0;

    LL x = 1, y = 1;  // x是分子，y是分母
    for (int i = a, j = 1; j <= b; i --, j ++ )
    {
        //完全直接用a! / (a-b)! * b!算的
        //走出循环时x就是a!/(a-b)!，y是b!
        x = (LL)x * i % p;
        y = (LL) y * j % p;
    }

    //用逆元解决不能直接除的问题
    return x * (LL)qmi(y, p - 2, p) % p;
}

//注意传入是LL
int lucas(LL a, LL b){
    if(a < p && b < p) return C(a,b);
    //左边不用进递归，右边还不确定除了之后是否 < p，还得进递归
    return (LL)C(a % p,b % p) * lucas(a / p, b / p) % p;
}

int main() {
    int m;
    cin >> m;
    while (m--){
        LL a,b;
        cin >> a >> b >> p;
        cout << lucas(a,b) << endl;
    }
    return 0;
}
