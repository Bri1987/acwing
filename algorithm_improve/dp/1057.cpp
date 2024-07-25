#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

class Solution {
public:
    static const int N = 100010;
    int f[N][2][102];
    int maxProfit(int k, vector<int>& prices) {
        // f代表当前步数完结状态

        memset(f,-0x3f,sizeof f);
        f[1][0][0] = 0;
        f[1][1][0] = -prices[0];

        for(int i = 2; i <= prices.size(); i++){
            f[i][0][0] = f[i-1][0][0];

            for(int j = 1; j <= k; j++){
                //手上没有东西但是完成了一次交易从i=2开始
                if(i >= 2*j)
                    f[i][0][j] = max(f[i-1][0][j], f[i-1][1][j-1]+prices[i-1]);
                else
                    break;
            }

            f[i][1][0] = max(f[i-1][1][0],f[i-1][0][0]-prices[i-1]);

            for(int j = 1; j <= k; j++){
                //手上有东西并完成了一次交易了，从i=3开始(前3次买卖买)
                if(i >= 2*j+1)
                    f[i][1][j] = max(f[i-1][1][j],f[i-1][0][j]-prices[i-1]);
                else
                    break;
            }
        }
        int res = 0;
        for(int j = 1; j <= k; j++){
            res = max(res,f[prices.size()][0][j]);
        }
        return res;
    }
};

int main() {
    int n,k;
    cin >> n >> k;
    vector<int> prices;
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        prices.push_back(a);
    }
    Solution solution;
    int maxProfit = solution.maxProfit(k, prices);
    cout  << maxProfit << endl;
    return 0;
}