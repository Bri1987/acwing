#include <iostream>
#include <unordered_set>
#include <cstring>

using namespace std;

const int N = 110, M = 10010;
int s[N],f[M];

int m;  //m可以代表SG的分支是几条

int SG(int x){
    //因为取石子数目的集合是已经确定了的,所以每个数的sg值也都是确定的,如果存储过了,直接返回即可
    if(f[x] != -1) return f[x];
    //代表的是无序集合(注:因为在函数内部定义,所以下一次递归中的S不与本次相同)
    unordered_set<int> S;
    for(int i = 0; i < m; i++){
        //先延伸到终点的sg值后,再从后往前排查出所有数的sg值
        //不能随便else insert 0,是错误的
        if(x >= s[i]) S.insert(SG(x-s[i]));
    }

    //从0开始找到最小的没用过的
    for(int i = 0;;i++){
        if(!S.count(i))
            return f[x] = i;
    }
}

int main(){
    memset(f,-1,sizeof f);

    cin >> m;
    for(int i = 0; i < m; i++)
        cin >> s[i];
    int n;
    cin >> n;
    int res = 0;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        res ^= SG(x);
    }
    if(res != 0)
        puts("Yes");
    else
        puts("No");
    return 0;
}