#include <iostream>
using namespace std;
const int N = 100010;

//就0和1吧
//注意这里开的数组大小，每个数最多可能存31个内容，N最大为10^5 ,开son[N][2]肯定是不够的
int son[31*N][2],idx;

void insert(int x){
    int p = 0;
    //存的时候高位在前 , 搜的时候也是搜到高位异或优先
    //!!这样用trie能考虑到前导0!
    //比如1，存的是00000000...1
    for(int i = 30; i >=0 ;i--){
        int u = (x >> i) & 1;
        if(!son[p][u])
            son[p][u]= ++idx;
        p = son[p][u];
    }
}

int search_max(int x){
    int p =0;
    int res = 0;
    for(int i = 30; i >=0 ;i--){
        int u = (x >> i) & 1;
        //如果找不到!u，就在自己这个数的路走下去
        //!u就是看有没有与这一位异或的
        if(!son[p][!u]){
            p = son[p][u];
            res *= 2;
        } else{
            //找到了!u，就+1
            p = son[p][!u];
            res = res*2 + 1;
        }
    }
    return res;
}

int main(){
    int n;
    cin >> n;
    int res = 0;
    int a[n];
    for(int i = 0; i < n ;i++){
        cin >> a[i];
        insert(a[i]);
    }
    for(int i = 0; i < n ;i++){
        res = max(res, search_max(a[i]));
    }
    cout << res ;
}