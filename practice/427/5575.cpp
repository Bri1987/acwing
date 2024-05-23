#include <iostream>
#include <map>

using namespace std;
const int N = 310;
int a[N],b[N];

//<第二维 ,值>
map<int ,int > dp;

// 在a数组里找出一个子集，使得子集内的数gcd为1，并且这个子集内的数对应的代价值之和尽量小

int n;

// a > b
int gcd(int x, int y)
{
    return y ? gcd(y, x % y) : x;
}

int main(){
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    for(int i = 1; i <= n; i++)
        cin >> b[i];

    //0和n的gcd是n
    dp[0] = 0;
    // 第一维：在前i个数中选，第二维：遍历能触碰到的所有gcd，值为激活代价。其中第二维数组和值由dp表达
    // 由于gcd范围可以很大，这里用map一边枚举一边存，只枚举当前出现过的可能的gcd
    for(int i = 1; i <= n; i++){
        for(auto [x,y] : dp){
            int d = x > a[i] ? gcd(x, a[i]) : gcd(a[i], x);
            if(dp.find(d) == dp.end()){
                // 还没有出现过这个最大公约数
                dp[d] = y + b[i];
            } else{
                // 已经出来过了这个d, 找个最小值
                dp[d] = min(dp[d], y + b[i]);
            }
        }
    }

    cout << (dp[1] ? dp[1] : -1) << endl;

    return 0;
}