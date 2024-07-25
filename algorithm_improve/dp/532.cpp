#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 110;
int a[N],f[25010];

// 比如排序后1 3 4 7，演变为3能不能用1表示出来，4能不能用1 3表示出来，那其实就是完全背包，每次外层循环，每当走到一个更大的新数时，如果此时f[a[i]] = 0，
// 说明比它小的都表示不出这个数，那么它就必须保留

int main(){
    int m;
    cin >> m;
    while(m--){
        int n;
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        memset(f,0,sizeof f);
        sort(a+1, a+n+1);
        int res = 0;
        f[0] = 1;
        for(int i = 1; i <= n; i++){
            // 这个数不能被前面更小的数表示出来，f[a[i]] = 0, 说明它必须在
            if(!f[a[i]])
                res++;
            for(int j = a[i]; j <= a[n]; j++){
                f[j] += f[j-a[i]];
            }
        }
        cout << res << endl;
    }
    return 0;
}