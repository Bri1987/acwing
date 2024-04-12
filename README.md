# ACWING

## 第一章 基础算法（一）

### 排序

#### 快速排序

分治思想：

1. 确定分界点：left or middle or right......
2. 调整左右，比如将比分界点小的放左边，比分界点大的放右边
3. 递归处理左右两段



```c++
void quick_sort(int q[],int l, int r){
    if(l >= r) return;

    //1. 确定分界点x
    //注意这里的i和j都比元素范围要大1 , 因为在后面的步骤中会先左移右移（swap之后肯定会先移动），所以将第一次也统一
    int i = l - 1, j = r + 1, x = q[(l + r) >> 1];

    //2. 调整左右，比如将比分界点小的放左边，比分界点大的放右边
    while(i < j){
        while (q[++i] < x);
        while (q[--j] > x);
        //注意还需判断一次 i < j
        if(i < j)
            swap(q[i],q[j]);
    }

    //3. 递归处理左右两段
    //注意判断条件时不能用i，因为此时如果退出则状态一定是 i >= j，所以取最小的j
    quick_sort(q,l,j);
    quick_sort(q,j+1 , r);
}
```





#### 归并排序

1. 递归排序左边和右边
2. 归并，将两个有序的数组合并为一个有序的数组
3. 将tmp数组重新赋值回q数组



```c++
void merge_sort(int q[],int l, int r){
    if(l >= r) return;

    //1. 递归排序左边和右边
    int mid = (l + r) >>1;
    merge_sort(q,l,mid);
    merge_sort(q,mid + 1,r);

    //2. 归并，将两个有序的数组合并为一个有序的数组
    int *tmp = new int[r-l+1];
    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r){
        if(q[i] < q[j])
            tmp[k++] = q[i++];
        else
            tmp[k++] = q[j++];
    }

    while (i <= mid) tmp[k++] = q[i++];
    while (j <= r) tmp[k++] = q[j++];

    //3. 赋值回原来的q
    for(i = l,j = 0; i <= r ;i++,j++){
        q[i] = tmp[j];
    }
}
```



### 二分法

#### 整数二分

有单调性的能二分，能二分的不一定需要有单调性

本质：边界

假设在绿色部分的是正确的，红色部分是不包含的

![image-20240121222243735](./img/image-20240121222243735.png)

二分法获得红色点：

1. 找mid = (l+r+**1**)>>1，判断中间值是不是满足性质（这里假设是判断mid在不在红色那边）
2. if(check(mid))
   - true 即mid处于红色部分：红色的边界点一定在[mid,r] l=mid
   - false 即mid处于绿色部分：红色的边界点一定在 [l,mid-1] r = mid-1，



二分法获得绿色点：

1. 找mid = (l+r)>>1，判断中间值是不是满足性质（这里假设是判断mid在不在绿色那边）
2. if(check(mid))
   - true 即mid处于绿色部分：绿色的边界点一定在[l,mid] r=mid
   - false 即mid处于红色部分：绿色的边界点一定在 [mid+1,r] l=mid+1



注意找红点时因为有r=mid-1，需要在计算mid时用l+r+1，需要避免死循环，因为r在-1后可以需要+1弥补下取整

```c++
bool check(int x) {/* ... */} // 检查x是否满足某种性质

// 区间[l, r]被划分成[l, mid]和[mid + 1, r]时使用：
//找绿
//找左界限的，第一个....
int bsearch_1(int l, int r)
{
    while (l < r)
    {
        int mid = l + r >> 1;
        if (check(mid)) r = mid;    // check()判断mid是否满足性质
        else l = mid + 1;
    }
    return l;
}
// 区间[l, r]被划分成[l, mid - 1]和[mid, r]时使用：
//找红
//找右界限的，最后一个....
int bsearch_2(int l, int r)
{
    while (l < r)
    {
        int mid = l + r + 1 >> 1;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }
    return l;
}
```



#### 浮点二分

```c++
bool check(double x) {/* ... */} // 检查x是否满足某种性质

double bsearch_3(double l, double r)
{
    const double eps = 1e-6;   // eps 表示精度，取决于题目对精度的要求
    while (r - l > eps)
    {
        double mid = (l + r) / 2;
        if (check(mid)) r = mid;
        else l = mid;
    }
    return l;
}
```



## 第一章 基础算法（二）

### 高精度

用数组存大整数，个位等低位在小索引

#### 高精度加法

2种情况：

- Ai + Bi
- Ai + Bi + C~i-1~(t)

```cpp
std::vector<int> add(std::vector<int> A, std::vector<int> B){
    if(B.size() > A.size())
        return add(B,A);
    int t = 0;
    std::vector<int> C;
    for(int i = 0; i < A.size(); i++){
        //上一次循环包含了进位
        t += A[i];
        if(i < B.size())
            t += B[i];

        C.push_back(t % 10);
        t /= 10;
    }
    if(t)
        C.push_back(t);
    return C;
}
```



#### 高精度减法

首先：

- A - B = A -B(A >= B)
- A - B = -(B - A)

需要先判断A,B大小



2种情况：

- Ai - Bi (Ai >= Bi)
- Ai - Bi + 10 - t

```cpp
//判断是否有 A >=B
bool cmp(std::vector<int> A, std::vector<int> B){
    if(A.size() != B.size())
        return A.size() > B.size();
    for(int i = A.size() - 1; i >= 0; i--){
        if(A[i] != B[i])
            return A[i] > B[i];
    }
    return true;
}

//输入进来一定是大数-小数 , A.size() >= B.size()
std::vector<int> sub(std::vector<int> A, std::vector<int> B){
    int t = 0;
    std::vector<int> C;
    for(int i = 0; i < A.size(); i++){
        t = A[i] - t;
        if(i < B.size())
            t -= B[i];
        //+10为避免t此刻是负数
        C.push_back((t + 10) % 10);

        if(t < 0) t = 1;
        else t = 0;
    }

    //删除所有前导0，比如003
    while (C.size() > 1 && C.back() == 0)
        C.pop_back();
    return C;
}
```



#### 高精度乘法

目前只处理了大数*小数

(Ai * Bi + t~i-1~) % 10

ti = (Ai * Bi + t~i-1~) / 10

```cpp
#include <iostream>
#include <vector>

//默认A是大数，B是小数
std::vector<int> mul(std::vector<int> A, int B){
    int t = 0;
    std::vector<int> C;
    for(int i = 0; i < A.size(); i++){
        //上一次循环包含了进位
        t += A[i] * B;

        C.push_back(t % 10);
        t /= 10;
    }
    if(t)
        C.push_back(t);

    //如果t是0的话，还是得删个前导0
    while (C.size() > 1 && C.back() == 0) C.pop_back();
    return C;
}
```



#### 高精度除法

目前只处理大数 / 小数

**左一位除完的余数 * 10 + Ai **是本次用来除的数

```cpp
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

//默认A是大数，B是小数
std::tuple<std::vector<int>,int> div(std::vector<int> A, int B){
    int t = 0;
    std::vector<int> C;
    for(int i = 0; i < A.size(); i++){
        //t是余数
        //t先是这次拿来除的数 , 左一位除完的余数 * 10 + Ai 是本次用来除的数
        t = A[i] + t * 10;
        C.push_back( t / B);
        t %= B;
    }

    //倒转一下C，方便删除前导0
    std::reverse(C.begin(),C.end());
    //删除前导0
    while (C.size() > 1 && C.back() == 0) C.pop_back();
    return {C,t};
}
```



### 前缀和

#### 一维前缀和

a1 , a2 , a3 , a4 ... an **注意下标是从1开始**

前缀和Si = a1 + a2 + ... + ai

作用：

求[a~l~,a~r~]的和 = S~r~ - S~l-1~



定义S0 = 0，前缀和比如S10也可以表示为S10 - S0

```cpp
S[i] = a[1] + a[2] + ... a[i]
a[l] + ... + a[r] = S[r] - S[l - 1]
```



```cpp
#include <iostream>

int main(){
    int n,m;
    scanf("%d %d",&n,&m);

    //计算前缀和
    //s0 = 0, 都往后挪一个
    int sum_prefix[n + 1];
    sum_prefix[0] = 0;
    int x;
    for(int i = 1; i <= n; i++){
        std::cin >> x;
        sum_prefix[i] = sum_prefix[i - 1] + x;
    }

    int l ,r;
    for(int i = 0; i < m; i++){
        //读入l, r
        scanf("%d %d",&l,&r);
        printf("%d\n",sum_prefix[r] - sum_prefix[l - 1]);
    }
}
```





