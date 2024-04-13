#include <iostream>

using namespace std;
typedef long long LL;

const int p = 1e9+7;

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

int main(){
    int n;
    cin >> n;
    //计算C 2n n / (n+1)
    int res = C(2*n,n);
    //!! 注意求 C(2*n,n) / (n+1) 也必须用逆元！！a/b mod p与a mod p / b mod p是不相等的 ，后面的是对的
    //!! qmi之前一定记得扩展成LL
    res = res * (LL)qmi(n+1, p - 2, p) % p;
    cout << res << endl;
    return 0;
}