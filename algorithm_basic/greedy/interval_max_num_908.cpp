#include <iostream>
#include <algorithm>

using namespace std;
const int N = 100010;

struct Range{
    int l,r;
    bool operator < (const Range& w)const{
        return l < w.l;
    }
}range[N];

//其实跟上一题可以是一模一样的 , 上一题的代码也能过
//接上题图，如果最多可以选超过cnt个区间，就必须选择cnt+1个点才能满足上题的要求，但是不行，所以最多也就cnt个区间

int main(){
    int n;
    cin >> n;
    for(int i= 0; i < n;i++){
        int l,r;
        cin >> l >> r;
        range[i] = {l,r};
    }

    sort(range,range+n);

    int res = 0,right_most = -2e9;
    for(int i= 0; i < n;i++){
        if(range[i].l > right_most){
            right_most = range[i].r;
            res++;
        } else{
            right_most = min(right_most,range[i].r);
        }
    }
    cout << res;
    return 0;
}