#### 二维前缀和

![image-20240207181523669](./img/image-20240207181523669.png)

Sij代表小正方形内数的和

**如想求图中蓝正方形内数的和：S~x2y2~ - S~x2,y1-1~ - S~x1-1,y2~ + S~x1-1,y1-1~**

![image-20240207212540797](./img/image-20240207212540797.png)



**前缀和：Sij = S~i-1,j~ + S~i,j-1~ - S~i-1,j-1~ + aij**

```cpp
#include <iostream>

int main(){
    int n,m,q;
    int x;
    std::cin >> n >> m >> q;
    int sum_prefix[n + 1][m + 1];
    for(int i = 0; i <= m; i++)
        sum_prefix[0][i] = 0;
    for(int i = 0; i <= n; i++)
        sum_prefix[i][0] = 0;

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++){
            std::cin >> x;
            sum_prefix[i][j] = sum_prefix[i - 1][j] + sum_prefix[i][j - 1] - sum_prefix[i - 1][j - 1] + x;
        }

    for(int i = 0; i < q; i++){
        int x1,y1,x2,y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        std::cout << sum_prefix[x2][y2] - sum_prefix[x1 - 1][y2] - sum_prefix[x2][y1 - 1] + sum_prefix[x1 - 1][y1 - 1] << std::endl;
    }
}
```





### 差分

#### 一维数组

有数组a1,a2,...an

要构造b数组使得ai = b1 + b2 +...+bi，即使得a数组是b数组的前缀和，那么b数组就称为a数组的差分

比如一维：

b1 = a1

b2 = a2 - a1

b3 = a3 - a2

...

bn = an - a~n-1~



作用示例：需要将a数组[l,r]索引的每个元素都加上constant c

可以在b差分上用O(1)操作完成：

由于a数组是通过求b数组的前缀和得到，在l处+c意味着a数组从l开始的所有元素都加上了c（算前缀和时都要算B[l]），在r+1处-c意味着a数组从r+1开始的所有元素都减去了c

![image-20240207214055248](./img/image-20240207214055248.png)



**假设a数组初始时全都为0，那么b差分数组初始时也全都为0，可以将实际的a数组看成n次插入操作，每次差分数组b将插入a1元素这个操作看成在原数组（初始为全0）基础上的[1,1]区间加上a1**

即构造bn到完成要求整个过程只有一个操作：``给区间[l, r]中的每个数加上c：B[l] += c, B[r + 1] -= c``

```cpp
#include <iostream>

using namespace std;

void insert(int l ,int r, int c, int b[]){
    b[l] += c;
    b[r + 1] -= c;
}

int main(){
    int n,m;
    cin >> n >> m;
    //insert算法涉及到r + 1，所以数组b多开一列
    int a[n + 1],b[n + 2];
    a[0] = 0;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    for(int i = 0; i <= n + 1; i++)
        b[i] = 0;

    for(int i = 1; i <= n; i++)
        //假设a数组初始时全都为0，那么b差分数组初始时也全都为0，可以将实际的a数组看成n次插入操作，差分数组b将插入a1元素看成在原数组（初始为全0）基础上的[1,1]区间加上a1
        //所以全过程包括bn的初始化都是insert操作
        insert(i,i,a[i],b);

    while (m--){
        int l,r,c;
        cin >> l >> r >> c;
        insert(l,r,c,b);
    }

    //求最终数组,即已知bn差分数组，求an前缀和数组
    for(int i = 1; i <= n;i++){
        a[i] = b[i] + a[i - 1];
        printf("%d ",a[i]);
    }
    return 0;
}
```



#### 二维数组

```
给以(x1, y1)为左上角，(x2, y2)为右下角的子矩阵中的所有元素加上c：
S[x1, y1] += c, S[x2 + 1, y1] -= c, S[x1, y2 + 1] -= c, S[x2 + 1, y2 + 1] += c
```

初始化操作的每一次插入 相当于对(i,j)到(i,j)范围加上一个数

```cpp
#include <iostream>

using namespace std;

void insert(int x1, int y1, int x2, int y2, int c, int **b){
    b[x1][y1] += c;
    b[x2 + 1][y1] -= c;
    b[x1][y2 + 1] -= c;
    b[x2 + 1][y2 + 1] += c;
}

int main(){
    int n,m,q;
    cin >> n >> m >> q;
    int a[n + 1][m + 1];
    //注意这里和下面清0的时候要给b分内存
    //由于insert涉及到边界+1，这里需要多+2多分内存
    int** b = new int*[n + 2];
    //清0操作
    //1. b数组
    for(int i = 0; i <= n + 1; i++){
        b[i] = new int[m + 2];
        for(int j = 0; j <= m + 1;j++)
            b[i][j] = 0;
    }
    //2. a数组
    for(int i = 0; i <= n; i++)
        a[i][0] = 0;
    for(int i = 0; i <= m; i++)
        a[0][i] = 0;

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            cin >> a[i][j];

    //初始化b差分数组
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            insert(i, j, i, j, a[i][j], b);

    while (q--){
        int x1,y1,x2,y2,c;
        cin >> x1 >> y1 >> x2 >> y2 >> c;
        insert(x1,y1,x2,y2,c,b);
    }

    //求最终数组,即已知bn差分数组，求an前缀和数组
    for(int i = 1; i <= n;i++){
        for(int j = 1; j <= m; j++){
            a[i][j] = b[i][j] + a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
            cout << a[i][j] << " ";
        }
        cout << endl;
    }

    //释放b占用内存
    for (int i = 0; i <= n + 1; i++) {
        delete[] b[i];
    }
    delete[] b;
    return 0;
}
```



## 第一章 基础算法（三）

### 双指针算法

![image-20240208161839184](./img/image-20240208161839184.png)

### 位运算

1. 求一个整数n的二进制表示的第k位数是几

   - 先把第k位数字移到最后一位 n >> k
   - 看看个位是几 x& 1

   即(n >> j) & 1

2. lowbit(x): 返回x的最后一个1是多少 , x & -x = x& (~x + 1)可得（可以自己试试，补码,-x与~x+1都是补码），比如10101100返回100

   

   求一个数有多少个1，可以用lowbit思想，减了多少次，就有多少个1

   示例：

   ```cpp
   #include <iostream>
   using namespace std;
   
   //lowbit(x): 返回x的最后一个1是多少 , x & -x = x& (~x + 1)可得（可以自己试试，补码,-x与~x+1都是补码），比如10101100返回100
   int lowbit(int x){
       return x & -x;
   }
   
   int main(){
       int n;
       cin >> n;
       while (n--){
           int x;
           cin >> x;
           //求一个数有多少个1，可以用lowbit思想，减了多少次，就有多少个1
           int res = 0;
           while (x){
               x -= lowbit(x);
               res++;
           }
           cout << res << " ";
       }
   }
   ```

   

### 整数保序离散化

离散化要用vector



值域大，比如0-10^9，但是个数远不如那么多，但是可能需要开数组，但我们不能开到10 ^9那么大，于是需要选出一些数，映射，比如：

![image-20240208183214019](./img/image-20240208183214019.png)

这就叫离散化。

问题：

1. a中可能有重复元素，所以需要去重，**去重就是离散化的过程，至于映射关系，没有使用map保存，每次用find现找现算**

   去重写法：

   ```cpp
   vector<int> alls;    //存储所有待离散化的值
   sort(alls.begin(),alls.end());     //将所有值排序
   alls.erase(unique(alls.begin(),alls.end()),alls.end());   //去掉重复元素
   ```

   unique会把重复元素都丢到后面，erase将重复元素开始的索引到end全给删掉就好

2. 如何算出a[i]离散化后的值是多少（二分）

   ```cpp
   // 二分求出x对应的离散化的值
   int find(int x) // 找到第一个大于等于x的位置
   {
       int l = 0, r = alls.size() - 1;
       while (l < r)
       {
           int mid = l + r >> 1;
           if (alls[mid] >= x) r = mid;
           else l = mid + 1;
       }
       //加不加一与题目有关
       return r + 1; // 映射到1, 2, ...n
   }
   ```

   由于这里去重唯一且一定有对应值，所以找红色（右界限，即最后一个小于等于x的位置）也是ok的

   ```cpp
   //找到最后一个小于等于x的位置
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
   ```

   

