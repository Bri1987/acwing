#include <iostream>

using namespace std;

const int N  = 100010;

//head表示虚拟头结点的next指针 ， 是头节点的下标
//e[N]表示value
//ne[N]表示next指针对应的索引是多少
//idx相当于指针，指当前已经用到了哪个点
int head,e[N],ne[N],idx;

void init(){
    head = -1;
    idx = 0;
}

//头插法 , 是直接插入变成第一个结点，而不是变成第一个结点后面
void add_to_head(int a){
    e[idx] = a;
    ne[idx] = head;  //它的下一个就是原来的第一个
    head = idx++;
}

//删除第k个插入的数后面的数
void delete_after_k(int k){
    //idx = 0对应第一个插入的数, idx = k - 1就是第k个插入的数
    if(k == 0){
        //删除头结点
        head = ne[head];
    }else {
        //找到要被删除的数的index
        int index = ne[k - 1];
        ne[k - 1] = ne[index];
    }
}

//表示在第 k个插入的数后面插入一个数 x（此操作中 k均大于 0）
void insert_after_k(int k , int x){
    //第k个插入的数索引是k-1
    e[idx] = x;
    ne[idx] = ne[k - 1];
    ne[k - 1] = idx++;
}

int main(){
    int M;
    cin >> M;
    init();
    for(int i = 0; i < M; i++){
        char c;
        cin >> c;
        if(c == 'I'){
            int k,x;
            cin >> k >> x;
            insert_after_k(k,x);
        } else if(c == 'D'){
            int k;
            cin >> k;
            delete_after_k(k);
        }else{
            //H
            int x;
            cin >> x;
            add_to_head(x);
        }
    }

    //head的初始值是-1 , ne[idx] = head使得最后结束时一定是-1
    for (int i = head; i != -1; i = ne[i]) cout << e[i] << ' ' ;
    cout << endl;
}