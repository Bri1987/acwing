#include <iostream>
#include <vector>

using namespace std;
typedef long long LL;

int n;

LL exgcd(LL a, LL b, LL& x,LL& y)
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
    LL d = exgcd(b, a % b, x, y);
    LL copy_x = x;
    x = y;
    y = copy_x - (a/b) * y;
    return d;
}


int main(){
    cin >> n;
    //用一个bool值存储当前是否已经无解了
    bool has_answer = true;

    LL a1,m1;
    cin >> a1 >> m1;
    for(int i = 1; i < n;i++){
        int a2, m2;
        cin >> a2 >> m2;

        //求k1a1+m1 = k2a2 + m2，k1a1-k2a2 = m2-m1，求k1,k2
        LL k1,k2;
        LL d = exgcd(a1,-a2,k1,k2);
        if((m2-m1) % d){
            has_answer = false;
            break;
        }
        k1 *= (m2 - m1) / d;
        //为了不溢出，让k1成为最小的正整数解 , k1 - nt使得k1 >0, 其实也就是求余数了
        //k1的通解 k1+k*a2/d
        LL t = abs(a2 / d);
        //(k1 % t + t)这样可以解决余数为负数(c++求mod可能求出负数)，得到k1最小值！
        k1 = (k1 % t + t) % t;

        //更新m1准备下一轮，x = x0+ka
        m1 = a1*k1 + m1;
        //求一个正的最小公倍数，并更新a1
        a1 = abs(a1 / d * a2);
    }

    if(has_answer){
        //求一个x的最小值，与之前求k1最小值一样，(c++求mod可能求出负数) , m1 % a1 + a1求出一个正余数，得到一个最小值x输出 x=a1k1 + m1
        cout << (m1 % a1 + a1) % a1 << endl;
    }else
        puts("-1");
    return 0;
}