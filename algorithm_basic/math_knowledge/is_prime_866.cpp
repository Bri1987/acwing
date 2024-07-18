#include <iostream>

using namespace std;

bool is_prime(int x)
{
    if (x < 2) return false;
    // !! 注意不能 i*i <= x，数字大的时候会溢出！！
    for (int i = 2; i <= x / i; i ++ )
        if (x % i == 0)
            return false;
    return true;
}

int main(){
    int n;
    cin >> n;
    while (n--){
        int x;
        cin >> x;
        if(is_prime(x))
            puts("Yes");
        else
            puts("No");
    }
}