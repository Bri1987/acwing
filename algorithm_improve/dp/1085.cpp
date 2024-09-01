#include <iostream>
#include <cstring>

using namespace std;

const int N = 12;
int memo[N][N];

int dfs(int i, int last, bool isLimit, bool isNum, string s) {
    int len = s.length();
    if(i == len)
        return isNum;
    if(!isLimit && isNum && memo[i][last] != -1)
        return memo[i][last];
    int up = isLimit ? s[i] - '0' : 9;
    int res = 0;
    for(int d = 0; d <= up; d++){
        if(d != 4 && !(last == 6 && d == 2) )
            res += dfs(i+1, d, isLimit && d == up, isNum || d != 0, s);
    }
    if(!isLimit && isNum)
        memo[i][last] = res;
    return res;
}

int main(){
    int a,b;
    while(cin >> a >> b, a || b){
        memset(memo,-1,sizeof memo);
        int resa = dfs(0,0,true, false,to_string(b));
        memset(memo,-1,sizeof memo);
        int resb = dfs(0,0,true, false,to_string(a-1));
        cout << resa - resb << endl;
    }
    return 0;
}