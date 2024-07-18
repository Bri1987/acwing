#include <iostream>
using namespace std;

// 稍微优化一下，全部直接dfs的话会报错
int dfs(int n, int m){
    if(n == m)
        return 1;
    int mi = min(n,m);
    int mx = max(n,m);
    return 1 + dfs(mi, mx - mi);
}

int main(){
    int n,m;
    cin >> n >> m;
    int mi = min(n,m);
    int mx = max(n,m);
    int basic = 0;
    if(mx > 2 * mi) {
        basic = mx / mi;
        if(mx % mi != 0)
            cout << basic + dfs(mi, mx % mi);
        else
            cout << basic << endl;
    } else
        cout << dfs(n,m);
    return 0;
}
