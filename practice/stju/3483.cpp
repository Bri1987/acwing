#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;
vector<pair<int,int>> vec2;   // 128, 7
unordered_map<int,string> memo;     

// ! 可以直接全打表，更快
// string s[30] = {
//    "2(0)",            //1
//    "2",               //2
//    "2(2)",            //4
//    "2(2+2(0))",       //8
//    "2(2(2))",         //16
//    "2(2(2)+2(0))",    //32
//    "2(2(2)+2)",       //64
//    "2(2(2)+2+2(0))",  //128
//    "2(2(2+2(0)))",           //256
//    "2(2(2+2(0))+2(0))",      //512
//    "2(2(2+2(0))+2)",         //1024
//    "2(2(2+2(0))+2+2(0))",    //2048
//    "2(2(2+2(0))+2(2))",      //4096
//    "2(2(2+2(0))+2(2)+2(0))", //8192
//    "2(2(2+2(0))+2(2)+2)"     //16384
//};

pair<int,int> get_mx_2(int r, int x){
    int l = 0;
    while(l < r){
        int mid = (l + r) >> 1;
        if(vec2[mid].first == x)
            return {vec2[mid].first, vec2[mid].second};
        if(vec2[mid].first > x)
            r = mid - 1;
        else if(mid == r || vec2[mid+1].first > x)
            return {vec2[mid].first, vec2[mid].second};
        else
            l = mid + 1;
    }
    return {vec2[l].first, vec2[l].second};
}

string get_res(int x){
    if(memo.find(x) != memo.end())
        return memo[x];
    
    bool is_final = true;
    string s;
    int r = vec2.size()-1;
    while(x) {
        auto [num, cnt] = get_mx_2(r, x);
        x -= num;
        if(cnt > 2) {
            is_final = false;
            s += "2(";
            s += get_res(cnt);
            s += ")";
        } else {
            if(cnt == 0)
                s += "2(0)";
            else if(cnt == 1)
                s += "2";
            else 
                s += "2(2)";
        }
        
        while(x > num) {
            s += "+(";
            x -= num;
            s += memo[num];
            s += ")";
        }
        r = cnt - 1;
        
        if(x)
            s += "+";
    }
    
    
    if(is_final) {
        memo[x] = s;
    }
        
    return s;
}

int main(){
    //预处理
    for(int i = 1, begin = 0; i <= 20000; i *= 2 , begin++){
        vec2.push_back({i, begin});
    }
    
    int x;
    while(cin >> x){
        cout << get_res(x) << endl;
    }
    return 0;
}