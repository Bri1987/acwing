#include <iostream>

using namespace std;

const int N = 310, INF=0x3f3f3f3f;
int s[N],f[N][N];
int w[N];

int main(){
    int n;
    cin >> n;
    for(int i = 1; i <= n;i++)
        cin >> w[i];

    //计算前缀和
    s[1] = w[1];
    for(int i = 2; i <= n; i++)
        s[i] = s[i-1] + w[i];

    //用长度来循环
    //!跳过了i = 1，因为[1,1]这种没必要，f[i][i]值为0就好，因为除了[l,r]每次最后一轮合并，其他合并都不用参与(单独一堆)，最后一轮又是直接用前缀和，f[i][i]一直保持为0即可
    for(int i = 2; i <= n; i++){
        //[1,1+2-1]即[1,2]按区间长度为2看
        for(int j = 1; j + i - 1<= n; j ++){
            int l = j, r = j +i -1;
            //! 注意这里只能只对f[l][r]初始化为负无穷了 , f[i][i]务必保持为0, 这样在把[1,3]分成[1,1]和[2,3]的时候，在最后计算前缀和之前只用算[2,3]，避免算重
            f[l][r] = INF;
            for(int k = l ; k < r; k++){
                //注意第二段的起点是k+1
                f[l][r] = min(f[l][r], f[l][k] + f[k+1][r]);
            }
            //最后一次一定是[l,r]的总和，是确定的
            f[l][r] += s[r] - s[l-1];
            //或者不要上一行，直接在循环里，其中s[r] - s[l-1]是在第二个min参数里面的.  f[l][r] = min(f[l][r], f[l][k] + f[k+1][r] + s[r] - s[l-1]);
        }
    }
    cout << f[1][n] << endl;
    return 0;
}