#include <iostream>

using namespace std;
const int N = 100010;
int h[N],size_h;

void down(int u){
    //t代表初始值index或者一轮换下来的大值对应的index，递归处理
    int t = u;
    if(u*2<= size_h && h[u*2] < h[t]) t = u*2;
    if(u*2+1 <= size_h && h[u*2+1] < h[t]) t = u*2+1;
    if(u !=t){
        swap(h[u],h[t]);
        down(t);
    }
}

int main(){
    int n,m;
    cin >> n >> m;
    for(int i =1; i <= n; i++)
        cin >> h[i];
    size_h = n;
    //把数组建成堆
    //最后一层的叶子结点不用管
    for(int i = n/2; i>0 ; i--)
        down(i);

    while (m--){
        cout << h[1] << " ";
        //删掉堆顶
        h[1] = h[size_h];
        size_h--;
        down(1);
    }
}