#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    vector<int> stk;     //模拟堆栈
    stk.push_back(arr[0]);

    for (int i = 1; i < n; ++i) {
        if (arr[i] > stk.back())    //如果该元素大于栈顶元素(即单调递增),将该元素入栈
            stk.push_back(arr[i]);
        else    //替换掉第一个大于或者等于这个数字的那个数 , 其他后面的数保留
            *lower_bound(stk.begin(), stk.end(), arr[i]) = arr[i];
    }
    cout << stk.size() << endl;
    return 0;
}