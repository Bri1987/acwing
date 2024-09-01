#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 12;

int n;
int a[N];
bool coprime[N][N];
vector<int> nums[N];

// x > y
int gcd(int x, int y){
    if(!y)
        return x;
    return gcd(y, x % y);
}

bool dfs(int idx,int len, int cnt) {
    if(idx == n + 1)
        return true;
    bool meet = false;
    for(int i = 1; i <= cnt; i++) {
        bool canPush = true;
        for(int j = 0; j < nums[i].size(); j++) {
            if(!coprime[nums[i][j]][idx]) {
                canPush = false;
                break;
            }
        }
        if(canPush) {
            nums[i].push_back(idx);
            if(dfs(idx+1, len, cnt))
                meet = true;
            nums[i].pop_back();
        }
    }

    bool newMeet = false;
    if(cnt < len) {
        nums[cnt + 1].push_back(idx);
        newMeet = dfs(idx+1, len, cnt + 1);
        nums[cnt + 1].pop_back();
    }
    if(newMeet || meet)
        return true;
    return false;
}

int main() {
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];

    sort(a+1, a+n+1);
    memset(coprime,-1,sizeof coprime);
    for(int i = 1; i <= n; i++)
        coprime[i][i] = false;
    for(int i = 1; i <= n; i++)
        for(int j = i + 1; j <= n; j++){
            if(gcd(a[j],a[i]) == 1) {
                coprime[i][j] = true;
                coprime[j][i] = true;
            } else {
                coprime[i][j] = false;
                coprime[j][i] = false;
            }
           // cout << a[i] << " " << a[j] << "," << coprime[i][j] << endl;
        }

    int depth = 1;
    while(!dfs(1,depth,0))
        depth++;
    cout << depth;
    return 0;
}