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
    int n;
    cin >> n;
    while (n--){
        int a,b,m;
        cin >> a >> b >> m;
        //ax+my'=b
        int x,y;
        int d = extend_gcd(a,m,x,y);
        //1.! (a,m) | b
        if(b % d != 0){
            puts("impossible");
            continue;
        }
        //最后记得LL和%m，是担心x 乘完之后超出int范围
        cout << (LL)x * (b / d) % m << endl;
    }
    return 0;
}