#include <iostream>
#include <queue>

using namespace std;
const int N = 100010;

int main(){
    //哈夫曼树，每次选择最小的两个数相加
    priority_queue<int,vector<int>,greater<>> q;

    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        int x;
        cin >> x;
        q.push(x);
    }

    int res = 0;
    for(int i = 0; i < n-1; i++){
        int x1 = q.top(); q.pop();
        int x2 = q.top(); q.pop();
        res += x1 + x2;
        q.push(x1 + x2);
    }
    cout << res << endl;
    return 0;
}