#include <iostream>

using namespace std;

const int N = 210*210;
int a[N];
int p[N];

int find(int x){
    if(p[x] != x)   p[x] = find(p[x]);
    return p[x];
}

int main(){
    int n,m;
    cin >> n >> m;
    int res = -1;
    for(int i = 1; i <= n*n; i++)
        p[i] = i;
    for(int i = 1; i <= m; i++){
        int a,b;
        char choice;
        cin >> a >> b >> choice;
        //起点是(a-1)*n+b;
        int st = (a-1)*n+b;
        int ed;
        //先找终点
        if(choice == 'D')
            ed = a*n+b;
        else
            ed = st+1;
        // 只差一条边连起来
        if(find(st) == find(ed)){
            res = i;
            break;
        } else{
            p[find(ed)] = find(st);
        }
    }

    if(res == -1)
        cout << "draw";
    else
        cout << res;
    return 0;
}