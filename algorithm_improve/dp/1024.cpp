#include <iostream>

using namespace std;

int f[20010],a[32];

int main(){
    int v,n;
    cin >> v >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];

    for(int i = 1; i <= n; i++){
        for(int j = v; j >= a[i]; j--){
            f[j] = max(f[j],f[j-a[i]] + a[i]);
        }
    }
    cout << v - f[v];
    return 0;
}