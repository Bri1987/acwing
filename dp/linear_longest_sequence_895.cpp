#include <iostream>

using namespace std;

const int N = 1010;
int f[N],w[N];

int main(){
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> w[i];

    //每个元素都初始为1，因为自己就是一个最短上升子序列
    for(int i = 1; i <= n; i++)
        f[i] = 1;
    int mx = 1;
    for(int i = 2; i <= n; i++){
        //注意这里还有一个for循环，找比w[i]小的值，所以j < i即可
        for(int j = 1; j < i; j++){
            if(w[i] > w[j]){
                f[i] = max(f[i] , f[j] + 1);
            }
        }
        mx = max(mx , f[i]);
    }
    cout << mx << endl;
    return 0;
}