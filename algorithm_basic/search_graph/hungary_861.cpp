#include <iostream>
#include <cstring>

using namespace std;

const int N = 510;
const int M = 100010;
int n1,n2;

// 注意边是2*N
int e[M],ne[M],h[N],idx; //匈牙利算法中只会用到从第一个集合指向第二个集合的边，所以这里只用存一个方向的边
int match[N];       // 存储第二个集合中的每个点当前匹配的第一个集合中的点是哪个
bool st[N];     // 表示第二个集合中的每个点是否已经被遍历过

// 添加一条边a->b
void add(int a, int b){
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

bool find(int x){
    //n1的点，连接的j一定是n2的点
    for (int i = h[x]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (!st[j])
        {
            st[j] = true;
            //待牵手，或者和这个女生已经牵手的男生有其他备胎！由于n >= 1，只要为0就一定是没牵手
            //在find递归中，一定会选择之前没选择过的备胎，因为之前的st已经是true了
            if (match[j] == 0 || find(match[j]))
            {
                //在find里面，保证了match[j]和其中一个选择牵手；在当前函数内，保证了x牵手成功，即x和j是一对啦~
                match[j] = x;
                return true;
            }
        }
    }

    return false;
}

int main(){
    int m;
    cin >> n1 >> n2 >> m;
    memset(h, -1, sizeof h);

    while (m--){
        int u,v;
        cin >> u >> v;
        add(u,v);
    }

    // 求最大匹配数，依次枚举第一个集合中的每个点能否匹配第二个集合中的点
    int res = 0;
    for (int i = 1; i <= n1; i ++ )
    {
        memset(st, false, sizeof st);
        if (find(i)) res ++ ;
    }
    cout << res << endl;
    return 0;
}