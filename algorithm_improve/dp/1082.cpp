#include <iostream>
#include <cstring>

using namespace std;

const int N = 12;
int memo[N][N];

int dfs(int i, int last, bool isLimit, string s){
    int len = s.length();
    if(i == len)
        return 1;
    if(!isLimit && memo[i][last] != -1)
        return memo[i][last];
    int up = isLimit ? s[i] - '0' : 9;
    int res = 0;
    for(int d = last; d <= up; d++){
        res += dfs(i+1, d, isLimit && d == up, s);
    }
    if(!isLimit)
        memo[i][last] = res;
    return res;
}

int main(){
    int a,b;
    while(cin >> a >> b) {
        memset(memo,-1,sizeof memo);
        int resa = dfs(0,0,true, to_string(b));
        memset(memo,-1,sizeof memo);
        int resb = dfs(0,0,true, to_string(a-1));
        cout << resa - resb << endl;
    }
    return 0;
}