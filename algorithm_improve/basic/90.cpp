#include <iostream>

using namespace std;

//例：计算 3*7 = 3*(1+2+4)
//
//7的二进制 111
//3*(2^0)=3
//3*(2^1)=6
//3*(2^2)=12
//
//结果=3+6+12=21

int main(){
    long long a,b,p;
    cin >> a >> b >> p;
    long long res = 0;
    while(b){
        if(b & 1)   res = (res + a) % p;
        a = (2*a) % p;
        b >>= 1;
    }
    cout << res;
    return 0;
}