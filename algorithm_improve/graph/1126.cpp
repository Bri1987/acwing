#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

const int N = 2010, M = 100010;
int h[N],e[M*2],ne[M*2],idx;
double w[M*2];
bool st[N];
double d[N];

typedef pair<double,int> PII;

void add(int a,int b,double c){
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

int main(){
    int n,m;
    cin >> n >> m;
    // ! double的初始不能给-1
    memset(d,0,sizeof d);
    memset(h,-1,sizeof h);
    while(m--){
        int a,b ,c;
        cin >> a >> b >> c;
        double weight = (100-c) / 100.0;
        add(a,b,weight);
        add(b,a,weight);
    }

    int bg,ed;
    cin >> bg >> ed;
    priority_queue<PII,vector<PII>,less<>> q;
    q.push({1,bg});
    d[bg] = 1;
    double res = 1;
    while(q.size()){
        auto [weight, t] = q.top();
        q.pop();

        if(st[t])   continue;
        st[t] = true;

        if(t == ed){
            res = d[ed];
            break;
        }

        for(int i = h[t]; i != -1; i = ne[i]){
            int j = e[i];
            if(d[j] < weight*w[i]){
                d[j] = weight*w[i];
                q.push({d[j],j});
            }
        }
    }
    res = 100.00 / res;
    // 这样输出!
    printf("%.8f",res);
    return 0;
}