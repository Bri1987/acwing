#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

const int N = 200010;

int n;
struct Range{
    int l,r;
    //重载一下，以左端点从小到大排序
    bool operator<(const Range& w)const{
        return l < w.l;
    }
}range[N];

int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        int l,r;
        cin >> l >> r;
        range[i] = {l,r};
    }
    sort(range, range+n);

    //维护一个右端点
    priority_queue<int,vector<int>,greater<>> q;
    for(int i = 0; i < n; i++){
        if(q.empty())
            q.push(range[i].r);
        else{
            if(q.size() == 2 && range[i].l <= q.top()){
                puts("NO");
                return 0;
            }

            if(range[i].l > q.top()){
                q.pop();
                q.push(range[i].r);
            } else{
                //q.size=1, q.size=2的已经淘汰了
                q.push(range[i].r);
            }
        }
    }
    puts("YES");
    return 0;
}