### 区间合并

1. 按区间左端点排序

2. 扫描整个区间，把所有可能的区间合并

   ![image-20240209103142181](./img/image-20240209103142181.png)

   由于按照左端点排序了，只可能出现三种绿色情况，而不会出现红色情况

   - 每次维护一个当前的区间

   ```cpp
   // 将所有存在交集的区间合并
   void merge(vector<PII> &segs)
   {
       vector<PII> res;
   
       sort(segs.begin(), segs.end());
   
       int st = -2e9, ed = -2e9;
       for (auto seg : segs)
           //左端大于right，则一定是新段
           //由于是左端升序，之后的interval的左端也一定大于之前段的right，固之前的段不用再考虑
           if (ed < seg.first)
           {
               if (st != -2e9) res.push_back({st, ed});
               st = seg.first, ed = seg.second;
           }
           else ed = max(ed, seg.second);
   
       //这是防止输入区间为空
       if (st != -2e9) res.push_back({st, ed});
   
       segs = res;
   }
   ```

   也可以是：

   ```cpp
   //以左端排序
       sort(intervals.begin(),intervals.end());
       int res = 1;
       int right = intervals[0].second;
       for(int i = 1; i < n; i++){
           if(intervals[i].first <= right)
               right = max( right, intervals[i].second);
           else{
               //左端大于right，则一定是新段
               //由于是左端升序，之后的interval的左端也一定大于之前段的right，固之前的段不用再考虑
               res++;
               right = intervals[i].second;
           }
       }
       //判断一下非空
       if(intervals.empty())
           res = 0;
       cout << res << endl;
   ```

   

## 第二章 数据结构（一）

### 链表

用数组模拟链表、栈、队列等数据结构。**用结构体的化效率会慢，做笔试题里不会采用动态new Node()的方式**

单链表：邻接表：存储图和树

#### 单链表

- value用e表示，e[N]
- ne[N]表示某个点的next指针的下标索引是多少
- idx相当于指针，指当前已经用到了哪个点

![image-20240210121933193](D:\ClionLinux\acwing\img\image-20240210121933193.png)

```cpp
//head表示虚拟头结点的next指针 ， 是头节点的下标
//e[N]表示value
//ne[N]表示next指针对应的索引是多少
//idx相当于指针，指当前已经用到了哪个点
int head,e[N],ne[N],idx;

void init(){
    head = -1;
    idx = 0;
}

//头插法 , 是直接插入变成第一个结点，而不是变成第一个结点后面
void insert(int a){
    e[idx] = a;
    ne[idx] = head;  //它的下一个就是原来的第一个
    head = idx++;
}

//删除头结点
void remove(){
    head = ne[head];
}
```



#### 双链表

- l[N]：存左边点的index
- r[N]：存右边点的index
- 直接让下标为0的点为head，下标为1的点是tail
- 还是有e[N]和idx

没有专门的head了

```
//意思是 0始终是左端点，1始终是右端点，所有操作都在0和1中间进行
//index : 0 最左边结点........最右边结点 1
```

```cpp
const int N  = 100010;

// e[]表示节点的值，l[]表示节点的左指针，r[]表示节点的右指针，idx表示当前用到了哪个节点
int e[N], l[N], r[N], idx;

// 初始化
void init()
{
    //0是左端点，1是右端点
    r[0] = 1, l[1] = 0;
    idx = 2;
}

// 在节点a的右边插入一个数x
void insert(int a, int x)
{
    e[idx] = x;
    l[idx] = a, r[idx] = r[a];
    l[r[a]] = idx, r[a] = idx ++ ;
}

// 删除节点a
void remove(int a)
{
    l[r[a]] = l[a];
    r[l[a]] = r[a];
}
```



### 栈

数据结构：

就按照习惯的top从-1开始就好

```cpp
// tt表示栈顶
int stk[N], tt = 0;

// 向栈顶插入一个数
stk[ ++ tt] = x;

// 从栈顶弹出一个数
tt -- ;

// 栈顶的值
stk[tt];

// 判断栈是否为空，如果 tt > 0，则表示不为空
if (tt > 0)
{

}
```

#### 单调栈

给定一个序列，求一下在这个序列当中 每一个数左边（右边）**离它最近**比它大（小）的数

```cpp
常见模型：找出每个数左边离它最近的比它大/小的数
int tt = 0;
for (int i = 1; i <= n; i ++ )
{
    while (tt && check(stk[tt], i)) tt -- ;
    stk[ ++ tt] = i;
}
```

```
//每个元素进栈的时候如果栈里什么都没有说明左边没有比它小的
    //每进一个新元素，会把比它大的元素都掏出栈，但是如果它最大的话就它直接入栈。这样栈中留下的就只有比当前数小的数了，大的都被踢走了，加快了速度（比如下例2把3，4踢走）
    //理解为0 1 x，不知道x是不是比1大，不能把1踢出来；但是如果是1 0 x，无论如何第一个比x小的也不可能是1，所以0入栈时就可以把1踢掉了
    //如果把比它大的元素都掏出栈之后，栈空了，说明左边没有比它小的了

    //比如 3 4 2 7
    //3进栈时为空，所有直接输出-1 , 3进栈
    //4进栈时3比它小，所以输出3，4入栈
    //2进栈时栈顶元素4，3大于它，他们都出栈，出栈后栈空了，所以是-1
```





### 队列

数据结构：

注意hh设置为0，默认第一次取head是有东西的，保证hh比tt大是为了在判断empty的时候可以用tt >= hh作为not empty的条件

```cpp
int q[N];
//注意hh设置为0，默认第一次取head是有东西的，保证hh比tt大是为了在判断empty的时候可以用tt >= hh作为not empty的条件
int hh = 0,tt = -1;

void push(int x){
    q[++tt] = x;
}

void pop(){
    hh++;
}
```



#### 单调队列：滑动窗口

找最小的话，如果新插入的数比原先队尾元素还小，之前的队尾元素就可以删掉了（如果大则之前队尾的不能删，也不能删这个大的，因为队尾可以被滑掉）

找一个滑动窗口的最小值：

队列q存的是下标

- 第一步：判断hh是不是已经被窗口滑过了，划过了的话需要hh++
- 第二步：**idx又靠后值又小的数出现，说明之前的小数之后再也不会用了，永久性删除**
- 第三步：用对应下标存值

```cpp
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
        while(hh <= tt && a[q[tt]] >= a[i])
            tt --;
        q[ ++ tt] = i;
        if(i + 1 >= k) printf("%d ", a[q[hh]]);
    }
```

举个例子：

```
8 3
1 3 -1 -3 5 3 6 7
```

- 1入队列，q[0] = 0; tt=1

- 3入队列，q[1] = 1; tt =2

- -1来了，-1比1，3都小，**idx又靠后值又小，说明1，3今后再也不会被用到了，永久性删除1，3**；

  于是q[0]= 2，tt=1。第一次输出a[q[0]] = a[2] = -1    **//2**

- -3来了，-3比-1小，同理删除-1，于是q[0] = 3,tt=1，输出a[q[0]] = a[3] = -3

- 5来了，q[1]=4, tt=2，输出a[q[0]] = a[3] = -3

- 3来了，3比5小，于是q[1]=5,tt=2，q[0]仍等于3，输出a[q[0]] = a[3] = -3

- 6来了，由于k = 3 < 6 - q[hh]=3 + 1，所以原先的hh经过滑动窗口之后就没有了，hh得右移。这里只if没有while的原因是，滑动窗口每次只划一个，一次只可能淘汰 一个,hh只用+1。于是q[2]=6 , tt=3，输出a[q[1]] = a[5] = 3

- ...

  

### KMP

S:要匹配的串，p：短串，看p是否为S的子串

暴力：

```cpp
for(int i=1;i<=n;i++){
    bool flag = true;
    for(int j =1; j<=m;j++){
        //只要有一个数不匹配，就可以让i++，然后再从j=1开始匹配了
        if(s[i+j-1] != p[j]){
            flag = false;
            break;
        }
    }
}
```



文本串：aabaabaaf

模式串：aa**b**aaf



前缀与后缀相等的最长字符个数：

a           0

aa         1

aab       0

aaba     1

aabaa    2

aabaaf   0

