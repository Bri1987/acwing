#include <iostream>
#include <algorithm>

using namespace std;
typedef long long LL;

const int N = 50010;

struct Cow{
    int w,s;

    //按照wi+si从小到大的顺序**从顶往下**排
    bool operator<(const Cow& c)const{
        return w+s < c.w + c.s;
    }
}cow[N];

int main(){
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        int w,s;
        cin >> w >> s;
        cow[i] = {w,s};
    }

    sort(cow, cow + n);

    LL res = -2e9, sum = 0;
    //由于 wi+si从小到大的顺序排，所以i=0的其实在最上面, 这是从最顶上面的牛开始从轻往重走的
    for(int i = 0; i < n; i++){
        //即使在最上面的也要减s，这是题目中风险值的定义
        sum -= cow[i].s;
        //求的是所有奶牛的风险值中的最大值 的最小值
        res = max(res, sum);
        sum += cow[i].s + cow[i].w;  //最终走完一轮一头牛的结果就是留下一个重量，先补上之前减去的s，将一个重量留给在它下面的那头牛
    }
    cout << res;
    return 0;
}