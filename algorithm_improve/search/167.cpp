//#include <iostream>
//#include <algorithm>
//
//using namespace std;
//const int N = 70;
//
//int n;
//int a[N];
//
//int v[N];
//
//int sum = 0;
//
//bool cmp(int v1, int v2){
//    return v1 >= v2;
//}
//
//// 这样做有很多剪枝不好写
//bool dfs(int idx, int depth, int cnt) {
//    if(idx == n + 1 ){
//        return true;
//    }
//    for(int i = 1; i <= cnt; i++){
//        if(v[i] + a[idx] <= depth){
//            v[i] += a[idx];
//            if(dfs(idx+1, depth, cnt))
//                return true;
//            v[i] -= a[idx];
//            // 如果刚好填的最后一根失败, 则一定失败
//            if(v[i] + a[idx] == depth)
//                return false;
//        }
//    }
//
//    if(cnt < sum / depth) {
//        v[cnt + 1] = a[idx];
//        if(dfs(idx+1, depth, cnt + 1))
//            return true;
//        v[cnt + 1] = 0;
//    }
//    return false;
//}
//
//int main() {
//    while(cin >> n, n){
//        sum = 0;
//        for(int i = 1; i <= n; i++) {
//            cin >> a[i];
//            sum += a[i];
//        }
//        sort(a+1, a+n+1, cmp);
//        int depth = a[1];
//        while(sum % depth != 0)
//            depth++;
//        while(!dfs(1,depth,0)) {
//            depth++;
//            while(sum % depth != 0)
//                depth++;
//        }
//        cout << depth << endl;
//    }
//    return 0;
//}

#include<iostream>
#include<cstring>
#include<algorithm>

// 这个思路是长度固定下来之后，一个长度棍填完再填下一根
// 上面注释的是一根一根小木棍处理的，这个思路填的话st用到的小木棍可能不连续

using namespace std;

const int N=70;

int w[N],sum,length,n;
bool st[N];

// 第u组(已经完整完成了u-1根长木棍),正在填第u根, part为第u组的已有长度(这跟长木棍已经填的长度)
// start表示第u组的枚举位置;(保证使用的小木棍下标递增, 这是这组能使用的第一个小木棍的idx)
bool dfs(int u,int part,int start)
{
    // 如果总长度到达了,返回true
    if(u*length==sum) return true;
    // true要一直持续不断的返回,false同理
    // 说明这跟填完了，接下来填下一根
    if(part==length)
        return dfs(u+1,0,0);

    // 保持递增
    for(int i=start;i<=n;i++)
    {
        // 这跟小木棍用过了
        if(st[i]) continue;
        if(w[i]+part > length)
            continue;
        st[i]=true;//标记已经使用
        if(dfs(u,w[i]+part,i+1)) return true;//因为前i个棍子都在第u组枚举了,所以直接从第i+1根棍子开始枚举
        st[i]=false;//返回上层分支时要恢复现场(枚举该组不选择第i根根子的方案)

        // 走到这儿说明一定是失败了，不然在94行就return false了
        //如果填第一根(一根长木棍的第一个小木棍)失败了, 后面的就一定不可能在成功，因为这一根小木棍总会以一个成员的形式出现
        //如果填一个长木棍的最后一根小木棍失败了,就一定失败(它如果填后面的新木棍, 也必须要有等长的其他木棍补上,是一样失败的)
        if(!part || w[i]+part == length) return false;

        //如果i失败了,那么长度跟i一样的棍子也一定失败
        int j = i;
        while(j <= n && w[j] == w[i])
            j++;
        i = j - 1;
    }

    return false;//枚举完了还没有成功,就返回失败
}

int main()
{
    while(cin>>n,n)
    {
        //初始化
        memset(st,0,sizeof st);
        sum=0,length=1;

        for(int i=1;i<=n;i++)
        {
            scanf("%d",&w[i]);
            sum+=w[i];//总和
        }

        //倒着排序,以减少分支
        sort(w+1,w+n+1);
        reverse(w+1,w+n+1);

        while(1)//枚举length的长度
        {
            if(sum%length==0&&dfs(0,0,0))
            {
                printf("%d\n",length);
                break;
            }
            length++;
        }
    }
}