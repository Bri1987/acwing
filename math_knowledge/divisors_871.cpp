#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = 1e9 + 7;

//如果 N = p1^c1 * p2^c2 * ... *pk^ck
//约数之和： (p1^0 + p1^1 + ... + p1^c1) * ... * (pk^0 + pk^1 + ... + pk^ck)

int main(){
    int n,x;
    LL ans = 1;
    //存p1和对应的c1
    unordered_map<int,int> hash;
    cin >> n;
    while(n--){
        cin >> x;
        for(int i = 2;i <= x/i; ++i){
            while(x % i == 0){
                x /= i;
                //增加p1对应的c1
                hash[i] ++;
            }
        }
        if(x > 1) hash[x] ++;
    }
    for(auto ele : hash) {
        //注意用LL，经常记得mod
        LL tmp = 1;
        //LL prev = 1;
        for(int i = 1 ; i <= ele.second; i++){
//            prev = ele.first * prev % mod;
//            tmp += prev % mod;
//            tmp = tmp % mod;
            //秦九韶算法
            tmp = (tmp * ele.first + 1) % mod;
        }
        ans = ans*tmp % mod;
    }
    cout << ans;
    return 0;
}