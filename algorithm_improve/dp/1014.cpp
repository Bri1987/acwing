#include <iostream>

const int N = 1010;

using namespace std;

int f[N][2];   // 1代表已经决定开始往下走
int h[N];

int main(){
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> h[i];
        f[i][0] = 1;
        f[i][1] = 1;
    }

    int res = 1;
    for(int i = 2; i <= n; i++){
        for(int j = 1; j < i ; j++){
            if(h[j] < h[i]){
                f[i][0] = max(f[i][0],f[j][0] + 1);
            } else if(h[j] > h[i]){
                f[i][1] = max(f[i][1],f[j][0] + 1);
                f[i][1] = max(f[i][1],f[j][1] + 1);
            }
            res = max(res,f[i][0]);
            res = max(res,f[i][1]);

        }
    }
    cout << res;
    return 0;
}