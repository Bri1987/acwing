#include <iostream>
#include <unordered_map>

using namespace std;

int l,r;

int cal_len(int num){
    int res_ = 0;
    while(num){
        res_++;
        num /= 10;
    }
    return res_;
}

int dfs(int cur_bit, int lim, int before, int num){
    if(cur_bit == lim){
        if(num >= l && num <= r)    return 1;
        else return 0;
    }

    //注意res = 0在这里定义，不要在全局变量
    int res = 0;
    for(int i = 0; i <= 9; i++){
        if(i == 0 && cur_bit == 0)
            continue;
        if(cur_bit == 0 || i == before+1 || i == before-1)
            res += dfs(cur_bit+1, lim, i, num*10 + i);
    }
    return res;
}

int main(){
    int n;
    cin >> n;
    while(n--){
        cin >> l >> r;
        int res = 0;
        int ls = cal_len(l);
        int lr = cal_len(r);
        //注意这里从2开始
        for(int i = max(2, ls); i <= lr; i++){
            res += dfs(0, i, -1, 0);
        }
        cout << res << endl;
    }
    return 0;
}

