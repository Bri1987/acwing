#include <iostream>
#include <vector>
#include <algorithm>

//去重就是离散化的过程，至于映射关系，没有使用map保存，每次用find现找现算

using namespace std;

typedef pair<int,int> PII;

const int N = 300010;

int n,m;
int a[N],S[N];

vector<int> alls;
vector<PII> add,query;

// 二分求出x对应的离散化的值
//int find(int x) // 找到第一个大于等于x的位置
//{
//    int l = 0, r = alls.size() - 1;
//    while (l < r)
//    {
//        int mid = l + r >> 1;
//        if (alls[mid] >= x) r = mid;
//        else l = mid + 1;
//    }
//    //加不加一与题目有关
//    return r + 1; // 映射到1, 2, ...n(用到前缀和，用1开始方便)
//}

//最后一个小于等于x的位置，也ok
int find(int x)
{
    int l = 0, r = alls.size() - 1;
    while (l < r)
    {
        int mid = (l + r + 1) >> 1;
        if (alls[mid] <= x) l = mid;
        else r = mid - 1;
    }
    return r+1;
}

int main(){
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        int x,c;
        cin >> x >> c;
        add.push_back({x,c});
        //将x放入要离散化的vector
        alls.push_back(x);
    }
    for(int i = 0; i < m; i++){
        int l ,r;
        cin >> l >> r;
        query.push_back({l,r});

        //**既然范围用到了这个数，那这个数也是需要离散化的**
        alls.push_back(l);
        alls.push_back(r);
    }
    //去重 , 就是离散化的过程
    sort(alls.begin(),alls.end());     //将所有值排序
    alls.erase(unique(alls.begin(),alls.end()),alls.end());   //去掉重复元素

    for(auto item : add){
        int x = find(item.first);
        //在离散化之后的坐标下加上要加的数
        a[x] += item.second;
    }

    //预处理前缀和
    S[0] = 0;
    for(int i = 1; i <= alls.size(); i++)
        S[i] = S[i - 1] + a[i];

    //处理询问
    for(auto item : query){
        int l = find(item.first);
        int r = find(item.second);
        cout << S[r] - S[l - 1] << endl;
    }
}