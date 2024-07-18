#include <iostream>
#include <vector>

using namespace std;
typedef long long LL;

const int N = 5010;

int primes[N],cnt;
bool st[N];
int sum[N];     // 存储每个质数的次数

void get_primes(int n){
    for(int i = 2; i <= n ;i++){
        if(!st[i]) primes[cnt++] = i;
        for(int j = 0; primes[j] <= n / i ;j++){
            st[primes[j] * i] = true;
            if(i % primes[j] == 0) break;
        }
    }
}


//求n的阶乘中包含p的次数
int get(int n, int p)       // 求n！中的次数
{
    int res = 0;
    while (n)
    {
        res += n / p;
        n /= p;
    }
    return res;
}

vector<int> mul(vector<int> a, int b)       // 高精度乘低精度模板
{
    vector<int> c;
    int t = 0;
    for (int i = 0; i < a.size(); i ++ )
    {
        t += a[i] * b;
        c.push_back(t % 10);
        t /= 10;
    }

    while (t)
    {
        c.push_back(t % 10);
        t /= 10;
    }

    return c;
}

int main(){
    int a,b;
    cin >> a >> b;

    //1. 线性筛1-a中所有质数
    get_primes(a);

    //2.求出阶乘中包含质数的次数
    //求每个质因数的次数
    for (int i = 0; i < cnt; i ++ )
    {
        int p = primes[i];
        //分子/分母，即分子各质数的次数 - 分母各质数的次数
        sum[i] = get(a, p) - get(b, p) - get(a - b, p);
    }

    //3.高精度乘法算个结果
    vector<int> res;
    res.push_back(1);

    for (int i = 0; i < cnt; i ++ )     // 用高精度乘法将所有质因子相乘
        for (int j = 0; j < sum[i]; j ++ )
            res = mul(res, primes[i]);
    for(int i = res.size() - 1; i>= 0; i--)
        cout << res[i];
    return 0;
}