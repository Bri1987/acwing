#include <iostream>

using namespace std;
const int N = 100010;

int n,m,p[N];

//返回x所在集合的编号 + 路径压缩
int find(int x){
    //注意这里p[x] = find(p[x]) , 顺手让路上的每个父结点都指向集合编号根节点
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int main(){
    cin >> n >> m;
    //一共有 n个数，编号是 1∼n，最开始每个数各自在一个集合中
    for(int i = 1; i <= n; i++)
        p[i] = i;
    while (m--){
        char op[2];
        int a,b;
        cin >> op >> a >> b;

        if(op[0] == 'M')
            p[find(a)] = find(b);    //让a的祖宗结点的父亲等于b的祖宗结点，即p[x]=x,p[y]=y => p[x]=y
        else{
            if(find(a) == find(b))
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
        }
    }
}