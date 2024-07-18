#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int,int> PII;
int N = 1000010;

int main(){
    int n;
    cin >> n;
    vector<PII> intervals;
    for(int i = 0; i < n; i++){
        int l,r;
        cin >> l >> r;
        intervals.push_back({l,r});
    }

    //以左端排序
    sort(intervals.begin(),intervals.end());
    int res = 1;
    int right = intervals[0].second;
    for(int i = 1; i < n; i++){
        if(intervals[i].first <= right)
            right = max( right, intervals[i].second);
        else{
            //左端大于right，则一定是新段
            //由于是左端升序，之后的interval的左端也一定大于之前段的right，固之前的段不用再考虑
            res++;
            right = intervals[i].second;
        }
    }
    //判断一下非空
    if(intervals.empty())
        res = 0;
    cout << res << endl;
}