所以aabaaf对应的前缀串：

​        010120

第一次匹配在f处失败之后，看前缀aabaa的值为2，意思是

- 这样做成立：因为在后半部分的aa是对上了的，前两个aa一定可以直接对上，接下来可以直接从f对应的b开始对着看b
- 再往前追溯会浪费：这样做其实直接从对index=0的a变成了对index=3的a，不从index=1的a开始对是因为前后缀是aa能对上，而不是aab与baa能对上，如果前后缀相等长为3，也就是说后半段baa的可以复用，那其实就会从index=2的b开始对，但是毕竟aab与baa不匹配，所以从index=2开始不行。所以最早必须留到index=3的a开始匹配



代码：next[i] = j;意味着p[1,j] = p[i-j+1]，就是意味着一个前后缀相等

求next数组：

```cpp
next[0] = -1;
for (int i = 1, j = -1; i < len; i ++)
{
    while (j != -1 && s[i] != s[j + 1]) // 前后缀匹配不成功
    {
        // 反复令 j 回退到 -1，或是 s[i] == s[j + 1]
        j = next[j];
    }
    if (s[i] == s[j + 1]) // 匹配成功
    {
        j ++; // 最长相等前后缀变长
    }
    next[i] = j; // 令 next[i] = j
}   
```

![image-20240211210824870](D:\ClionLinux\acwing\img\image-20240211210824870.png)

求17对应的next数组值，假设16前面的最长前缀为7，8前面的最长前缀为3：

- 如果val[8]==val[16]：直接把当前最长前缀长度+1，8+1=9
- 如果不等于，则j=ne[8]=4：
  - 找前缀为4是有可能正确的：ne[8]=4所以123=567 , 又因为n[16]=8所以1234567=9 10 11 12 13 14 15 ，所以123=567=9 10 11=13 14 15，所以123= 13 14 15，于是如果4=16，则长为4满足
  - 大于4的前缀一定是错误的：在8处，123=567且1234 != 4567(4123)。假设想找前缀长为5的，即12345 = 12 13 14 15 16 = 4567 16 = 4123 16。因为之前已经有1234 != 4123，所以不满足，最理想的就是从4处再找



## 第二章 数据结构（二）

### trie树

用来快速存储和查找字符串集合的数据结构

**能用trie做的一定限制了字母种类数目**，比如835题为26

但是比如是数字，也可以用二进制来存

![image-20240215162039014](./img/image-20240215162039014.png)

打标记处代表有这个字符串

int son[N] [26]：一维是结点总数，而结点和结点之间的关系（谁是谁儿子）存在第二个维度，比如[0] [1]=3, [0]表示根节点，[1]表示它有一个儿子‘b’,这个儿子的下标是3；接着如果有一个[3] [2]=8 ; 说明根节点的儿子‘b’也有一个儿子‘c’，这个孙子的下标就是8；这样传递下去，就是一个字符串。随便给一个结点] [x] [y], 并不能看出它在第几层，只能知道，它的儿子是谁

son[x] [y] =z : x这个索引的点，有一个儿子y，延申到y之后存在z处

```cpp
int son[N][26], cnt[N], idx;
// 0号点既是根节点，又是空节点
// son[][]存储树中每个节点的子节点
// cnt[]存储以每个节点结尾的单词数量

// 插入一个字符串
void insert(char *str)
{
    int p = 0;
    for (int i = 0; str[i]; i ++ )
    {
        int u = str[i] - 'a';
        if (!son[p][u]) son[p][u] = ++ idx;
        p = son[p][u];
    }
    cnt[p] ++ ;
}

// 查询字符串出现的次数
int query(char *str)
{
    int p = 0;
    for (int i = 0; str[i]; i ++ )
    {
        int u = str[i] - 'a';
        if (!son[p][u]) return 0;
        p = son[p][u];
    }
    return cnt[p];
}
```



### 并查集

操作：

1. 将两个集合合并
2. 询问两个元素是否在一个集合当中



基本原理：

用树的形式维护集合，每一个集合的编号是根节点它根节点的编号，对于每个点都存储一下父节点是谁

对于每一个结点，想找它属于哪个集合，就找它的father，直到找到根为止

- 判断是不是树根：树根p[x] = x
- 如何求x的集合编号：while(p[x] != x) x = p[x];
- 如何合并两个集合：加条边即可，比如将左树插到右边树某个位置，比如原先p[x]=x , p[y] = y => p[x]=y



优化：路径压缩

before：

<img src="./img/image-20240215213108028.png" alt="image-20240215213108028" style="zoom:50%;" />

after：

<img src="./img/image-20240215213134604.png" alt="image-20240215213134604" style="zoom:50%;" />



```cpp
(1)朴素并查集：

    int p[N]; //存储每个点的祖宗节点

    // 返回x的祖宗节点
    int find(int x)
    {
        if (p[x] != x) p[x] = find(p[x]);
        return p[x];
    }

    // 初始化，假定节点编号是1~n
    for (int i = 1; i <= n; i ++ ) p[i] = i;

    // 合并a和b所在的两个集合：
    p[find(a)] = find(b);    
```



如果想知道每个集合有多少个元素：加一个size数组

```cpp
(2)维护size的并查集：

    int p[N], size[N];
    //p[]存储每个点的祖宗节点, size[]只有祖宗节点的有意义，表示祖宗节点所在集合中的点的数量

    // 返回x的祖宗节点
    int find(int x)
    {
        if (p[x] != x) p[x] = find(p[x]);
        return p[x];
    }

    // 初始化，假定节点编号是1~n
    for (int i = 1; i <= n; i ++ )
    {
        p[i] = i;
        size[i] = 1;
    }

    // 合并a和b所在的两个集合：
    size[find(b)] += size[find(a)];
    p[find(a)] = find(b);
```



### 堆

 操作：

1. 插入一个数

   heap[++size]=x; up(size)

2. 求集合当中的最小值

   heap[1];

3. 删除最小值

   将堆的最后一个元素覆盖掉堆顶元素，覆盖掉之后size--，再把对顶down()

   heap[1]=heap[size--]; down(1);

4. 删除任意一个元素

   heap[k]=heap[size]; size--;如果heap[k]变大了就up，变下了就down，也可以不管三七二十一，先down()再up()，但是只会执行一次

5. 修改任意一个元素

   heap[k]=x; down(k);up(k);

6. 数组建堆：

   最后一层的叶子结点不用管，错位相减

   ```
   // O(n)建堆
   for (int i = n / 2; i; i -- ) down(i);
   ```

   

堆是完全二叉树

小根堆：每个点的值都小于等于左右儿子的值。根结点是最小值

存储方式：

注意下标从1开始方便，毕竟 0 * 2=0，重叠了

![image-20240215225551106](./img/image-20240215225551106.png)

- down()：以小根堆为例，将它与左右儿子中更小的值交换，不断往下走到对的位置
- up：往上走



维护对应关系：

```cpp
// h[N]存储堆中的值, h[1]是堆顶，x的左儿子是2x, 右儿子是2x + 1
// ph[k]存储第k个插入的点在堆中的位置
// hp[k]存储堆中下标是k的点是第几个插入的
int h[N], ph[N], hp[N], size;

// 交换两个点，及其映射关系
void heap_swap(int a, int b)
{
    swap(ph[hp[a]],ph[hp[b]]);
    swap(hp[a], hp[b]);
    swap(h[a], h[b]);
}

void down(int u)
{
    int t = u;
    if (u * 2 <= size && h[u * 2] < h[t]) t = u * 2;
    if (u * 2 + 1 <= size && h[u * 2 + 1] < h[t]) t = u * 2 + 1;
    if (u != t)
    {
        heap_swap(u, t);
        down(t);
    }
}

void up(int u)
{
    while (u / 2 && h[u] < h[u / 2])
    {
        heap_swap(u, u / 2);
        u >>= 1;
    }
}

// O(n)建堆
for (int i = n / 2; i; i -- ) down(i);
```



## 第二章 数据结构（三）

### 哈希表

如果当成蹲坑：
开放寻址法：如果看到一个坑里有人就往前找没人的坑
拉链法：认准一个坑无论有没有人都在厕所门口排队



拉链法：

一个数组拉了很多链

![image-20240219201538880](./img/image-20240219201538880.png)

