#include <iostream>
#include <algorithm>

using namespace std;
const int N = 100010;

int n;
struct Range{
    int l,r;
    //重载一下，以右端点从小到大排序
    bool operator<(const Range& w)const{
        return r < w.r;
    }
}range[N];

int main(){
    cin >> n;
    for(int i = 0; i < n;i++){
        int l,r;
        cin >> l >> r;
        range[i] = {l,r};
    }
    //1. 排序
    sort(range,range+n);

    //2.每次如果之前不包含，就选择新段的右端点
    int res = 0, right_most = -2e9;
    for(int i = 0; i < n;i++){
        if(range[i].l > right_most){
            res++;
            right_most = range[i].r;
        }
    }
    cout << res << endl;
    return 0;
}