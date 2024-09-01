#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int N = 13, S = 1 << N;
int f[N][S];    // 表示前i-1行已被填满, 第i列的状态是s
vector<int> trans[S];

int main(){
    int n,m;
    while(cin >> n >> m, n || m){
        memset(f,0,sizeof f);
        // 1. 预处理一下这个state的上个state可以是什么
        for(int i = 0; i < 1 << m; i++){
            for(int j = 0; j < 1 << m; j++){
                if((i & j) == 0)
            }
        }
    }
    return 0;
}