```cpp
#include <iostream>
#include <cstring>
using namespace std;
const int N = 100003;

//哈希表的槽
int h[N];
//竖着的链
int e[N],ne[N],idx;

void insert(int x){
    //+N让余数变成整数
    int k = (x % N + N) % N;
    //将数插到h[k]那一个链表
    //每一次把ne指向原来的头部，再更新头部
    e[idx]=x; ne[idx] = h[k];
    h[k]=idx++;
}

bool find(int x){
    int k = (x % N + N) % N;
    //在k对应的链表里找有没有对应的x
    for(int i = h[k]; i!=-1; i = ne[i])
        if(e[i] == x)
            return true;
    return false;
}

int main(){
    memset(h,-1,n*4);
    ...
}
```



开放寻址法

```cpp
int find(int x) {
    int t = (x % N + N) % N;
    while (h[t] != null && h[t] != x) {
        t++;
        if (t == N) {
            t = 0;
        }
    }
    return t;  //如果这个位置是空的, 则返回的是他应该存储的位置
}

//设值:
h[find(x)] = x;
```



#### 字符串哈希

字符串前缀哈希法

如何定义某个前缀的哈希值：将字符串看成P进制的数，每个字母表示p进制的某个数字

把任何一个字符串映射到从0到Q-1的数，，其中不能把字母映射成0：

假定不存在冲突：

经验：当p=131 or 13331 , Q = 2^64^，基本上不出现冲突（我们处理可以用unsigned long long存储，溢出的方式，不用取模了）

![image-20240220000137054](./img/image-20240220000137054.png)

预处理所有前缀的哈希：**可算出任意一个子串的哈希值**

- 算所有子串hash : h~i~ = h~i-1~*p + str[i]

- L-R的哈希值：h[R]-h[L-1]*p^R-L+1^（ 想想123和12345，那么应该12345-123 *100）

![image-20240220001517788](./img/image-20240220001517788.png)

### stl

```cpp
vector, 变长数组，倍增的思想
    size()  返回元素个数
    empty()  返回是否为空
    clear()  清空
    front()/back()
    push_back()/pop_back()
    begin()/end()
    []
    支持比较运算，按字典序

pair<int, int>
    first, 第一个元素
    second, 第二个元素
    支持比较运算，以first为第一关键字，以second为第二关键字（字典序）

string，字符串
    size()/length()  返回字符串长度
    empty()
    clear()
    substr(起始下标，(子串长度))  返回子串
    c_str()  返回字符串所在字符数组的起始地址

queue, 队列
    size()
    empty()
    push()  向队尾插入一个元素
    front()  返回队头元素
    back()  返回队尾元素
    pop()  弹出队头元素

priority_queue, 优先队列，默认是大根堆
    size()
    empty()
    push()  插入一个元素
    top()  返回堆顶元素
    pop()  弹出堆顶元素
    定义成小根堆的方式：priority_queue<int, vector<int>, greater<int>> q;

stack, 栈
    size()
    empty()
    push()  向栈顶插入一个元素
    top()  返回栈顶元素
    pop()  弹出栈顶元素

deque, 双端队列
    size()
    empty()
    clear()
    front()/back()
    push_back()/pop_back()
    push_front()/pop_front()
    begin()/end()
    []

set, map, multiset, multimap, 基于平衡二叉树（红黑树），动态维护有序序列
    size()
    empty()
    clear()
    begin()/end()
    ++, -- 返回前驱和后继，时间复杂度 O(logn)

    set/multiset
        insert()  插入一个数
        find()  查找一个数
        count()  返回某一个数的个数
        erase()
            (1) 输入是一个数x，删除所有x   O(k + logn)
            (2) 输入一个迭代器，删除这个迭代器
        lower_bound()/upper_bound()
            lower_bound(x)  返回大于等于x的最小的数的迭代器
            upper_bound(x)  返回大于x的最小的数的迭代器
    map/multimap
        insert()  插入的数是一个pair
        erase()  输入的参数是pair或者迭代器
        find()
        []  注意multimap不支持此操作。 时间复杂度是 O(logn)
        lower_bound()/upper_bound()

unordered_set, unordered_map, unordered_multiset, unordered_multimap, 哈希表
    和上面类似，增删改查的时间复杂度是 O(1)
    不支持 lower_bound()/upper_bound()， 迭代器的++，--

bitset, 圧位
    bitset<10000> s;
    ~, &, |, ^
    >>, <<
    ==, !=
    []

    count()  返回有多少个1

    any()  判断是否至少有一个1
    none()  判断是否全为0

    set()  把所有位置成1
    set(k, v)  将第k位变成v
    reset()  把所有位变成0
    flip()  等价于~
    flip(k) 把第k位取反
```



## 第三章 搜索与图论（一）

### DFS , BFS

- DFS：深度优先遍历，从数据结构看是栈，使用的空间更少，不一定是最短路

  DFS求全排列：相当于之前的回溯法：

  ```cpp
  void backtracking(...){
      if(终止条件){
          收集结果；        //通常在叶子结点上
          return;
      }
      for(遍历集合中元素，遍历当前层子结点){
          处理结点;
          递归;
          回溯，去掉处理结点的结果；
      }
  }
  ```

  

- BFS：宽度优先遍历，从数据结构看是队列，使用的空间大一些，（每条路权重相同时）“最短路”

  哪个点被哪条路先走到，这条路一定是最短路之一（严格从小到大走的）
  
  ```cpp
  queue <- 初始路径
  while(queue不变){
      //找最短路的话，如果找到终点了就可以return了
      
  	t <- 队头
  	扩展t
  }
  ```
  



### 树和图的存储 与 深广度遍历

#### 树和图的存储

树是特殊的图，无环连通图

图：无向图是特殊的有向图

有向图：

- 邻接矩阵：二维数组，不能存储重边，g[a] [b] : a -> b

- 邻接表：每一个结点上开一个单链表，一般头插法

  ![image-20240221234919305](./img/image-20240221234919305.png)

  ```cpp
  // 对于每个点k，开一个单链表，存储k所有可以走到的点。h[k]存储这个单链表的头结点
  int h[N], e[N], ne[N], idx;
  
  // 添加一条边a->b
  void add(int a, int b)
  {
      e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
  }
  
  // 初始化
  idx = 0;
  memset(h, -1, sizeof h);
  ```

  

#### 树和图的遍历

深度优先遍历：

```cpp
int dfs(int u)
{
    st[u] = true; // st[u] 表示点u已经被遍历过

    for (int i = h[u]; i != -1; i = ne[i])
    {
        //e[i]就是当前u结点能指向的结点
        int j = e[i];
        if (!st[j]) dfs(j);
    }
}
```

宽度优先遍历：

```cpp
queue<int> q;
st[1] = true; // 表示1号点已经被遍历过
q.push(1);

while (q.size())
{
    int t = q.front();
    q.pop();

    for (int i = h[t]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (!st[j])
        {
            st[j] = true; // 表示点j已经被遍历过
            q.push(j);
        }
    }
}
```



### 拓扑排序

记录入度d[N],值为0时即可进入拓扑排序队列

```cpp
#include <iostream>
#include <cstring>

using namespace std;
const int N = 1000010;

int n;
int h[N],e[N],ne[N],idx;
int hh = 0, tt = -1;
int q[N];
int d[N];     //记录每个点的入度

void add(int a, int b){
    e[idx] = b; ne[idx] = h[a]; h[a] = idx++;
    //增加一个入度
    d[b]++;
};

int main(){
    int m;
    cin >> n >> m;
    memset(h,-1,sizeof h);
    while (m--){
        int a,b;
        cin >> a >> b;
        add(a,b);
    }

    //先加入所有入度为0的点
    for (int i = 1; i <= n; i ++ )
        if (!d[i])
            q[ ++ tt] = i;

    while (hh <= tt){
        int head = q[hh ++ ];
        //当前点由于已经被摘除，它指向的所有点的入度都减1
        for (int i = h[head]; i != -1; i = ne[i]){
            int j = e[i];
            if (-- d[j] == 0)
                q[ ++ tt] = j;
        }
    }

    //!! 如果所有点都入队了，说明存在拓扑序列；否则不存在拓扑序列
    if(tt == n - 1){
        for(int i = 0; i <= n - 1; i++)
            cout << q[i] << " ";
    }else
        cout << -1 << endl;
}
```



## 第三章 搜索与图论（二）

### 最短路

一般考察如何建图成最短路问题

