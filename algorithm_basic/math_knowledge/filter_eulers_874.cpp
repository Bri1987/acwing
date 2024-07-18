#include <iostream>

using namespace std;
typedef long long LL;

const int N = 1000010;
bool st[N];
int primes[N];
int euler[N];
int cnt;

int main(){
    int n;
    cin >> n;

    //记得1也有欧拉数
    euler[1] = 1;
    for(int i = 2; i <= n; i++){
        if(!st[i]){
            //是质数，质数的欧拉数是它自己/自己 * (自己-1)
            primes[cnt ++ ] = i;
            euler[i] = i - 1;
        }

        for(int j = 0; primes[j] <= n / i; j++){
            int t = primes[j] * i;
            st[t] = true;
            if(i % primes[j] == 0){
                euler[t] = euler[i] * primes[j];
                break;
            }
            euler[t] = euler[i] * (primes[j] - 1);
        }
    }

    LL res = 0;
    for(int i = 0; i < n; i++)
        res += euler[i];
    cout << res << endl;
    return 0;
}