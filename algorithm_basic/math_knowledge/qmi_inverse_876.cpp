#include <iostream>

using namespace std;
typedef long long LL;

// a > b
LL gcd(LL a, LL b)
{
    return b ? gcd(b, a % b) : a;
}

//求a^b^ % p
LL qmi(LL a, LL b, LL p){
    LL res = 1;
    LL t = a;
    while (b){
        if(b&1) res = res * t % p;
        t = t * t % p;
        b >>= 1;
    }
    return res;
}

int main(){
    int m;
    cin >> m;
    while (m--){
        LL a,p;
        cin >> a >> p;
        //先用欧几里得判断是不是互质
        LL max = a > p ? a : p;
        LL min = a < p ? a : p;
        if(gcd(max,min) > 1){
            puts("impossible");
            continue;
        }

        //如果p是质数, 用快速幂求逆元, 求a^p-2^ mod p
        cout << qmi(a,p-2,p) << endl;
    }
    return 0;
}