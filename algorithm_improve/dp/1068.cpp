#include <iostream>
#include <cstring>

using namespace std;
const int N = 210;
int f[N][N];

int w[N];
int sum[N];

int n;

int getMod(int x){
    if(x == n)
        return x;
    return x % n;
}

int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> w[i];
        sum[i] = w[i] + sum[i-1];
    }

    if(n == 1){
        cout << 0 << endl << 0 << endl;
        return 0;
    }

    memset(f,0x3f,sizeof f);
    // ! 注意这里初始化值为0, 不然算len=1的时候会加两次
    for(int i = 1; i <= n; i++)
        f[i][i] = 0;

    // 认为合并1 2两堆间隔是1, 如果合并1 2 3 4四堆, 那间隔最多是3
    int mi = 1e9;
    for(int len = 1; len <= n-1; len++){
        for(int i = 1; i <= n; i++){
            int valSum;
            if(i + len > n){
                valSum = sum[getMod(i+len)] + sum[n] - sum[i-1];
            } else
                valSum = sum[i+len] - sum[i-1];
            for(int k = i; k <= i + len - 1; k++){
                f[i][getMod(i+len)] = min(f[i][getMod(i+len)], valSum + f[i][getMod(k)] + f[getMod(k+1)][getMod(i+len)]);
                // cout << i << " " << getMod(i+len) <<"," << f[i][getMod(i+len)] << endl;
                if(len == n-1)
                    mi = min(mi, f[i][getMod(i+len)]);
            }
        }
    }
    cout << mi << endl;

    // ---------------------max
    memset(f,-1,sizeof f);
    for(int i = 1; i <= n; i++)
        f[i][i] = 0;

    // 认为合并1 2两堆间隔是1, 如果合并1 2 3 4四堆, 那间隔最多是3
    int mx = 0;
    for(int len = 1; len <= n-1; len++){
        for(int i = 1; i <= n; i++){
            int valSum;
            if(i + len > n){
                valSum = sum[getMod(i+len)] + sum[n] - sum[i-1];
            } else
                valSum = sum[i+len] - sum[i-1];
            for(int k = i; k <= i + len - 1; k++){
                f[i][getMod(i+len)] = max(f[i][getMod(i+len)], valSum + f[i][getMod(k)] + f[getMod(k+1)][getMod(i+len)]);
                // cout << i << " " << getMod(i+len) <<"," << f[i][getMod(i+len)] << endl;
                if(len == n-1)
                    mx = max(mx, f[i][getMod(i+len)]);
            }
        }
    }
    cout << mx << endl;
    return 0;
}