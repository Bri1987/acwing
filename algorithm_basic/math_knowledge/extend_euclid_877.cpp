#include <iostream>

//找x,y ax+by=gcd(a,b)

using namespace std;
typedef long long LL;

// a > b
//返回最小公约数
int extend_gcd(int a, int b, int& x,int& y)
{
    if(!b){
        x = 1,y = 0;
        return a;
    }

    //x' , y'代表上一层的结果
    //d : bx' + (a mod b)*y' = (b,a % b) = (a,b)
    //a % b = a - [a/b]*b ，其中[]指下取整 =>
    //d : bx' + (a - [a/b]*b)*y' = (a,b) =>
    //ay' + b(x' - [a/b]*y') = d
    //所以这一轮的x = y' , y = x' - [a/b]*y'
    int d = extend_gcd(b, a % b, x, y);
    int copy_x = x;
    x = y;
    y = copy_x - (a/b) * y;
    return d;
}

int main(){
    int m;
    cin >> m;
    while (m--){
        LL a,b;
        cin >> a >> b;
        int x,y;
        extend_gcd(a,b,x,y);
        cout << x << " " << y << endl;
    }
    return 0;
}