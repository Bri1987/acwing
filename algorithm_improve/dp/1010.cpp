#include<iostream>
#include<algorithm>
using namespace std;

const int N = 1005;
int n = 1, a[N];

int main()
{
    vector<int> f,g;
    while(cin >> a[n]){
        n ++;
    }
    n--;
    int ans1 = 0;
    int ans2 = 0;
    g.push_back(a[1]);
    f.push_back(a[n]);

    // ans2是严格上增
    for(int i = 2; i <= n; i++){
        if(a[i] > g.back())
            g.push_back(a[i]);
        else
            *lower_bound(g.begin(),g.end(),a[i]) = a[i];
    }

    // ans1是从后到前的不严格上增
    for(int i = n-1; i >= 1; i--){
        if(a[i] >= f.back())
            f.push_back(a[i]);
        else
            *upper_bound(f.begin(),f.end(),a[i]) = a[i];
    }

    cout << f.size() << endl;
    cout << g.size() << endl;
    return 0;
}