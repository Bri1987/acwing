#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 33;
int memo[N][N];

int K,B;

// 注意这一步非常巧妙, 比如如果转化后为201, 就说明需要用至少3个该进制数才能表示(比如10进制下的201是100+100+1)
// 题目中要求数不相同，说明转化后必须为1或0的字符串才能满足要求
// 把x转化为b进制的字符串
string convert(int x){
    string res = "";
    while(x){
        res += to_string((x % B));
        x /= B;
    }
    reverse(res.begin(),res.end());
    return res;
}

// cnt代表用了多少个数了
int dfs(int i, int cnt, bool isLimit, string s){
    int len = s.length();
    if(i == len){
        if(cnt == K)
            return 1;
        return 0;
    }

    if(!isLimit && memo[i][cnt] != -1)
        return memo[i][cnt];

    int up = isLimit ? s[i] - '0' : B-1;
    int res = 0;
    for(int d = 0; d <= up; d++){
        if(d == 0 || d == 1)
            res += dfs(i+1, cnt + (d == 1), isLimit && d == up, s);
    }

    if(!isLimit)
        memo[i][cnt] = res;
    return res;
}

int main(){
    int x,y;
    cin >> x >> y;
    cin >> K >> B;
    // cout << convert(x) << " see " << convert(y) << endl;
    memset(memo,-1,sizeof memo);
    int res1 = dfs(0,0,true, convert(y));
    memset(memo,-1,sizeof memo);
    int res2 = dfs(0,0,true, convert(x-1));
    cout << res1 - res2 ;
    return 0;
}
