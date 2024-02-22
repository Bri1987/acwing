#include <iostream>

using namespace std;
const int N = 1000010;
int n;
//cur是当前的这种情况，state代表当前情况中对应数字是否被使用过
int cur[N],state[N];

//x代表这次是放入第几个数
void back_tracing(int x){
    //达到终止条件则收集结果
    if(x > n){
        for(int i = 0; i < n; i++)
            cout << cur[i] << " ";
        cout << endl;
        return;
    }

    for(int i = 1; i <= n; i++){
        //不选择重复数字，通过state判定
        if(!state[i]){
            //处理结点;
            cur[x-1] = i;
            state[i] = 1;
            //递归
            back_tracing(x+1);
            //回溯，去掉处理结点的结果；
            state[i] = 0;
        }
    }
}

int main(){
    cin >> n;
    //从放入第一个数开始
    back_tracing(1);
}
