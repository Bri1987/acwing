#include <iostream>

using namespace std;

const int N = 60;
// 对于每个队列，只维护当前单调队列的最后一个数，递增的是up，每个元素代表一个递增队列的最后一个数，递减的是down
int a[N],up[N],down[N];
int su,sd;
int n;

// 其实就是对每个数有4种选择: 放入一个up队列，放入一个新开的up队列，放入一个down队列，放入一个新开的down队列，注意维护su,sd那些，注意在下一种选择后复原

// 注意up和down是保持顺序，可以维持着贪心的
// 比如up序列先放了4，那么3只能放入新队列，再遇到5的时候，会直接放入第一个4的序列，保持一个贪心，始终选择最大的
bool dfs(int depth, int cur){
    if(su + sd > depth)
        return false;
    if(cur > n)
        return true;

    // 1.  放入一个up队列  
    // flag判断能不能放到某个队列后面，不能的话就只有新开这一种选择
    bool flag = false;
    int i;
    for(i = 1; i <= su; i++){
        if(up[i] < a[cur]){
            flag = true;
            break;
        }
    }
    if(flag){
        int tmp = up[i];
        up[i] = a[cur];
        if(dfs(depth,cur+1))
            return true;
        up[i] = tmp;
    }
    //2. 开新的up
    up[++su] = a[cur];
    if(dfs(depth,cur+1))
        return true;
    --su;


    flag = false;
    // 3. 放入一个down队列
    for(i = 1; i <= sd; i++){
        if(down[i] > a[cur]){
            flag = true;
            break;
        }
    }
    if(flag){
        int tmp = down[i];
        down[i] = a[cur];
        if(dfs(depth,cur+1))
            return true;
        down[i] = tmp;
    }
    // 4. 开新的down
    down[++sd] = a[cur];
    if(dfs(depth,cur+1))
        return true;
    --sd;
    return false;
}

int main(){
    while(cin >> n && n){
        su = 0; sd = 0;
        for(int i = 1; i <= n; i++)
            cin >> a[i];

        // 从1开始，看1个序列能不能满足要求，知道x个序列能满足要求为止
        int depth = 1;
        while(!dfs(depth,1))
            depth++;
        cout << depth << endl;
    }
    return 0;
}