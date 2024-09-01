#include <iostream>

using namespace std;

const int N = 100010, M = 500010;
int h[N], e[M * 2], ne[2 *M], idx;
int w[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx++;
}

int main(){
    int n,m;
    cin >> n >> m;
    for(int i = 1 ; i <= n; i++)
        cin >> w[i];
    while(m--){
        int a,b,c;
        cin >> a >> b >> c;
        add(a,b);
        if(c == 2)
            add(b,a);
    }

    return 0;
}