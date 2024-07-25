#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    static const int N = 100010;
    int f[N][3];   //0 : 没东西, 1:没卖, 2:刚卖冷冻期
    int maxProfit(vector<int>& prices) {
        f[1][0] = 0;
        f[1][1] = -prices[0];
        f[1][2] = 0;
        for(int i = 2; i <= prices.size(); i++){
            f[i][0] = max(f[i-1][0],f[i-1][2]);     // 上次也没东西，或者上次是冷冻期但完了也没买
            f[i][1] = max(f[i-1][0]-prices[i-1],f[i-1][1]); //在上次没东西的基础上上买了东西
            f[i][2] = f[i-1][1]+prices[i-1];        // 把上次东西卖了才能进入冷冻期 . 意思是下一步不能买

            // cout << f[i][0] << " " << f[i][1]<< " " << f[i][2] << endl;
        }
        return max(f[prices.size()][0],f[prices.size()][2]);
    }
};

int main() {
    int n;
    cin >> n;
    vector<int> prices;
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        prices.push_back(a);
    }
    Solution solution;
    int maxProfit = solution.maxProfit(prices);
    cout << maxProfit << endl;
    return 0;
}