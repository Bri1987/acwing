#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> get_divisors(int x)
{
    vector<int> res;
    //由于毕竟是i * i <= x，所以不会影响到之后有重复
    for (int i = 1; i <= x / i; i ++ )
        if (x % i == 0)
        {
            res.push_back(i);
            //如果是平方，不要重复添加，其他情况则补上大的那半边的约数
            if (i != x / i) res.push_back(x / i);
        }
    sort(res.begin(), res.end());
    return res;
}

int main(){
    int m;
    cin >> m;
    while (m--){
        int x;
        cin >> x;
        auto vec = get_divisors(x);
        for(auto& v : vec){
            cout << v << " ";
        }
        cout << endl;
    }
    return 0;
}