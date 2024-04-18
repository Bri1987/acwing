#include <iostream>

using namespace std;

const int N = 1010;
int f[N];
int v[N],w[N];

int n,m;

int main(){
    cin >> n >> m;
    //注意这里是1-n，与后面方程匹配对应
    for(int i = 1; i <= n; i++){
        cin >> v[i] >> w[i];
    }

    //朴素
//    for(int i = 1; i <=n ;i++){
//        for(int j = 0; j <= m;j++){
//            //f[i][j] = f[i-1][j];
//            //只要k从0开始，后面那个就包含了原先的f[i-1][j]
//            for(int k = 0; k*v[i] <= j; k++){
//                f[i][j]= max(f[i][j],f[i-1][j-k*v[i]] + k*w[i]);
//            }
//        }
//    }

//    for(int i = 1; i <=n ;i++){
//        for(int j = 0; j <= m;j++){
//            f[i][j] = f[i-1][j];
//            if(j >= v[i])
//                f[i][j]= max(f[i][j],f[i][j - v[i]] + w[i]);
//        }
//    }

    for(int i = 1; i <=n ;i++){
        //注意这里就是从小到大了，因为max的后一项，我们需要的就是当前i层的f[j - v[i]]，所以我们需要先更新j-v[i]的f值，再更新j的f值，不像背包需要的是上一层i-1层的f[j-v[i]]
        for(int j = v[i]; j <= m;j++){
            f[j] = max(f[j], f[j - v[i]] + w[i]);
        }
    }
    cout << f[m] << endl;
    return 0;
}