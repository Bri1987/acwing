#include <iostream>

using namespace std;

const int N = 1000010;

int primes[N], cnt;     // primes[]存储所有素数
bool st[N];         // st[x]存储x是否被筛掉

//朴素
//void get_primes(int n)
//{
//    for (int i = 2; i <= n; i ++ )
//    {
//        //不用每一个数都算倍数删，只删去质数的倍数就可以了
//        if (st[i]) continue;
//
//        //在这个数之前删倍数都没筛到它，说明它一定是质数
//        primes[cnt ++ ] = i;
//        //筛去所有倍数
//        for (int j = i + i; j <= n; j += i)
//            st[j] = true;
//    }
//}

//线性
void get_primes(int n)
{
    for (int i = 2; i <= n; i ++ )
    {
        if (!st[i]) primes[cnt ++ ] = i;
        //其实边界条件就是primes[j]*i <= n，怕越界
        for (int j = 0; primes[j] <= n / i; j ++ )
        {
            //以primes[j]为最小质因子筛掉一个数
            st[primes[j] * i] = true;
            //如果下一行不break，比如让35走到了7，它筛掉了7*35，即5*7*7，被7筛掉了；等遍历到i=49的时候，又会被5*49筛掉，就低效了
            if (i % primes[j] == 0) break;
        }
    }
}

int main(){
    int n;
    cin >> n;
    get_primes(n);
    cout << cnt << endl;
    return 0;
}