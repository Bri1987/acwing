#include <iostream>
#include <cstring>

using namespace std;

/* 本题可以判断是稠密图，可以用邻接矩阵来写 , !! 不是所有都用邻接表才方便的 , 用邻接表也能做的就是了  */

const int N = 510;
int n , m;   //n个点，m条边
int d[N];    //记录1到每个点的距离
bool st[N];    //记录点是不是已经确定最短了
int g[N][N];    //为稠密阵所以用邻接矩阵存储

int dijkstra(){
    //1.初始化
    memset(d, 0x3f, sizeof d);
    d[1] = 0;
    //st[1] = true;   !! 不能要这句，要从第一个点开始走3. 更新

    // i只用来计数
    for(int i = 0;i < n; i++) {     //有n个点所以要进行n次 迭代
        int t = -1;       //t存储当前访问的点

        //2. 在还未确定最短路的点中，寻找这个点1出发距离最小的点
        for(int j = 1;j <= n; j++)   //这里的j代表的是从1号点开始
            if(!st[j] && ( t == -1|| d[t] > d[j]))   //t=-1是第一次，第一次无条件赋值
                t = j;
        st[t] = true;

        //3. 更新从t出发的能更新的所有点
        for(int j = 1;j <= n;j++)           //依次更新每个点所到相邻的点路径值
            d[j] =min(d[j],d[t]+g[t][j]);
    }

    if(d[n]==0x3f3f3f3f) return -1;  //如果第n个点路径为无穷大即不存在最低路径
    return d[n];
}

int main(){
    cin >> n >> m;
    //!! 初始化图 因为是求最短路径 , 所以每个点初始为无限大
    memset(g,0x3f,sizeof g);

    for(int i = 0; i < m; i++){
        int a,b,c;
        cin >> a >> b >> c;
        g[a][b]=min(g[a][b],c);     //如果发生重边的情况则保留最短的一条边
    }

    cout << dijkstra() << endl;
}

//邻接表版本
//#include <iostream>
//#include <cstring>
//
//using namespace std;
//
//const int N = 1000010;
//int n , m;   //n个点，m条边
//int d[510];    //记录1到每个点的距离
//bool st[510];    //记录点是不是已经确定最短了
//int h[N], w[N], e[N], ne[N], idx;
//
//// 添加一条边a->b
//void add(int a, int b, int c){
//    // 有重边也不要紧，假设1->2有权重为2和3的边，再遍历到点1的时候2号点的距离会更新两次放入堆中
//    // 这样堆中会有很多冗余的点，但是在弹出的时候还是会弹出最小值2+x（x为之前确定的最短路径），
//    // 并标记st为true，所以下一次弹出3+x会continue不会向下执行。
//    w[idx] = c;
//    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
//}
//
//int dijkstra(){
//    //1.初始化
//    memset(d, 0x3f, sizeof d);
//    d[1] = 0;
//    //st[1] = true;   !! 不能要这句，要从第一个点开始走3. 更新
//
//    // i只用来计数
//    for(int i = 0; i < n; i++) {     //有n个点所以要进行n次 迭代
//        int t = -1;       //t存储当前访问的点
//
//        //2. 在还未确定最短路的点中，寻找这个点1出发距离最小的点
//        for(int j = 1;j <= n; j++)   //这里的j代表的是从1号点开始
//            if(!st[j] && ( t == -1|| d[t] > d[j]))   //t=-1是第一次，第一次无条件赋值
//                t = j;
//        st[t] = true;
//
//        //3. 更新从t出发的能更新的所有点
//        for (int j = h[t]; j != -1; j = ne[j]){
//            int k = e[j];
//            if (d[k] > d[t] + w[j]){
//                d[k] = d[t] + w[j];
//            }
//        }
//    }
//
//    if(d[n]==0x3f3f3f3f) return -1;  //如果第n个点路径为无穷大即不存在最低路径
//    return d[n];
//}
//
//int main(){
//    cin >> n >> m;
//    memset(h, -1 ,sizeof h);
//
//    for(int i = 0; i < m; i++){
//        int a,b,c;
//        cin >> a >> b >> c;
//        add(a,b,c);
//    }
//
//    cout << dijkstra() << endl;
//}

