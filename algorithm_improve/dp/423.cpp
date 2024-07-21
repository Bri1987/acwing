#include <iostream>

using namespace std;
const int N = 1010;
int v[N],f[N],w[N];

int main(){
    int total,n;
    cin >> total >> n;
    for(int i = 1; i <= n; i++){
        cin >> v[i] >> w[i];
    }

    for(int i = 1; i <= n; i++){
        for(int j = total; j >= v[i]; j--){
            f[j] = max(f[j],f[j-v[i]]+w[i]);
        }
    }
    cout << f[total];
    return 0;
}