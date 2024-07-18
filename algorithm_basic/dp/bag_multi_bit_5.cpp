#include <iostream>

using namespace std;

//N开到25000，最多1000 * log2000个新物品
const int N = 25000, M = 2010;

int n,m;
int v[N],w[N];
int f[N];

int main(){
    int cnt=0; //要将一个物品拆成多个新物品, 记录拆分后的物品总数

    cin >> n >> m;
    //注意这里是1-n，与后面方程匹配对应
    for(int i = 1; i <= n; i++){
        //当前物品的体积，价值，个数
        int a,b,s;
        cin >> a >> b >> s;
        int k = 1;
        while (k <= s){
            cnt++;
            v[cnt] = a*k;
            w[cnt] = b*k;
            s -= k;      //注意s -= k, 相当于拿到1,2,4,8,...,64的时候s是73
            k <<= 1;
        }
       if(s > 0){
           cnt++;
           v[cnt] = a*s;
           w[cnt] = b*s;
       }
    }

    //相当于就是cnt个物品的01背包
    for(int i = 1; i <=cnt ;i++)
        for(int j = m; j >=v[i] ;j--){
            f[j] = max(f[j],f[j - v[i]] + w[i]);
        }

    cout << f[m] << endl;
    return 0;
}