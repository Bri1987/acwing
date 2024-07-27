#include <iostream>
#include <queue>
#include <cstring>

using namespace std;
const int N = 200010;
int d[N];

int main(){
    int a,b;
    cin >> a >> b;
    queue<int> q;
    memset(d,-1,sizeof d);
    d[a] = 0;
    q.push(a);
    while(!q.empty()){
        int t = q.front();
        q.pop();

        if(t == b)
            break;

        int point1 = 2 * t;
        int point2 = t + 1;
        int point3 = t -1;
        if(point1 < N && d[point1] == -1){
            d[point1] = d[t] + 1;
            q.push(point1);
        }
        if(point2 <= b && d[point2] == -1){
            d[point2] = d[t] + 1;
            q.push(point2);
        }
        if(d[point3] == -1){
            d[point3] = d[t] + 1;
            q.push(point3);
        }
    }
    cout << d[b];
    return 0;
}