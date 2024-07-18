#include <iostream>
#include <cstring>

using namespace std;
const int N = 100010;

int n;
// 注意边是2*N
int e[2*N],ne[2*N],h[N],idx;
int color[N];

// 添加一条边a->b
void add(int a, int b){
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

bool dna_dfs(int i, int c){
    color[i] = c;
    for(int j = h[i]; j != -1; j = ne[j]){
        int k = e[j];
        if(!color[k]){
            if(!dna_dfs(k,3-c))
                return false;
        } else if(color[k] == color[i])
            return false;
    }
    return true;
}

int main(){
    int m;
    cin >> n >> m;
    memset(h,-1,sizeof h);
    while (m--){
        int a,b;
        cin >> a >> b;
        add(a,b);
        add(b,a);
    }

    bool res = true;
    //注意这里的下标是从1开始!! 因为n >= 1 !
    for(int i = 1; i <= n; i++){
        if(!color[i]){
            if(!(res = dna_dfs(i, 1)))
                break;
        }
    }
    if(res)
        puts("Yes");
    else
        puts("No");
}