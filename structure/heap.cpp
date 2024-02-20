#include <iostream>

using namespace std;
const int N = 1000010;
//ph存的是第k个插入的点的下标index
//hp存的是堆里面的第几个点是第几个插入的点
//ph[j]=k则hp[k]=j
int h[N],ph[N],hp[N],size_h,idx;

//a,b是在h堆里的下标
void heap_swap(int a,int b){
    //hp[a]先得到它是第几个插入的点
    swap(h[a],h[b]);
    swap(hp[a],hp[b]);
    swap(ph[hp[a]],ph[hp[b]]);
}

void down(int u){
    //t代表初始值index或者一轮换下来的大值对应的index，递归处理
    int t = u;
    if(u*2<= size_h && h[u*2] < h[t]) t = u*2;
    if(u*2+1 <= size_h && h[u*2+1] < h[t]) t = u*2+1;
    if(u !=t){
        heap_swap(u,t);
        down(t);
    }
}

void up(int u){
    while (u / 2 && h[u/2] > h[u]){
        heap_swap(u/2,u);
        u /= 2;
    }
}

int main(){
    int n;
    cin >> n;
    string op;
    while (n--){
        cin >> op;
        if(op == "I"){
            int x;
            cin >> x;
            h[++size_h] = x;
            ph[++idx] = size_h;
            hp[size_h] = idx;
            up(size_h);
        } else if(op == "D"){
            int k;
            cin >> k;
            int h_idx = ph[k];
            //注意这里不能直接赋值覆盖，要改ph和hp
            heap_swap(h_idx,size_h);
            size_h--;
            up(h_idx);
            down(h_idx);
        } else if(op == "C"){
            int k,x;
            cin >> k >> x;
            int h_idx = ph[k];
            h[h_idx] = x;
            up(h_idx);
            down(h_idx);
        }else if(op == "PM"){
            cout << h[1] << endl;
        }else{
            //注意这里不能直接赋值覆盖，要改ph和hp
            heap_swap(1,size_h);
            size_h--;
            down(1);
        }
    }
}