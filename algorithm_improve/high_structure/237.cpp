#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

const int N = 100010 * 2;
int p[N];

int find(int x){
    if(p[x] != x)   p[x] = find(p[x]);
    return p[x];
}

int main(){
    int m;
    cin >> m;
    while(m--){
        int n;
        cin >> n;
        vector<int> alls;
        vector<tuple<int,int,int>> vec;
        unordered_map<int,int> mm;
        // 10 ^9 需要做离散化
        for(int k = 0; k < n; k++){
            int i,j,e;
            cin >> i >> j >> e;
            alls.push_back(i);
            alls.push_back(j);
            vec.emplace_back(i,j,e);
        }
        sort(alls.begin(),alls.end());
        alls.erase(unique(alls.begin(),alls.end()),alls.end());
        for(int k = 0; k < alls.size(); k++){
            mm[alls[k]] = k+1;
            p[k+1] = k+1;
        }

        bool is_right = true;
        vector<pair<int,int>> tmp_save;
        // 不等的情况可能当前判断不出来，需要做后处理
        for(auto [a, b, e] : vec){
            int x = mm[a], y = mm[b];
            if(e == 1){
                if(find(x) != find(y)){
                    p[find(y)] = find(x);
                }
            } else {
                if(find(x) == find(y)){
                    is_right = false;
                    break;
                } else {
                    // 先存起来，最后检验
                    tmp_save.emplace_back(x,y);
                }
            }

        }
        for(auto & i : tmp_save){
            if(find(i.first) == find(i.second)){
                is_right = false;
                break;
            }
        }

        if(!is_right)   cout << "NO"<< endl;
        else    cout << "YES" << endl;
    }
    return 0;
}