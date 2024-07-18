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

    sort(a,a+n);

    //奇数就选中位数，偶数就选在中间两个数之间
    //将距离两两分成一组，将第一个与最后一个分组，第二个与倒数第二个分组
    //对于每一组，一定是将点选在它们中间 值最小
    for(int i = 0; i < n;i++)
        res += abs(a[i] - a[n / 2]);
    cout << res;
    return 0;
}