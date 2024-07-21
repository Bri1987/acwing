#include <iostream>

using namespace std;

const int N = 1010, M = 510, K = 110;

// 用n个精灵球和m点体力
int f[N][M];
int a[K],b[K];

int main(){
    int v,m,n;
    cin >> v >> m >> n;
    for(int i = 1; i <= n; i++){
        cin >> a[i] >> b[i];
    }

    for(int i = 1; i <= n; i++){
        for(int j = v; j >= a[i]; j--){
            // 注意这个维度，k从m-1开始，>= b[i]；而不能从m开始，> b[i]，因为比如此时m是100而正k=50，50其实不是皮卡丘生命用尽，还是应该处理k=b[i]的情况，
            // 只要处理最后一次皮卡丘k=100的情况不出现就行了，所以从m-1开始
            for(int k = m-1; k >= b[i]; k--){
                f[j][k] = max(f[j][k], f[j-a[i]][k-b[i]] + 1);
            }
        }
    }

    int res = 0, ans = m;
    for(int i = 0; i <= m; i++){
        if(f[v][i] > res){
            res = f[v][i];
            ans = m - i;
        }
    }
    cout << res << " " << ans;
    return 0;
}

