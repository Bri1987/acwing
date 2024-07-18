#include <iostream>
using namespace std;
const int N = 100010;

//一维是结点总数，而结点和结点之间的关系（谁是谁儿子）存在第二个维度，比如[0][1]=3, [0]表示根节点，[1]表示它有一个儿子‘b’,这个儿子的下标是3；
// 接着如果有一个[3][2]=8 ; 说明根节点的儿子‘b’也有一个儿子‘c’，这个孙子的下标就是8；这样传递下去，就是一个字符串。
// 随便给一个结点][x][y], 并不能看出它在第几层，只能知道，它的儿子是谁
int son[N][26];
int cnt[N];
//下标是0的点，既是根结点，也是空结点
int idx;
char s[N];

//插入一个字符串到trie树
void insert(const char str[]){
    int p = 0;
    for(int i=0; str[i];i++){
        //映射成0-25
        int u = str[i] - 'a';
        //如果在trie中不存在，就创建出来
        if(!son[p][u])
            son[p][u] = ++idx;
        p = son[p][u];
    }
    cnt[p]++;
}

//查询一个字符串出现多少次
int query(char str[]){
    int p =0;
    for(int i=0; str[i];i++) {
        //映射成0-25
        int u = str[i] - 'a';
        if(!son[p][u])
            return 0;
        p = son[p][u];
    }
    return cnt[p];
}

int main(){
    int n ;
    cin >> n;
    while(n--){
        char op[2];
        scanf("%s%s",op,s);
        if(op[0] == 'I') insert(s);
        else cout << query(s) << endl;
    }
}