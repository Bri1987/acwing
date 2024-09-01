#include <iostream>
#include <cstring>

using namespace std;

const int N = 110;
int a[N];
int save[N];

int n;
int len;

void dfs(int idx) {
    if(idx >= len)
        return ;
    for(int i = idx-1; i >= 1; i--) {
        for(int j = i; j < idx; j++) {
            if(a[i] + a[j] > a[idx-1] && a[i] + a[j] <= n) {
                if(a[i] + a[j] == n){
                    a[idx] = n;
                    len = min(len, idx);
                    for(int k = 1; k <= idx; k++)
                        save[k] = a[k];
                }
                a[idx] = a[i] + a[j];
                dfs(idx+1);
            }
        }
    }
}

int main() {
    while(cin >> n , n){
        len = n;
        memset(a,0,sizeof a);
        memset(save,0,sizeof save);
        a[1] = 1;save[1] = 1;
        a[2] = 2;save[2] = 2;
        if(len > 3)
            dfs(3);
        else {
            a[3] = 3;
            save[3] = 3;
        }
        // cout << len << "   " ;
        for(int i = 1; i <= len; i++)
            cout << save[i] << " ";
        cout << endl;
    }
    return 0;
}