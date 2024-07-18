//#include <iostream>
//#include <vector>
//#include <algorithm>
//#include <unordered_map>
//
//using namespace std;
//const int N = 20010;
//unordered_map<int,int> m;
//
//int n,y;
//
//struct Range{
//    int a;
//    int b;
//    int w;
//
//    bool operator > (const Range& other) const {
//        return w > other.w;
//    }
//}range[N];
//
//int find(int x,int p[]){
//    if (p[x] != x) p[x] = find(p[x],p);
//    return p[x];
//}
//
//int main(){
//    int mm;
//    cin >> mm;
//    while(mm--){
//        cin >> n >> y;
//        m.clear();
//        for(int i = 0; i < n-1; i++){
//            int a,b,w;
//            cin >> a >> b >> w;
//            range[i] = {a,b,w};
//        }
//        sort(range, range + N, greater<>());
//        int p[N],s[N];
//        for(int i = 0; i < n; i++){
//            p[i] = i;
//            s[i] = 1;
//        }
//
//        int res = 0;
//        for(int i = 0; i < n-1; i++){
//            int a = range[i].a, b = range[i].b, w = range[i].w;
//            if(find(a,p) != find(b,p)){
//                s[find(a,p)] += s[find(b,p)];
//                p[find(b,p)] = find(a,p);
//                if(s[find(0,p)] > y){
//                    res = w + 1;
//                    break;
//                }
//            }
//        }
//        cout << res << endl;
//    }
//    return 0;
//}

#include <iostream>
#include <cstring>

using namespace std;
const int N = 40010;

int h[N],e[N],w[N],ne[N],idx;
int n,y;

void add(int a,int b,int c){
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

int ans;

void dfs(int a, int fa, int val){
    ans++;
    for(int i = h[a]; i != -1; i = ne[i]){
        if(ans > y) break;
        int j = e[i];
        //!注意这招处理不往回搜
        if(j == fa) continue;
        if(w[i] >= val) dfs(j, a, val);
    }
}

bool check(int x){
    dfs(0,-1,x);
    if(ans > y) return false;
    else return true;
}

int main(){
    int m;
    cin >> m;
    while(m--){
        cin >> n >> y;
        memset(h, -1, sizeof h);
        idx = 0;
        for(int i = 0; i < n-1; i++){
            int a,b,c;
            cin >> a >> b >> c;
            add(a,b,c);
            add(b,a,c);
        }
        //二分看最长的边应该在哪
        int l = 0, r = 1e8;
        while(l < r){
            ans = 0;
            int mid = (l + r) >> 1;
            if(check(mid))  r = mid;
            else l = mid + 1;
        }
        cout << l << endl;
    }

    return 0;
}