//#include <iostream>
//
//using namespace std;
//
//const int N = 1010;
//int n,m;
//int v[N], w[N];
//int f[N][N];
//
//int main(){
//    cin >> n >> m;
//    //注意这里是1-n，与后面方程匹配对应
//    for(int i = 1; i <= n; i++){
//        cin >> v[i] >> w[i];
//    }
//
//    //f[i][j]=w，在前i个物品中选，不超过体积j，能取得的最大价值w
//    //f[i] [j]=max(f[i - 1] [j] ,f[i - 1] [j - v[i]] + w[i]) 注意右边这部分是可能不存在的，当体积j装不下i物品时，即j < v[i]
//    for(int i = 1; i <=n ;i++)
//        for(int j = 1; j <=m ;j++){
//            f[i][j] = f[i-1][j];
//            if(j >= v[i])
//                //注意这里取max
//                f[i][j] = max(f[i][j],f[i-1][j - v[i]] + w[i]);
//        }
//
//    cout << f[n][m] << endl;
//    return 0;
//}

#include <iostream>

using namespace std;

const int N = 1010;
int n,m;
int v[N], w[N];
int f[N];

int main(){
    cin >> n >> m;
    //注意这里是1-n，与后面方程匹配对应
    for(int i = 1; i <= n; i++){
        cin >> v[i] >> w[i];
    }

    //在i为i-1上一层的时候，j从v[i]到m走了一遍；在走到i层的时候，由于j-v[i]一定比j小，所以在更新f[j]之前，一定更新了第i层的f[j-v[i]]，
    // f[j-v[i]]就不是i-1层的值了，但我们需要的是i-1层的值。所以需要从大到小更新
    for(int i = 1; i <=n ;i++)
        for(int j = m; j >=v[i] ;j--){
            f[j] = max(f[j],f[j - v[i]] + w[i]);
        }

    cout << f[m] << endl;
    return 0;
}