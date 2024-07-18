#include <iostream>
#include <unordered_set>
#include <cstring>

using namespace std;

const int M = 110;
int f[M];

int m;  //m可以代表SG的分支是几条

int SG(int x){
    //因为取石子数目的集合是已经确定了的,所以每个数的sg值也都是确定的,如果存储过了,直接返回即可
    if(f[x] != -1) return f[x];
    //代表的是无序集合(注:因为在函数内部定义,所以下一次递归中的S不与本次相同)
    unordered_set<int> S;

    //因为SG树是走完所有分支情况画的，所以两层完整的for循环，因为拆新堆拆成什么数都有可能, 因为不能超过原堆大小，所以i < x
    for(int i = 0 ; i < x ; i++)
        for(int j = 0 ; j <= i ; j++)//规定j不大于i，避免重复
            S.insert(SG(i) ^ SG(j));//相当于一个局面拆分成了两个局面，由SG函数理论，多个独立局面的SG值,等于这些局面SG值的异或和

    //从0开始找到最小的没用过的
    for(int i = 0;;i++){
        if(!S.count(i))
            return f[x] = i;
    }
}

int main(){
    memset(f,-1,sizeof f);

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