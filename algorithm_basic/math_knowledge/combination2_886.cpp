#include <iostream>

using namespace std;
const int N = 100010, mod = 1e9+7;
typedef long long LL;

int fact[N], infact[N];

int qmi(int a, int k, int p)    // 快速幂模板
{
    int res = 1;
    while (k)
    {
        if (k & 1) res = (LL)res * a % p;
        a = (LL)a * a % p;
        k >>= 1;
    }
    return res;
}

int main(){
    int m;
    cin >> m;
    fact[0] = infact[0] = 1;
    //预处理求的是i的阶乘mod值和i的阶乘逆元
    for(int i = 1; i <= N; i++){
        fact[i] = (LL)fact[i - 1] * i % mod;
        infact[i] = (LL)infact[i - 1] * qmi(i,mod - 2,mod) % mod;
    }
    while (m--){
        int a,b;
        cin >> a >> b;
        //注意有2个乘就mod一下防溢出
        cout << ((LL)fact[a] * (LL)infact[a-b]) % mod * (LL)infact[b] % mod << endl;
    }
    return 0;
}