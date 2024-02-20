#include<iostream>
#include<cstdio>
#include<string>

using namespace std;
const int N = 1000010;
int n,m;
int P = 13331;
//使用p数组保存p的阶乘
unsigned long long prefix[N],p[N];

int main(){
    cin >> n >> m;
    string str;
    cin >> str;
    int l1,r1,l2,r2;

    p[0] = 1;
    //计算所有前缀子串的hash
    for(int i = 1; i <= n; i++){
        //prefix位记得乘P
        prefix[i] = prefix[i-1] * P + str[i-1];
        p[i] = p[i-1] * P;
    }

    while (m--){
        cin >> l1 >> r1 >> l2 >> r2;
        //算l1-r1的hash
        //由于prefix下标是从1开始，刚好与输入也从1开始对上了
        unsigned long long hash1 = prefix[r1]-prefix[l1-1]*p[r1-l1+1];
        //算l2-r2的hash
        unsigned long long hash2 = prefix[r2]-prefix[l2-1]*p[r2-l2+1];
        if(hash1 == hash2) puts("Yes");
        else puts("No");
    }
}