#include <bits/stdc++.h>
using namespace std;
int n,m,v[100010],w[100010],f[100010];
int main()
{
    cin>>n>>m;
    int cnt=1;
    for(int i=1;i<=n;i++)
    {
        int a,b,s;
        cin>>a>>b>>s;
        int k=1;
        if(s<0)s=1;
        else if(s==0)
            s = m/a;    //把01背包和完全背包先转化成多重背包，若为完全背包，则在最优情况下，只能取总体积/该物品体积向下取整
        while(k<=s)
        {
            v[cnt]=a*k;
            w[cnt]=b*k;
            s-=k;
            k*=2;
            cnt++;
        }
        if(s>0)
        {
            v[cnt]=s*a;
            w[cnt]=s*b;
            cnt++;
        }
    }//将多重背包进行二进制优化，变成01背包 
    for(int i=1;i<=cnt;i++)
    {
        for(int j=m;j>=v[i];j--)
        {
            f[j]=max(f[j],f[j-v[i]]+w[i]);
        }
    }//01背包问题
    cout<<f[m]<<endl;
    return 0;
}