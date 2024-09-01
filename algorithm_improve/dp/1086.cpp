#include <iostream>
#include <unordered_map>

using namespace std;
typedef long long LL;

const int N = 20, MOD = 1e9+7;

// 自定义哈希函数
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2>& pair) const {
        auto hash1 = std::hash<T1>()(pair.first); // 哈希第一个元素
        auto hash2 = std::hash<T2>()(pair.second); // 哈希第二个元素
        return hash1 ^ (hash2 << 1); // 合并哈希值
    }
};

unordered_map<pair<int,string>,LL,pair_hash> m;

LL dfs(int i, int sum, int fullVal, bool isLimit, bool isNum, string cur, string s) {
    int len = s.length();
    if(i == len){
        if(!isNum)
            return 0;
        LL val = atoll(cur.c_str());
        if(sum != 0 && fullVal != 0){
            LL res =  ((val % MOD) * (val % MOD)) % MOD ;
            return res;
        }
        return 0;
    }

    if(!isLimit && m.find({i,cur}) != m.end())
        return m[{i,cur}];

    int up = isLimit ? s[i] - '0' : 9;
    LL res = 0;
    for(int d = 0; d <= up; d++){
        if(d != 7){
            bool beNum = isNum || d != 0;
            string nextString = beNum ? cur + to_string(d) : "";
            res = (res + dfs(i+1, (sum + d) % 7, (fullVal*10 + d) % 7, isLimit && d == up, beNum, nextString, s)) % MOD;
        }
    }
    if(!isLimit)
        m[{i,cur}] = res;
    return res;
}

int main() {
    int x,y;
    int T;
    cin >> T;
    while(T--){
        cin >> x >>  y;
        m.clear();
        LL res1 = dfs(0,0,0,true,false,"", to_string(y));
        m.clear();
        LL res2 = dfs(0,0,0,true,false,"", to_string(x-1));
        if(res2 > res1)
            res1 += MOD;
        cout << res1 - res2 << endl;
    }
    return 0;
}