#include <iostream>

using namespace std;

// NIM博弈先手必胜，当且仅当 A1 ^ A2 ^ … ^ An != 0
int main(){
    int n;
    cin >> n;
    int res;
    cin >> res;
    for(int i = 0; i<n-1; i++){
        int m;
        cin >> m;
        res ^= m;
    }
    if(res != 0)
        puts("Yes");
    else
        puts("No");
    return 0;
}