#include <iostream>
#include <cstring>
#include <climits>
#include <vector>

using namespace std;

typedef long long LL;

const int N = 55;
vector<int> f[N][N];

int w[N];

int n;

bool cmp(vector<int> &a, vector<int> &b)
{
    if (a.size() != b.size()) return a.size() < b.size();
    for (int i = a.size() - 1; i >= 0; i -- )
        if (a[i] != b[i])
            return a[i] < b[i];
    return true;
}
vector<int> add(vector<int> a, vector<int> b)
{
    vector<int> c;
    int t = 0;
    for (int i = 0; i < a.size() || i < b.size(); i ++ )
    {
        if (i < a.size()) t += a[i];
        if (i < b.size()) t += b[i];
        c.push_back(t % 10);
        t /= 10;
    }
    while (t) c.push_back(t % 10), t /= 10;
    return c;
}
vector<int> mul(vector<int> a, LL b)
{
    vector<int> c;
    LL t = 0;
    for (int i = 0; i < a.size(); i ++ )
    {
        t += b * a[i];
        c.push_back(t % 10);
        t /= 10;
    }
    while (t) c.push_back(t % 10), t /= 10;
    return c;
}

int getMod(int x){
    if(x == n)
        return x;
    return x % n;
}

int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> w[i];
    }

    if(n == 1){
        cout << 0 << endl;
        return 0;
    }

    // ! 注意这里初始化值为0, 不然算len=1的时候会加两次
    for(int i = 1; i <= n; i++){
        vector vec = {0};
        f[i][i] = vec;
        f[i][getMod(i+1)] = vec;
    }

    // 认为合并1 2两堆间隔是1, 如果合并1 2 3 4四堆, 那间隔最多是3
    // 凸多边形划分间隔最小为2
    vector<int> mi;
    for(int len = 2; len <= n-1; len++){
        for(int i = 1; i <= n; i++){
            for(int k = i + 1; k <= i + len - 1; k++){
                auto mulVal = mul(mul({w[i]},w[getMod(k)]),w[getMod(i+len)]);
                auto newVal = add(add(mulVal, f[i][getMod(k)]),f[getMod(k)][getMod(i+len)]);
                if(f[i][getMod(i+len)].empty() || cmp(newVal,f[i][getMod(i+len)]))
                    f[i][getMod(i+len)] = newVal;
                if(len == n-1) {
                    if(mi.empty() || cmp(f[i][getMod(i+len)],mi))
                        mi = f[i][getMod(i+len)];
                }
            }
        }
    }
    for (int i = mi.size() - 1; i >= 0; i -- )
        printf("%d", mi[i]);
    return 0;
}