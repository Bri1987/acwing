#include<iostream>
using namespace std;
const int N = 1e6 + 10;

int main()
{
    int n, k, q[N], a[N];//q[N]存的是数组下标

    int tt = -1, hh=0;//hh队列头 tt队列尾
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin>>n>>k;
    for(int i = 0; i <n; i ++) cin>>a[i];
    for(int i = 0; i < n; i ++)
    {
        //维持滑动窗口的大小
        //当队列不为空(hh <= tt) 且 当当前滑动窗口的大小(i - q[hh] + 1)>我们设定的
        //滑动窗口的大小(k),队列弹出队列头元素以维持滑动窗口的大小
        if(hh <= tt && k < i - q[hh] + 1)
            hh ++;
        //构造单调递增队列
        //当队列不为空(hh <= tt) 且 当队列队尾元素>=当前元素(a[i])时,那么队尾元素
        //就一定不是当前窗口最小值,删去队尾元素,加入当前元素(q[ ++ tt] = i)
        //注意是从队尾开始删，因为队尾是相对较大的元素
        while(hh <= tt && a[q[tt]] >= a[i])
            tt --;
        q[ ++ tt] = i;
        if(i + 1 >= k) printf("%d ", a[q[hh]]);
    }
    puts("");
    hh = 0,tt = -1;
    for(int i = 0; i < n; i ++)
    {
        if(hh <= tt && k < i - q[hh] + 1) hh ++;
        while(hh <= tt && a[q[tt]] <= a[i]) tt --;
        q[ ++ tt] = i;
        if(i + 1 >= k ) printf("%d ", a[q[hh]]);
    }
    return 0;
}