#include <iostream>
#include <cstring>

using namespace std;
const int N = 110;
int h[N],e[N],ne[N],idx;
int v_[N],w_[N];
int f[N][N];

int n,v;

void add(int a,int b){
    e[idx] = b;
    ne[idx] = h[a];
    h[a] = idx++;
}

// 后序遍历树吧
void dfs(int root, int p){
    // 分组
    for(int i = h[root]; i != -1; i = ne[i]){
        int j = e[i];
        if(j != p){
            dfs(j,root);

            // 由于要分配给son了, 那自己本身是必选的, 必须预留出v[root]
            for(int a = v - v_[root]; a >= 0; a--){
                for(int b = 0; b <= a; b++){
                    // 一个分组一个分组地分
                    // cout << v - v_[root] << " , " << root << " " << a - b << ". " << f[root][a-b] << endl;
                    f[root][a] = max(f[root][a] , f[root][a-b] + f[j][b]);
                    // cout << "f : root : " << root<< " "<< a << " " << f[root][a] << endl;
                }
            }
        }
    }

    // 把自己选上的话就加上自己, 之前在分配体积算的时候已经把这部分预留出来了
    for(int j = v; j >= v_[root]; j--)
        f[root][j] = f[root][j - v_[root]] + w_[root];
    //清空没选上u的所有状态, 根都没选上, 那一定就直接是0了
    for (int j = 0; j <  v_[root]; ++ j)
        f[root][j] = 0;
}

int main(){
    cin >> n >> v;
    memset(h,-1,sizeof h);
    int root;
    for(int i = 1; i <= n; i++){
        int father;
        cin >> v_[i] >> w_[i] >> father;
        if(father == -1)
            root = i;
        else
            add(father,i);      // 指儿子
    }

    dfs(root,-1);
    cout << f[root][v];
    return 0;
}