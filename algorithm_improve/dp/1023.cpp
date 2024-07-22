#include <iostream>

using namespace std;

const int N = 1010;
int f[N];
int a[5] = {0,10,20,50,100};

int main(){
    int n;
    cin >> n;
    // 注意这种必须全部花完的做法的初始化
    f[0] = 1;
    for(int i = 1; i <= 4; i++){
        for(int j = a[i]; j <= n ;j++){
            f[j] += f[j-a[i]];
        }
    }
    cout << f[n];
    return 0;
}