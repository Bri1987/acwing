#include <iostream>

using namespace std;

const int N = 2010, mod = 1e9+7;

int c[N][N];

void combination_init(){
    for(int i = 0; i < N; i++){
        //j<=i 选出的数不可能超过i, c[0][1]这种全局变量默认是0
        for(int j = 0; j <= i; j++){
            //选0个的话只有一种选法
            if(!j) c[i][j] = 1;
            //c[0][1]这种是0
            else c[i][j] = (c[i-1][j] + c[i-1][j-1]) % mod;
        }
    }
}

int main(){
    int m;
    cin >> m;
    combination_init();
    while (m--){
        int a,b;
        cin >> a >> b;
        cout << c[a][b] << endl;
    }
    return 0;
}