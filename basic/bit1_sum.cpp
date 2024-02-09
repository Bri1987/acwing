#include <iostream>
using namespace std;

//lowbit(x): 返回x的最后一个1是多少 , x & -x = x& (~x + 1)可得（可以自己试试，补码,-x与~x+1都是补码），比如10101100返回100
int lowbit(int x){
    return x & -x;
}

int main(){
    int n;
    cin >> n;
    while (n--){
        int x;
        cin >> x;
        //求一个数有多少个1，可以用lowbit思想，减了多少次，就有多少个1
        int res = 0;
        while (x){
            x -= lowbit(x);
            res++;
        }
        cout << res << " ";
    }
}