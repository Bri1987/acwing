#include <iostream>

using namespace std;

//时间复杂度为logn
//d | a && d | b --> d | a+b 和 d | ax+by，比如2 | 4 && 2 | 6 ---> 2 | 4 * 1+6 * 7

//a与b的最大公约数 = b与a mod b的最大公约数 （a > b）
//原理：
//a mod b = a - c*b
//先证明左边任何一个公约数都是右边的公约数：d | a && d | b --> d | 1 * a+b * (-c)
//再证明左边任何一个公约数都是右边的公约数：d | b && d | (a-c*b) --> d | c * b+ 1 * (a-c*b)
//所以两者等价

// a > b
int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}

int main(){
    int m;
    cin >> m;
    while (m--){
        int x,y;
        cin >> x >> y;
        int max = x > y ? x : y;
        int min = x < y ? x : y;
        cout << gcd(max,min) << endl;
    }
    return 0;
}