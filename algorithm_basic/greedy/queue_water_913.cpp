#include <iostream>
#include <algorithm>

using namespace std;
typedef long long LL;

const int N = 100010;
int a[N];

int main(){
    int n;
    cin >> n;
    LL res = 0;
    for(int i = 0; i < n;i++)
        cin >> a[i];

    // 按照从小到大的顺序排队，总时间最小
    sort(a,a+n);

    for(int i = 0; i < n-1; i++){
        res += a[i] * (n-i-1);
    }
    cout << res << endl;
    return 0;
}