#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

const int N = 100010;
int h[N],e[N],ne[N], w[N],idx;
int dist[N];
bool st[N];
int cnt[N];

int n,m;

void add(int a, int b, int c){
    e[idx] = b; ne[idx] = h[a]; w[idx] = c;
    h[a] = idx++;
};

void spfa(){
    //! 这里不需要初始化dist数组为 正无穷/初始化的原因是， 如果存在负环， 那么dist不管初始化为多少， 都会被更新
    // memset(dist, 0x3f, sizeof dist);
    // dist[1] = 0;

    queue<int> q;
    // q.push(1);
    // st[1] = true;
    //! 不仅仅是1了， 因为点1可能到不了有负环的点， 因此把所有点都加入队列
    for(int i = 1; i <= n; i++){
        q.push(i);
        st[i] = true;
    }

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
                cnt[j] = cnt[t] + 1;
                if(cnt[j] >= n){
                    puts("Yes");
                    return;
                }

                if (!st[j])     // 如果队列中已存在j，则不需要将j重复插入
                {
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }
    puts("No");
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
}