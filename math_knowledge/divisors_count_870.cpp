#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = 1e9 + 7;

//如果 N = p1^c1 * p2^c2 * ... *pk^ck
//约数个数： (c1 + 1) * (c2 + 1) * ... * (ck + 1)

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
    for(auto i : hash) ans = ans*(i.second + 1) % mod;
    cout << ans;
    return 0;
}