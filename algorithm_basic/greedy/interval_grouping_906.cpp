#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;
const int N = 100010;

struct Range{
    int l,r;
    bool operator < (const Range& w)const{
        return l < w.l;
    }
}range[N];

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        range[i] = {l, r};
    }

    sort(range, range + n);

    //一个小根堆
    priority_queue<int,vector<int>,greater<>> heap;
    for(int i = 0; i < n; i++){
        auto r = range[i];
        if(heap.empty() || heap.top() >= r.l){
            heap.push(r.r);
        } else {
            //如果当前小根堆顶点的右端点就比当前区间的小，就默认放入这个组，那自然就需要更新这个组的新右端点值（更新为当前区间右端点）
            heap.pop();
            heap.push(r.r);
        }
    }
    cout << heap.size();
    return 0;
}