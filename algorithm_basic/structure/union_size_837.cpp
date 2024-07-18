#include <iostream>

using namespace std;
const int N = 100010;

int n,m,p[N],size_[N];

//返回x所在集合的编号 + 路径压缩
int find(int x){
    //注意这里p[x] = find(p[x]) , 顺手让路上的每个父结点都指向集合编号根节点
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int main(){
    cin >> n >> m;
    //一共有 n个数，编号是 1∼n，最开始每个数各自在一个集合中
    for(int i = 1; i <= n; i++){
        p[i] = i;
        //初始化一下每个集合初始个数，只包含自己
        size_[i] = 1;
    }
    while (m--){
        char op[5];
        int a,b;
        cin >> op;

        if(op[0] == 'C'){
            cin >> a >> b;
            //如果a和b都在一个集合里就不处理了
            if(find(a) == find(b))
                continue;
            //注意下一行要放在前面
            size_[find(b)] += size_[find(a)];
            p[find(a)] = find(b);    //让a的祖宗结点的父亲等于b的祖宗结点，即p[x]=x,p[y]=y => p[x]=y
        }
        else if(op[1] == '1'){
            cin >> a >> b;
            if(find(a) == find(b))
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
        }else {
            cin >> a;
            cout << size_[find(a)] << endl;
        }
    }
}