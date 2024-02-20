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

![image-20240208183214019](D:\ClionLinux\acwing\img\image-20240208183214019.png)

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



# 小技巧

可以专门拿一个数组记录各个元素出现次数，便于判断处理是否重复

 
