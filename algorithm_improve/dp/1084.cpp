#include <iostream>
#include <cstring>

using namespace std;

const int N = 12, M = 110;
int memo[N][M];

int dfs(int i, int sum, bool isLimit, bool isNum, string s, int n) {
    int len = s.length();
    if(i == len)
        return isNum && sum == 0;
    if(!isLimit && isNum && memo[i][sum] != -1)
        return memo[i][sum];
    int up = isLimit ? s[i] - '0' : 9;
    int res = 0;
    for(int d = 0; d <= up; d++){
        res += dfs(i+1, (sum + d) % n, isLimit && d == up, isNum || d != 0, s,n);
    }
    if(!isLimit && isNum)
        memo[i][sum] = res;
    return res;
}

int main(){
    int a,b,n;
    while(cin >> a >> b >> n){
        memset(memo,-1,sizeof memo);
        int resa = dfs(0,0,true, false,to_string(b),n);
        memset(memo,-1,sizeof memo);
        int resb = dfs(0,0,true, false,to_string(a-1),n);
        cout << resa - resb << endl;
    }
    return 0;
}