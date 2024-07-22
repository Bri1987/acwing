#include <iostream>

using  namespace std;

const int N = 20,M = 3010;
long long a[N],f[M];

int main(){
    int n,m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        cin >> a[i];

    f[0] = 1;
    for(int i = 1; i <= n; i++){
        for(int j = a[i]; j <= m; j++){
            f[j] += f[j-a[i]];
        }
    }
    cout << f[m];
    return 0;
}