#include <iostream>

using namespace std;
const int N = 1010, V = 110, M = 110;

int v[N],m[N],w[N];
int f[V][M];

int main(){
    int n, totalV, totalM;
    cin >> n >> totalV >> totalM;
    for(int i = 1; i <= n; i++){
        cin >> v[i] >> m[i] >> w[i];
    }

    for(int i = 1; i <= n; i++){
        for(int j = totalV; j >= v[i]; j--){
            for(int k = totalM; k >= m[i]; k--){
                f[j][k] = max(f[j][k], f[j-v[i]][k-m[i]]+w[i]);
            }
        }
    }
    cout << f[totalV][totalM];
    return 0;
}