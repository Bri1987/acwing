#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

const int N = 100010;
int h[N],e[N],ne[N], w[N],idx;
int dist[N];
bool st[N];

int n,m;

void add(int a, int b, int c){
    e[idx] = b; ne[idx] = h[a]; w[idx] = c;
    h[a] = idx++;
};

void spfa(){
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;

    queue<int> q;
    q.push(1);
    st[1] = true;

    while (!q.empty()){
        int t = q.front();
        q.pop();

        st[t] = false;

        for (int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            if (dist[j] > dist[t] + w[i])
            {
                dist[j] = dist[t] + w[i];
                if (!st[j])     // 如果队列中已存在j，则不需要将j重复插入
                {
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }
}

int main(){
    cin >> n >> m;
    memset(h, -1 ,sizeof h);
    while (m--){
        int x,y,z;
        cin >> x >> y >> z;
        add(x,y,z);
    }

    spfa();
    if (dist[n] > 0x3f3f3f3f / 2)
        puts("impossible");
    else
        cout << dist[n];
}