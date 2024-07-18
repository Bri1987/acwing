#include <iostream>
#include <cstring>

using namespace std;
const int N = 10010, mod = 1e9+7;
int f[N];

//int cal(string s1, string s2){
//    //用s1串的前i个字符提取出s2串前j个字符的子序列
//    for(int i = 1; i <= s1.size(); i++){
//        if(s1[i-1] == s2[0])
//            f[i][1] = f[i-1][1] + 1;
//        else
//            f[i][1] = f[i-1][1];
//    }
//
//    for(int i = 2; i <= s1.size(); i++){
//        for(int j = 2; j <= s2.size(); j++){
//            if(s1[i-1] == s2[j-1])
//                f[i][j] = (f[i-1][j-1] + f[i-1][j]) % mod;
//            else
//                f[i][j] = f[i-1][j] % mod;
//        }
//    }
//    return f[s1.size()][s2.size()];
//}

int cal(string s1, string s2){
    //用s1串的前i个字符提取出s2串前j个字符的子序列

    //找到前0个字符串的子序列，只有一种办法就是什么都不选
    f[0] = 1;

    for(int i = 1; i <= s1.size(); i++){
        for(int j = s2.size(); j >= 1 ; j--){
            if(s1[i-1] == s2[j-1])
                f[j] = (f[j-1] + f[j]) % mod;
        }
    }
    return f[s2.size()];
}

int main(){
    int m;
    cin >> m;
    while(m--){
        memset(f, 0, sizeof f);
        string s1,s2;
        cin >> s1 >> s2;
        if(s1.size() < s2.size())
            cout << 0 << endl;
        else
            cout << cal(s1,s2) << endl;
    }
    return 0;
}