- 单源最短路：一个点到其他点的最短路径，起点确定

  - 所有边都是正权值

    - 朴素版迪杰斯特拉 n^2^ (n指点数，m指边数) ， **适用于稠密图(边多)，用邻接矩阵**
    - 堆优化迪杰斯特拉 mlogn ， 适用于稀疏图，**适用于稀疏图，用邻接表**

  - 存在负权边

    - Bellman-Ford O(nm)
    - SPFA 一般是O(m)，极端还是可能O(nm)

    但是如果最短路经过的边数 <= k：只能有Bellman-Ford

- 多源最短路：源是起点，汇是终点，起点和终点都不确定

  Floyd算法， O(n^3^)

![image-20240226174059814](./img/image-20240226174059814.png)

#### 迪杰斯特拉

##### 朴素版迪杰斯特拉

1. 初始化距离，从1点出发distance[1]=0，distance[其他点] = 正无穷

2. 集合S：当前已经确定最短距离的点

3. for循环n次：

   找到不在s中的距离最近的点t，

   把t加到s里面去，

   用t更新其他所有点的距离：新得到了从t出去的所有的边距离，更新得到最小值

   ```cpp
   #include <iostream>
   #include <cstring>
   
   using namespace std;
   
   /* 本题可以判断是稠密图，可以用邻接矩阵来写 , !! 不是所有都用邻接表才方便的  */
   
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
   
           //2. 在还未确定最短路的点中，寻找这个点出发距离最小的点
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
   ```

稀疏图的话这样做会爆掉，把这里N = 1000010就懂了



##### 堆优化版迪杰斯特拉

迪杰斯特拉在找最小的距离的数这一步是最慢的（第二步），所以用堆优化（使用优先队列模拟堆）

```cpp
typedef pair<int, int> PII;

int n;      // 点的数量
int h[N], w[N], e[N], ne[N], idx;       // 邻接表存储所有边
int dist[N];        // 存储所有点到1号点的距离
bool st[N];     // 存储每个点的最短距离是否已确定

// 求1号点到n号点的最短距离，如果不存在，则返回-1
int dijkstra()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.push({0, 1});      // first存储距离，second存储节点编号

    while (heap.size())
    {
        auto t = heap.top();
        heap.pop();

        int ver = t.second, distance = t.first;

        if (st[ver]) continue;
        st[ver] = true;

        for (int i = h[ver]; i != -1; i = ne[i])
        {
            int j = e[i];
            if (dist[j] > distance + w[i])
            {
                dist[j] = distance + w[i];
                heap.push({dist[j], j});
            }
        }
    }

    if (dist[n] == 0x3f3f3f3f) return -1;
    return dist[n];
}
```





### Bellman-Ford

存图可以用任意方式存

有负权回路的话，最短路径不一定存在：

![image-20240226202322319](./img/image-20240226202322319.png)

1到5不存在最短路

**也可以用来找负环**

```cpp
int n, m;       // n表示点数，m表示边数
int dist[N];        // dist[x]存储1到x的最短路距离

struct Edge     // 边，a表示出点，b表示入点，w表示边的权重
{
    int a, b, w;
}edges[M];

// 求1到n的最短路距离，如果无法从1走到n，则返回-1。
int bellman_ford()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;

    // 如果第n次迭代仍然会松弛三角不等式(**即最短路径大于n条边**)，就说明存在一条长度是n+1的最短路径，由抽屉原理，路径中至少存在两个相同的点，说明图中存在负权回路。
    //           b
    //      a   
    //
    // 点1                  相当于意思就是最终如果都能找到最短路径，则一定构成三角形
    //即最终dist[b] <= dist[a] + w
    for (int i = 0; i < n; i ++ ) {
        for (int j = 0; j < m; j ++ ) {
            int a = edges[j].a, b = edges[j].b, w = edges[j].w;
            if (dist[b] > dist[a] + w)
                dist[b] = dist[a] + w;
        }
    }

    if (dist[n] > 0x3f3f3f3f / 2) return -1;
    return dist[n];
}
```



用备份：

![image-20240226204258342](./img/image-20240226204258342.png)

如果不用备份，1和3的距离会在第一次就被更新为2，是两条边，应该在第二次才被更新出来



### SPFA

在Bellman-Ford中dist[b] = dist[a] + w，一定是dist[a]变小，dist[b]才会变小

用宽搜优化，队列里存的是所有变小的结点。

1. while 队列不空，取出头元素t
2. 更新t的所有出边，如果更新成功，就把更新成功的放入队列

队列里面存的是等待更新别的点的点

```cpp
int n;      // 总点数
int h[N], w[N], e[N], ne[N], idx;       // 邻接表存储所有边
int dist[N];        // 存储每个点到1号点的最短距离
bool st[N];     // 存储每个点是否在队列中

// 求1号点到n号点的最短路距离，如果从1号点无法走到n号点则返回-1
int spfa()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;

    queue<int> q;
    q.push(1);
    st[1] = true;

    while (q.size())
    {
        auto t = q.front();
        q.pop();

        st[t] = false;

        for (int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            if (dist[j] > dist[t] + w[i])
            {
                dist[j] = dist[t] + w[i];
                if (!st[j])     // 如果队列中已存在j，则不需要将j重复插入
                {
                    q.push(j);
                    st[j] = true;
                }
            }
        }
    }

    if (dist[n] == 0x3f3f3f3f) return -1;
    return dist[n];
}
```

为什么SPFA算法可以解决带负权边的，而迪杰斯特拉算法不行，他们长得那么像？

Dijkstra算法是一种贪婪算法，当图中存在负权边时，Dijkstra算法的贪婪策略会导致无法正确找到最短路径，可能会陷入无限循环。SPFA算法通过使用队列来选择待更新的顶点，以避免Dijkstra算法中的贪婪选择问题。它通过不断更新顶点的最短路径估计值来逐步收敛到最短路径。

（Dijkstra算法中的st数组保存的是当前确定了到源点距离最小的点，且一旦确定了最小那么就不可逆了(不可标记为true后改变为false)；SPFA算法中的st数组仅仅只是表示的当前发生过更新的点，且spfa中的st数组可逆(可以在标记为true之后又标记为false)。顺带一提的是BFS中的st数组记录的是当前已经被遍历过的点）



#### 找负环

int dist[N], cnt[N];        // dist[x]存储1号点到x的最短距离，cnt[x]存储1到x的最短路中经过的点数

每次更新：

dist[x] = dist[t] + w[i];

cnt[x] = cnt[t] + 1;

如果cnt[x] >= n：如果某条最短路径上有n个点（除了自己），那么加上自己之后一共有n+1个点，由抽屉原理一定有两个点相同，所以存在环。因为只要有负环，求最小值的时候就会一直走那个负环，走过的点数迟早会大于n



### Floyd

多源汇最短路：

```
初始化：
    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j <= n; j ++ )
            if (i == j) d[i][j] = 0;
            else d[i][j] = INF;

// 算法结束后，d[a][b]表示a到b的最短距离
void floyd()
{
    for (int k = 1; k <= n; k ++ )
        for (int i = 1; i <= n; i ++ )
            for (int j = 1; j <= n; j ++ )
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}
```

原理：动态规划：==感觉没太理解==

- d[k,i,j]：从i这个点出发，只经过1-k中间点到达j的最短距离



## 第三章 搜索与图论（三）



![image-20240321234330338](./img/image-20240321234330338.png)



### 最小生成树

无向图

#### Prim

与迪杰斯特拉**很相似**，复杂度与迪杰斯特拉也相同

- 朴素版：稠密图
- 堆优化版：稀疏图

**!!! 与迪杰斯特拉不同的点，更新其他点到最小生成树集合的距离，而迪杰斯特拉是更新到起点的距离**

