#include <iostream>

using namespace std;

const int N = 1010;
int n1,n2;
char s1[N],s2[N];
int f[N][N];

int main(){
    cin >> n1 >> (s1 + 1);
    cin >> n2 >> (s2 + 1);

    //初始化
    for(int i = 1; i <= n2; i++) f[0][i] = i;
    for(int i = 1; i <= n1; i++) f[i][0] = i;

    //dp[i][j] 为 a 的 [0..i] 转换成 b 的 [0..j] 的最小操作数。
    //
    //if (删除的情况) dp[i][j] = dp[i-1][j] + 1;
    //else if (新增的情况) dp[i][j] = dp[i][j-1] + 1;
    //else if (修改的情况) dp[i][j] = dp[i - 1][j - 1] + 1;
    //else dp[i][j] = dp[i-1][j-1]; // 不需要任何操作, 和上一个状态相同
    for(int i = 1; i <= n1; i++){
        for(int j = 1; j <= n2; j++){
            if(s1[i] == s2[j])
                f[i][j] = f[i-1][j-1];
            else{
                //f[i][j] = min(f[i - 1][j],f[i][j - 1],f[i - 1][j - 1]) + 1;
                //通过增删改三种状态+1能达到当前状态，往回退一步，看要增要删要改的三种前一个状态，哪个的修改步数最少
                f[i][j] = min(f[i - 1][j],f[i][j - 1]);
                f[i][j] = min(f[i][j], f[i - 1][j - 1]) + 1;
            }
        }
    }
    cout << f[n1][n2] << endl;
    return 0;
}