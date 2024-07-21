#include <iostream>

using namespace std;

const int N = 3010;
// f[i] [j]代表所有a[1 ~ i]和b[1 ~ j]中以b[j]结尾的公共上升子序列的集合；
int a[N],b[N],f[N][N];

int main(){
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    for(int i = 1; i <= n; i++)
        cin >> b[i];

    int res = 0;
//    for(int i = 1; i <= n; i++){
//        for(int j = 1; j <= n; j++){
//            f[i][j] = f[i-1][j];
//            if(a[i] == b[j]){
//                // 首先进不进循环或者if，都至少有1
//                int maxv = 1;
//                for(int k = 1; k < j; k++){
//                    // 保证是上升
//                    if(b[j] > b[k])
//                        maxv = max(maxv,f[i-1][k]+1);
//                }
//                f[i][j] = max(f[i][j], maxv);
//            }
//            res = max(res,f[i][j]);
//        }
//    }

    for(int i = 1; i <= n; i++){
        int maxv = 0;
        for(int j = 1; j <= n; j++){
            f[i][j] = f[i-1][j];
            if(a[i] == b[j]){
                f[i][j] = max(f[i][j], maxv+1);
            } else if(a[i] > b[j])  {
                //i相同的情况下，每轮maxv是不需要重复计算的
                maxv = max(maxv, f[i-1][j]);
            }
            res = max(res,f[i][j]);
        }
    }
    cout << res;
    return 0;
}