```cpp
int n;      // n表示点数
int g[N][N];        // 邻接矩阵，存储所有边
int dist[N];        // 存储其他点到当前最小生成树的距离
bool st[N];     // 存储每个点是否已经在生成树中


// 如果图不连通，则返回INF(值是0x3f3f3f3f), 否则返回最小生成树的树边权重之和
int prim()
{
    //1. 初始化距离为正无穷
    memset(dist, 0x3f, sizeof dist);

    int res = 0;
    for (int i = 0; i < n; i ++ )
    {
        //这样和后面t = -1一起，这样至少保证每次能选到一个点
        int t = -1;
        //2.找到集合外距离最近的点
        for (int j = 1; j <= n; j ++ )
            if (!st[j] && (t == -1 || dist[t] > dist[j]))
                t = j;

        //第一次肯定是INF
        if (i && dist[t] == INF) return INF;

        if (i) res += dist[t];
        st[t] = true;

        //3. 用t来更新其他点到集合的距离
        //!!! 与迪杰斯特拉不同的点，更新其他点到最小生成树集合的距离，而迪杰斯特拉是更新到起点的距离
        for (int j = 1; j <= n; j ++ ) dist[j] = min(dist[j], g[t][j]);
    }

    return res;
}
```





#### Kruskal

稀疏图用



1. 对所有边进行排序（注意存储边的数据结构不要用之前的结构，因为是对边遍历，之前那种不方便）
2. 从权值最小的边开始看，如果边的两侧已被加入一个并查集 即已连通，就跳过该边
3. cnt代表被加入到生成树中的点数，如果最后比n-1小，说明仍不是所有点都在一个并查集中



```cpp
int n, m;       // n是点数，m是边数
int p[N];       // 并查集的父节点数组

struct Edge     // 存储边
{
    int a, b, w;

    bool operator< (const Edge &W)const
    {
        return w < W.w;
    }
}edges[M];

int find(int x)     // 并查集核心操作
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

int kruskal()
{
    sort(edges, edges + m);

    for (int i = 1; i <= n; i ++ ) p[i] = i;    // 初始化并查集

    int res = 0, cnt = 0;
    for (int i = 0; i < m; i ++ )
    {
        int a = edges[i].a, b = edges[i].b, w = edges[i].w;

        a = find(a), b = find(b);
        if (a != b)     // 如果两个连通块不连通，则将这两个连通块合并
        {
            p[a] = b;
            res += w;
            cnt ++ ;
        }
    }

    if (cnt < n - 1) return INF;
    return res;
}
```



### 二分图

![image-20240323122219104](./img/image-20240323122219104.png)

#### 染色法

判断一个图是不是二分图，给定0代表没染色，1代表白色，2代表黑色

**一个图是二分图当且仅当图中没有奇数环**

一个点的颜色如果确定了，那与它连通的所有点的颜色也都确定了

1. 遍历每一个点
2. 对于每一个点，对它dfs，把它连通的点的颜色都确定下来。如果出现了染色矛盾，就说明不是二分图



```cpp
#include <iostream>
#include <cstring>

using namespace std;
const int N = 100010;

int n;
// 注意边是2*N
int e[2*N],ne[2*N],h[N],idx;
int color[N];

// 添加一条边a->b
void add(int a, int b){
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

bool dna_dfs(int i, int c){
    color[i] = c;
    for(int j = h[i]; j != -1; j = ne[j]){
        int k = e[j];
        if(!color[k]){
            if(!dna_dfs(k,3-c))
                return false;
        } else if(color[k] == color[i])
            return false;
    }
    return true;
}

int main(){
    int m;
    cin >> n >> m;
    memset(h,-1,sizeof h);
    while (m--){
        int a,b;
        cin >> a >> b;
        add(a,b);
        add(b,a);
    }

    bool res = true;
    //注意这里的下标是从1开始!! 因为n >= 1 !
    for(int i = 1; i <= n; i++){
        if(!color[i]){
            if(!(res = dna_dfs(i, 1)))
                break;
        }
    }
    if(res)
        puts("Yes");
    else
        puts("No");
}
```



#### 匈牙利算法

二分图的匹配：给定一个二分图S，在S的一个子图M中，M的边集{E}中的任意两条边都不依附于同一个顶点，则称M是一个匹配

- **极大匹配**
  极大匹配是指在当前已完成的匹配下,无法再通过增加未完成匹配的边的方式来增加匹配的边数。（也就是说，再加入任意一条不在匹配集合中的边，该边肯定有一个顶点已经在集合中的边中了）
- **最大匹配**
  所有极大匹配当中边数最大的一个匹配

即一定是一对一

思路详见https://blog.csdn.net/Yaoyao2024/article/details/129895964，即如果A和2配对，到C了，只有2一个选择，会去查看A有没有其他备胎，如果有其他备胎，就让A和备胎处，C抢走2

```cpp
int n1, n2;     // n1表示第一个集合中的点数，n2表示第二个集合中的点数
int h[N], e[M], ne[M], idx;     // 邻接表存储所有边，匈牙利算法中只会用到从第一个集合指向第二个集合的边，所以这里只用存一个方向的边
int match[N];       // 存储第二个集合中的每个点当前匹配的第一个集合中的点是哪个
bool st[N];     // 表示第二个集合中的每个点是否已经被遍历过

bool find(int x)
{
    for (int i = h[x]; i != -1; i = ne[i])
    {
        int j = e[i];
        if (!st[j])
        {
            st[j] = true;
            if (match[j] == 0 || find(match[j]))
            {
                match[j] = x;
                return true;
            }
        }
    }

    return false;
}

// 求最大匹配数，依次枚举第一个集合中的每个点能否匹配第二个集合中的点
int res = 0;
for (int i = 1; i <= n1; i ++ )
{
    memset(st, false, sizeof st);
    if (find(i)) res ++ ;
}
```



## 第四章 数学知识（一）

### 质数

#### 试除法判断质数

**注意不能 i*i <= x，数字大的时候会溢出**

```cpp
bool is_prime(int x)
{
    if (x < 2) return false;
    // !! 注意不能 i*i <= x，数字大的时候会溢出！！
    for (int i = 2; i <= x / i; i ++ )
        if (x % i == 0)
            return false;
    return true;
}
```



#### 试除法分解质因数

指数与底数：对于正整数 12 的质因数分解，可以将其分解为 2² × 3¹，其中 2 和 3 分别是底数，而 2 和 1 则是对应的指数

n中最多只包含一个大于根号n的质因子

```cpp
void divide(int x)
{
    // n中最多只包含一个大于根号n的质因子
    for (int i = 2; i <= x / i; i ++ )
        if (x % i == 0)
        {
            int s = 0;
            while (x % i == 0) x /= i, s ++ ;
            cout << i << ' ' << s << endl;
        }
    if (x > 1) cout << x << ' ' << 1 << endl;
    cout << endl;
}
```



#### 筛质数

找2~n范围内所有质数

##### 朴素筛法求素数

筛去倍数，比如搜到2了，就删去4，6，8，...搜到3了，就删去6, 9 , 12....

```cpp
int primes[N], cnt;     // primes[]存储所有素数
bool st[N];         // st[x]存储x是否被筛掉

void get_primes(int n)
{
    for (int i = 2; i <= n; i ++ )
    {
        //不用每一个数都算倍数删，只删去质数的倍数就可以了
        if (st[i]) continue;
        
        //在这个数之前删倍数都没筛到它，说明它一定是质数
        primes[cnt ++ ] = i;
        //筛去所有倍数
        for (int j = i + i; j <= n; j += i)
            st[j] = true;
    }
}
```



##### 线性筛法求素数

**n只会被它的最小质因子筛掉！**，比如6只会被2筛掉，不会被3筛掉

原理：

主要看第二层for循环，primes数组里存了2-i中所有质数，

以i = 30为例，primes数组里面存了2 , 3, 5 , 7, 11 ,13, 17, 19 , 23 , 29

35的最小质因子是5，在找到5（i % 5 == 0 break掉之前），还有质数2，3

primes[j]一定是primes[j]*i的最小质因子：2(primes[j]) * 35(i) = 70 2是70的最小质因子

因为35的最小质因子为5，还没在第二层遍历到，所以乘起来之后的最小质因子一定是primes[j] 2。让70被它的最小质因子筛掉



这样每个数都被最小质因子筛掉，每个数只被筛掉一次，所以是线性的

```cpp
int primes[N], cnt;     // primes[]存储所有素数
bool st[N];         // st[x]存储x是否被筛掉

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
```



### 约数

约数是包含1和自身的

#### 试除法求约数

```cpp
vector<int> get_divisors(int x)
{
    vector<int> res;
    for (int i = 1; i <= x / i; i ++ )
        if (x % i == 0)
        {
            res.push_back(i);
            //如果是平方，不要重复添加，其他情况则补上大的那半边的约数
            if (i != x / i) res.push_back(x / i);
        }
    sort(res.begin(), res.end());
    return res;
}
```



