#include <iostream>

using namespace std;
int N,K;
const int CN = 100010;
int p[CN],d[CN];

//带权并查集
//知道x和ｙ的关系　和　ｙ和ｚ的关系，就一定能知道ｘ和ｚ的关系
//破环： 只有３种关系，％３可表示所有关系，用点到根节点的距离表示它和根结点的关系，余１第一代表示它可以吃根结点，距离余２第二代代表它被根结点吃，距离余０代表与根结点是同类（根结点与自己距离为０）
//存的ｄ是它到父结点的距离，初始化时为０
//知道结点和根节点的关系，就能知道任意２点的关系。

//返回x所在集合的编号 + 路径压缩
int find(int x){
    //注意这里p[x] = find(p[x]) , 顺手让路上的每个父结点都指向集合编号根节点
    if(p[x] != x) {
        //由于p[x]会变，先不让p[x]直接等于最终结果
        int tmp = find(p[x]);
        d[x] += d[p[x]];
        p[x] = tmp;
    }
    return p[x];
}

int main(){
    cin >> N >> K;

    int op,a,b;
    int fake=0;
    //初始d[i]都为0，此处省略
    for(int i = 1; i <= N; i++)
        p[i] = i;

    while (K--){
        cin >> op >> a >> b;
        if(a > N || b > N){
            fake++;
            continue;
        }

        int pa = find(a),pb = find(b);
        if(op == 1){
            //%3=0是同类的关系
            //已经在一个集合，则是有一定限制的话就直接判断
            if(pa == pb && (d[a]-d[b])%3 != 0){
                fake++;
                continue;
            }else if(pa != pb){
                //如果还没有任何关系，就制定一个1的正确关系
                //要定一个pa到pb的距离 ?
                //要使得之后ab同类，则(d[a] + ? - d[b])%3 = 0 ,所以?=d[b]-d[a]
                p[pa] = pb;
                d[pa] = d[b] - d[a];
            }
        }else if(op == 2){
            //差1是代表2对应的吃的关系
            //已经在一个集合，有一定限制的话就直接判断
            if(pa == pb && (d[a] - d[b] - 1) %3 != 0){
                fake++;
                continue;
            }else if(pa != pb){
                //如果还没有任何关系，就制定一个2的正确关系
                //d[a] + ? -d[b] - 1 =0
                //? = d[b]-d[a]+1
                p[pa] = pb;
                d[pa] = d[b] - d[a] + 1;
            }
        }
    }
    cout << fake << endl;
    return 0;
}