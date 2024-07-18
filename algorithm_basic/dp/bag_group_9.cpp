#include <iostream>

using namespace std;

const int N = 110;

int n,m;
int s[N];
int v[N][N],w[N][N];
int f[N];

int main(){
    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        cin >> s[i];
        for(int j = 1; j <= s[i]; j++)
            cin >> v[i][j] >> w[i][j];
    }

    //朴素
//    for(int i = 1; i <= n; i++)
//        for(int j = 0; j <= m; j++){
//            for(int k = 0; k <= s[i]; k++){
//                if(v[i][k] <= j)
//                    f[i][j] = max(f[i][j], f[i-1][j - v[i][k]] + w[i][k]);
//            }
//        }

    //一维
    for(int i = 1; i <= n; i++)
        for(int j = m; j >= 0; j--){
            for(int k = 0; k <= s[i]; k++){
                if(v[i][k] <= j)
                    f[j] = max(f[j], f[j - v[i][k]] + w[i][k]);
            }
        }

    cout << f[m] << endl;
    return 0;
}