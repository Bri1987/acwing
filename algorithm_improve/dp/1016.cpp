#include <iostream>

using namespace std;

const int N = 1010;
int f[N],a[N];

int main(){
    int n;
    cin >> n;
    int res = 0;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        f[i] = a[i];
        res = max(f[i],res);
    }

    for(int i = 2; i <= n; i++){
        int tmp = f[i];
        for(int j = 1; j < i; j++){
            if(a[i] > a[j]){
                f[i] = max(f[i],tmp + f[j]);
                res = max(f[i],res);
            }
        }
    }
    cout << res;
    return 0;
}