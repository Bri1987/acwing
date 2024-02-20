#include <iostream>
#include <cstring>
using namespace std;
const int N = 100003;

//哈希表的槽
int h[N];
//竖着的链
int e[N],ne[N],idx;

void insert(int x){
    //+N让余数变成整数
    int k = (x % N + N) % N;
    //将数插到h[k]那一个链表
    //每一次把ne指向原来的头部，再更新头部
    e[idx]=x; ne[idx] = h[k];
    h[k]=idx++;
}

bool find(int x){
    int k = (x % N + N) % N;
    //在k对应的链表里找有没有对应的x
    for(int i = h[k]; i!=-1; i = ne[i])
        if(e[i] == x)
            return true;
    return false;
}

int main(){
    int n,x;
    cin >> n;

    memset(h,-1,N*4);

    while(n--){
        char op[2];
        cin >> op >> x;
        if(op[0] == 'I')
            insert(x);
        else{
            if(find(x)) puts("Yes");
            else puts("No");
        }
    }
}