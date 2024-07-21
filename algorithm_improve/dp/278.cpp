#include <iostream>

using namespace std;

const int N = 110, M = 10010;
int f[M],a[N];

int main(){
    int n,m;
    cin >> n >> m;
    for(int i = 1; i <= n ;i++)
        cin >> a[i];

    // 注意这个初始化!
    f[0] = 1;
    for(int i = 1; i <= n ;i++){
        for(int j = m; j >= a[i] ;j--){
            // 选择这个数是一种新选法，不要+1
            f[j] += f[j-a[i]];
        }
    }
    cout << f[m];
    return 0;
}