#include <iostream>

using namespace std;

const int N = 1010;
//所有在第一个序列的前i个字母与在第二个序列的前j个字母出现的子序列
int f[N][N];

int n1,n2;
char s1[N],s2[N];

int main(){
    cin >> n1 >> n2;
    for(int i = 1; i <= n1; i++)
        cin >> s1[i];
    for(int i = 1; i <= n2; i++)
        cin >> s2[i];

    for(int i = 1; i <= n1; i++){
        for(int j = 1; j <= n2; j++){
            //以s1i s2j是否包含在子序列中划分
            if(s1[i] == s2[j]){
                //如果当前值相等了，双方都要后退一步，就不存在aca和a重复算a的情况，
                // 应该是由于即使用max，如果遇到aca和a这种情况，要么抛弃当前字符组+1, 要么可能当前其中一个字符是有用的，还是想匹配原来的，  反正结果都一样，一次变动最多只能是+1,要么舍弃原来匹配对-1+1，要么保留原来的是0
                //也可以f[i][j] = max(f[i][j] , f[i - 1][j - 1] + 1);
                f[i][j] = f[i - 1][j - 1] + 1;
            } else {
                f[i][j] = max(f[i - 1][j] , f[i][j - 1]);
            }
        }
    }
    cout << f[n1][n2] << endl;
    return 0;
}