#### 约数个数和约数之和



```
如果 N = p1^c1 * p2^c2 * ... *pk^ck
约数个数： (c1 + 1) * (c2 + 1) * ... * (ck + 1)
约数之和： (p1^0 + p1^1 + ... + p1^c1) * ... * (pk^0 + pk^1 + ... + pk^ck)
```

int范围内约数个数最大的数大概有1500个约数

**用一个hash存<p1,c1>的对**



计算约数之和时可用秦九韶算法：

即：这里第一项a0一定恒为1

![image-20240325142325901](./img/image-20240325142325901.png)

```cpp
for(int i = 1 ; i <= ele.second; i++){
            //秦九韶算法
            tmp = (tmp * ele.first + 1) % mod;
        }
```



### 欧几里得（辗转相除法）求最大公约数

时间复杂度为logn

d | a && d | b --> d | a+b 和 d | ax+by，比如2 | 4 && 2 | 6 ---> 2 | 4 * 1+6 * 7

```cpp
// a > b
int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}
```

a与b的最大公约数 = b与a mod b的最大公约数 （a > b）

原理：

a mod b = a - c*b

先证明左边任何一个公约数都是右边的公约数：d | a && d | b --> d | 1 * a+b * (-c)

再证明左边任何一个公约数都是右边的公约数：d | b && d | (a-c*b) --> d | c * b+ 1 * (a-c*b)

所以两者等价



### 欧拉函数

1∼N 中与 N 互质的数的个数被称为欧拉函数，记为 ϕ(N)。
若在算数基本定理中，$N=p_{1}^{a_{1}} p_{2}^{a_{2}} \ldots p_{m}^{a_{m}}$，则：
$$
\phi(N)=N \times \frac{p_{1}-1}{p_{1}} \times \frac{p_{2}-1}{p_{2}} \times \ldots \times \frac{p_{m}-1}{p_{m}}
$$
原理：假设n只存在质因子p,q, 则与n互质的数的集合需要除去p,2p,3p,⋯,⌊Np⌋以及q,2q,⋯,⌊Nq⌋。根据容斥原理，需要补回pq的倍数pq,2pq,⋯,⌊Npq⌋。因此个数，ϕ(n)=n−n/p−n/q+n/pq=n(1−1p)(1−1q)



#### 线性筛欧拉

与线性求素数一样：primes[j]一定是primes[j]*i的最小质因子

```cpp
const int N = 1000010;
bool st[N];
int primes[N];
int euler[N];
int cnt;

int main(){
    int n;
    cin >> n;

    //记得1也有欧拉数
    euler[1] = 1;
    for(int i = 2; i <= n; i++){
        if(!st[i]){
            //是质数，质数的欧拉数是它自己/自己 * (自己-1)
            primes[cnt ++ ] = i;
            euler[i] = i - 1;
        }

        for(int j = 0; primes[j] <= n / i; j++){
            int t = primes[j] * i;
            st[t] = true;
            if(i % primes[j] == 0){
                euler[t] = euler[i] * primes[j];
                break;
            }
            euler[t] = euler[i] * (primes[j] - 1);
        }
    }
}
```

- 质数的欧拉数是它自己/自己 * (自己-1)，也就是自己-1
- ![image-20240326203337981](./img/image-20240326203337981.png)

欧拉定理：如果a与n互质，a^$\phi(n)$^ mod n = 1

费马小定理：如果a和p互质，且p是质数，则a^p-1^ mod p = 1



### 快速幂

![image-20240326224220713](./img/image-20240326224220713.png)

左边是预处理，将k写成2进制数的和

左边的预处理，每一个数都是上个数的平方mod p :

![image-20240326224353456](./img/image-20240326224353456.png)

```cpp
求 m^k mod p，时间复杂度 O(logk)。

int qmi(int m, int k, int p)
{
    int res = 1 % p, t = m;
    while (k)
    {
        if (k&1) res = res * t % p;
        t = t * t % p;
        k >>= 1;
    }
    return res;
}
```

比如求4^5^ mod 10:

预处理出4^2的0次方^ mod 10 = 4, 4^2的1次方^ mod 10 = 6（4 * 4 mod 10）, 4^2的2次方^ mod 10 = 6（6 * 6 mod 10）

5 = (101)~2~  = 2^0^ + 2^2^  , 4*6 mod 10 = 4（注意是乘！） 



#### 逆元

![image-20240329231644531](./img/image-20240329231644531.png)

b的逆元：b^-1^

<img src="./img/image-20240329232110087.png" alt="image-20240329232110087" style="zoom:50%;" />

因为b与m互质，a与a* b * b^-1^同余，余数是a和b和b逆元模m结果相乘，说明b * b^-1^ mod m = 1

然后用费马定理（费马小定理：如果a和p互质，且p是质数，则a^p-1^ mod p = 1），后略 



### 扩展欧几里得算法

裴蜀定理：有一对正整数a,b，那么一定存在非0整数x,y，使得ax+by = (a,b)

![image-20240329233257676](./img/image-20240329233257676.png)

```cpp
// 求x, y，使得ax + by = gcd(a, b)
//返回最小公约数
//a > b
int exgcd(int a, int b, int &x, int &y)
{
    if (!b)      //a % b = 0
    {
        x = 1; y = 0;
        return a;
    }
    //y' x'代表上一层的结果
    //d : by' + (a mod b)*x' = (b,a % b) = (a,b)
    //a % b = a - [a/b]*b ，其中[]指下取整 =>
    //d : by' + (a - [a/b]*b)*x' = (a,b) =>
    //ax' + b(y' - [a/b]*x') = d , 即x不用变，y要减去后面那截
    //x=x' , y = y' - [a/b]*x'
    
    //注意这里是传入y,x !!
    int d = exgcd(b, a % b, y, x);
    y -= (a/b) * x;
    return d;
}
```

得到一个解ax + by = d之后，由于(a,b)=d，所以a(x - b/d) + b(y + a/d) = d，即推得所有解



#### 线性同余方程

ax与b对m同余，说明ax=my+b

所以ax-my=b，令y'=y，即ax+my'=b

**这个方程有解的==充分必要==条件是(a,m) | b**，因为：

方程有解=>(a,m) | b： a是(a,m)的倍数，m是(a,m)的倍数，ax-my也一定是(a,m)的倍数

(a,m) | b=>方程有解：扩展欧几里得ax+my = gcd(a,b)有解，扩大一下gcd倍数一定也有解（线性的，系数乘对应倍数就行）



### 中国剩余定理

https://blog.csdn.net/qq_43589852/article/details/128469183

给定一堆==**两两互质**==的数m1...mk

Mi等于除了mi以外，其他所有m的乘积，所以Mi（相当于是满足整除其他m）与mi互质，于是就能求出Mi^-1^，即Mi的模mi的乘法逆元

满足Mi | a时，$\frac{a}{M_{i}} \equiv a \times x(\bmod m_{i})$

![image-20240406235557058](D:\ClionLinux\acwing\image-20240406235557058.png)



对于ax同余1(mod m)的理解可以看看链接，带入上面latex公式的a为a*Mi（a其实就是图里的a1,a2...）

${a} \equiv a*M_{i} \times M_{i}^{-1}(\bmod m_{i})$，Mi * Mi^-1^ = 1(mod m)，推导见逆元处

看每一项是否成立，比如看a1 mod m1，对于右式的第一部分mod数为a1，其他项M都整除m1，mod结果为0，加起来是1

其中由于mi可能不是正数，求Mi^-1^时需用扩展欧几里得，ax+my = 1，由于m是a的余数，gcd(a,m)=1



具体题目：

没有两两互质的前提！先考虑两个方程的情况：

![image-20240410235930122](./img/image-20240410235930122.png)

于是：

![image-20240411000524869](./img/image-20240411000524869.png)

（右->左），[a1,a2]是最小公倍数，最右下方那个是扩展欧几里得的通解。

当最后得到左边x=x0+ka之后，就与右边最开始时的x=k1a1+m1结构相似，可以继续往下迭代发展：新a1就是上一次的[a1,a2]最小公倍数，新m1就是上一次的x0,即a1k1+m1，然后就可以继续k1a1+m1=k2a2+m2了



每次将一个新的方程合并到现有方程当中



# 小技巧

可以专门拿一个数组记录各个元素出现次数，便于判断处理是否重复

 
