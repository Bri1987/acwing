#include <iostream>

using namespace std;

const int N  = 100010;

// e[]表示节点的值，l[]表示节点的左指针，r[]表示节点的右指针，idx表示当前用到了哪个节点
//意思是 0始终是左端点，1始终是右端点，所有操作都在0和1中间进行
//index : 0 最左边结点........最右边结点 1
int e[N], l[N], r[N], idx;

// 初始化
void init()
{
    //0是左端点，1是右端点
    r[0] = 1, l[1] = 0;
    idx = 2;
}

//在第 K 个点右边插入一个 X
//在 k 的左边插入一个 数 等价于在 l[k] 的右边插入一个数 add(l[k],x)
void insert(int k , int x){
    e[idx] = x;
    l[idx] = k;
    r[idx] = r[k];
    l[r[k]] = idx;
    r[k] = idx++;
}

// 删除节点a
void remove_k(int k)
{
    l[r[k]] = l[k];
    r[l[k]] = r[k];
}

int main(){
    int M;
    cin >> M;
    init();
    for(int i = 0; i < M; i++){
        string c;
        cin >> c;
        if(c == "L"){
            int x;
            cin >> x;
            insert(0,x);
        }else if(c == "R"){
            int x;
            cin >> x;
            insert(l[1],x);
        }else if(c == "D"){
            int k;
            cin >> k;
            remove_k(k + 1);
        }else if(c == "IL"){
            int k,x;
            cin >> k >> x;
            //idx索引下标比第k个数多1(单链表是少1，但是这里0和1被定为头尾了，idx比单链表多了2)
            insert(l[k+1],x);
        }else {
            int k,x;
            cin >> k >> x;
            insert(k+1,x);
        }
    }
    for(int i = r[0]; i != 1; i = r[i]) cout << e[i] << ' ';
}