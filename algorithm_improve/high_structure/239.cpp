#include <iostream>
#include <unordered_map>

using namespace std;

const int N = 2e4 + 10;

int n, m;
int p[N], d[N];
unordered_map<int, int> S;

//d[x]代表距离根节点的距离，和食物链很像
//d[x]表示x与p[x]的奇偶性关系，0是同类，所以初始化也是0

// 离散化 + 前缀和，S代表前缀
// 比如最开始得到1-2里有奇数个1，说明前2个数 中1的个数 - 前0个数中1的个数= 奇数，说明S[r]与S[l-1]不同奇偶，并查集的元素其实是各个前缀的奇偶性质
int get(int x) {
    if (S.count(x) == 0) {
        S[x] = ++n;
    }
    return S[x];
}

int find(int x) {
    if (p[x] != x) {
        int root = find(p[x]);
        d[x] ^= d[p[x]];
        p[x] = root;
    }
    return p[x];
}

int main() {
    cin >> n >> m;
    n = 0;

    for (int i = 0; i < N; i++) {
        p[i] = i;
    }

    int res = m;  //如果无矛盾, 输出问题数量, 初始的时候为m
    for (int i = 1; i <= m; i++) {
        int a, b;
        string type;
        cin >> a >> b >> type;
        a = get(a - 1), b = get(b);  // s[a-1], s[b]

        // 为0代表同奇偶，为1代表不同奇偶
        int t = 0;
        if (type == "odd") {
            t = 1;
        }
        int pa = find(a), pb = find(b);
        if (pa == pb) {
            // d[a] ^ d[b]能判断a和b是不是同奇偶
            if ((d[a] ^ d[b]) != t) {
                res = i - 1;
                break;
            }
        } else {
            // 之前这两个前缀还没什么关系
            p[pa] = pb;
            // d[a],d[b]初始为0， 0 ^ 0=0，如果t = 0代表应该同奇偶，再^一次即0^0^0=0
            // 如果a距d[a]的p已经为1，d[b]还为0，假设t=0(a,b同奇偶). d[pa] = 1^0^0 = 1, b的pb是同奇偶 => pa与pb奇偶不同，a与pa奇偶不同，实现了a,b同奇偶
            d[pa] = d[a] ^ d[b] ^ t;
        }
    }
    cout << res << endl;
}