#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 30010;
int n = 30000, m;

int p[N],d[N],s[N];

int find (int x) {
    if (p[x] != x) {
        int rx = find (p[x]);
        // 还需要更新别的点，所以p[x]先不能变，才能拿到正确的d[p[x]], 每个根的d都是0的，不用担心重复加
        d[x] += d[p[x]];
        p[x] = rx;
    }
    return p[x];
}

int main () {
    cin >> m;
    for (int i = 1;i <= n;i++) p[i] = i,s[i] = 1;
    while (m--) {
        char op;
        int a,b;
        cin >> op >> a >> b;
        int ra = find (a),rb = find (b);
        if (op == 'M') {
            if (ra != rb) {
                p[ra] = rb;
                // 只用把当前的根节点加上size（即模拟放在队尾）, 除了根节点的其他点会在下一次find里面更新(询问也会走find，所以一定被更新)
                d[ra] = s[rb];
                s[rb] += s[ra];
            }
        }
        else {
            if (ra != rb) puts ("-1");
            else cout << max (0,abs (d[a] - d[b]) - 1) << endl;
        }
    }
    return 0;
}