#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

const int N = 1000010;
int n;
int h[N],ne[N],e[N],idx;
int d[N];    //记录1到每个点的距离
queue<int> q;
bool st[N];

// 添加一条边a->b
void add(int a, int b){
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

int main(){
    int m;
    memset(h, -1, sizeof h);
    cin >> n >> m;
    while (m--){
        int a,b;
        cin >> a >> b;
        add(a,b);
    }

    //如果是1到1，那么一定为0
    if(n == 1){
        cout << 0 << endl;
        return 0;
    }

    q.push(1);
    while (!q.empty())
    {
        int t = q.front();
        q.pop();

        for (int i = h[t]; i != -1; i = ne[i]){
            int j = e[i];
            if (!st[j]){
                st[j] = true; // 表示点j已经被遍历过
                d[j] = d[t] + 1;
                if(j == n){
                    cout << d[j] << endl;
                    return 0;
                }
                q.push(j);
            }
        }
    }
    cout << -1 << endl;
    return 0;
}