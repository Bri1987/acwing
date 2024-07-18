#include <iostream>

using namespace std;

int get_euler(int x){
    int res = x;
    for(int i = 2; i <= x / i; i++ ){
        if(x % i == 0){
            while (x % i == 0) x /= i;
            // !! 注意是先除再乘
            res = res / i * (i - 1);
        }
    }
    //这个记得放for循环外面
    if(x > 1){
        res = res / x * (x - 1) ;
    }
    return res;
}

int main(){
    int m;
    cin >> m;
    while (m--){
        int x;
        cin >> x;
        cout << get_euler(x) << endl;
    }
    return 0;
}