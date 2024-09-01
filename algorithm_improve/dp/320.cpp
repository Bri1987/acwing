#include <iostream>
#include <cstring>

using namespace std;
const int N = 110;
int f[N][N];
int tmp[N];

typedef struct Node{
    int head;
    int tail;
}Node;

Node w[N];

int n;

int getMod(int x){
    if(x == n)
        return x;
    return x % n;
}

int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> tmp[i];
    }
    for(int i = 1; i <= n; i++){
        if(i != n)
            w[i] = {tmp[i],tmp[i+1]};
        else
            w[i] = {tmp[n],tmp[1]};
    }

    // 注意也是初始化为0 !
    memset(f,-1,sizeof f);
    for(int i = 1; i <= n; i++)
        f[i][i] = 0;

    // 认为合并1 2两堆间隔是1, 如果合并1 2 3 4四堆, 那间隔最多是3
    int mx = 0;
    for(int len = 1; len <= n-1; len++){
        for(int i = 1; i <= n; i++){
            for(int k = i; k <= i + len - 1; k++){
                f[i][getMod(i+len)] = max(f[i][getMod(i+len)], w[i].head * w[getMod(i+len)].tail * w[getMod(k)].tail + f[i][getMod(k)] + f[getMod(k+1)][getMod(i+len)]);
                // cout << i << " " << getMod(i+len) <<"," << f[i][getMod(i+len)] << endl;
                if(len == n-1)
                    mx = max(mx, f[i][getMod(i+len)]);
            }
        }
    }
    cout << mx << endl;
    return 0;
}