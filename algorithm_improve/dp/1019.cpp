#include <iostream>

using namespace std;

const int N = 510, M = 6010;
int cnt ;
int v[N * 5], w[N * 5];
int f[M];

int main(){
    int n,total_v;
    cin >> n >> total_v;
    for(int i = 1; i <= n; i++){
        int vi,wi,si;
        cin >> vi >> wi >> si;
        int num = 1;
        while(si){
            cnt++;
            if(si < num){
                v[cnt] = vi * si;
                w[cnt] = wi * si;
                si = 0;
            } else {
                v[cnt] = vi * num;
                w[cnt] = wi * num;
                si -= num;
                num <<= 1;
            }
        }
    }

    // 01背包
    for(int i = 1; i <= cnt; i++){
        for(int j = total_v; j >= v[i]; j--){
            f[j] = max(f[j], f[j-v[i]]+w[i]);
        }
    }
    cout << f[total_v];
    return 0;
}