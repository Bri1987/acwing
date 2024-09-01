//#include <iostream>
//#include <cstring>
//#include <unordered_map>
//
//using namespace std;
//
//const int N = 10010;
//int h[N], e[N*2], ne[N*2], w[N*2], idx;
//
//struct pair_hash {
//    template <class T1, class T2>
//    std::size_t operator() (const std::pair<T1, T2>& pair) const {
//        auto hash1 = std::hash<T1>{}(pair.first);
//        auto hash2 = std::hash<T2>{}(pair.second);
//        return hash1 ^ (hash2 << 1); // Combine the two hashes
//    }
//};
//
//unordered_map<pair<int,int>,int,pair_hash> memo;
//
//void add(int a,int b, int c){
//    e[idx] = b;
//    w[idx] = c;
//    ne[idx] = h[a];
//    h[a] = idx++;
//}
//
//int dfs(int root, int p){
//    if(memo.find({root,p}) != memo.end())
//        return memo[{root,p}];
//
//    int res = 0;
//    for(int i = h[root]; i != -1; i = ne[i]){
//        int j = e[i];
//        if(j != p){
//            int path = w[i];
//            int dfsRes = dfs(j,root);
//            if(dfsRes > 0)
//                path += dfsRes;
//            path = max(0, path);
//            res = max(res, path);
//        }
//    }
//    memo[{root,p}] = res;
//    return res;
//}
//
//int main(){
//    int n;
//    cin >> n;
//    memset(h,-1,sizeof h);
//    for(int i = 0; i < n-1; i++){
//        int a,b,c;
//        cin >> a >> b >> c;
//        add(a,b,c);
//        add(b,a,c);
//    }
//
//    int res = 0;
//    for(int i = 1; i <= n; i++){
//        res = max(res, dfs(i,-1));
//    }
//    cout << res;
//    return 0;
//}

#include <iostream>
#include <cstring>
#include <unordered_map>

using namespace std;

const int N = 10010;
int h[N], e[N*2], ne[N*2], w[N*2], idx;

// f1 : 最长路, f2 : 次长路
int f1[N],f2[N];
int res = 0;

void add(int a,int b, int c){
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

void dfs(int root, int p){
    f1[root] = f2[root] = 0;
    for(int i = h[root]; i != -1; i = ne[i]){
        int j = e[i];
        if(j != p){
            dfs(j,root);
            if(f1[j] + w[i] >= f1[root]) {
                f2[root] = f1[root];
                f1[root] = f1[j] + w[i];
            } else if(f1[j] + w[i] > f2[root])
                f2[root] = f1[j] + w[i];
        }
    }
    res = max(res, f1[root] + f2[root]);
}

int main(){
    int n;
    cin >> n;
    memset(h,-1,sizeof h);
    for(int i = 0; i < n-1; i++){
        int a,b,c;
        cin >> a >> b >> c;
        add(a,b,c);
        add(b,a,c);
    }

//    for(int i = 1; i <= n; i++){
//        dfs(i,-1);
//    }
    // 可以任意选取一个点作为根节点
    dfs(1,-1);
    cout << res;
    return 0;
}