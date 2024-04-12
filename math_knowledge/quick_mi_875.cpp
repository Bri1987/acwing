#include <iostream>

using namespace std;
typedef long long LL;

LL qmi(LL a,LL b,LL p){
    LL res = 1;
    LL t = a;
    while (b){
        if(b&1) res = (res * t) % p;
        //预处理
        t = (t * t) % p;
        b >>= 1;
    }
    return res;
}

int main(){
    int n;
    cin >> n;
    while (n--){
        LL a,b,p;
        cin >> a >> b >> p;
        cout << qmi(a,b,p) << endl;
    }
    return 0;
}