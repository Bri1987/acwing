#include <iostream>

using namespace std;

const int N  = 100010;
int q[N];
//注意hh设置为0，默认第一次取head是有东西的，保证hh比tt大是为了在判断empty的时候可以用tt >= hh作为not empty的条件
int hh = 0,tt = -1;

void push(int x){
    q[++tt] = x;
}

void pop(){
    hh++;
}

void get_first(){
    cout << q[hh] << endl;
}

void empty(){
    if(tt >= hh)
        cout << "NO" << endl;
    else
        cout << "YES" << endl;
}

int main(){
    int M;
    cin >> M;
    string s;
    for(int i = 0; i < M; i++) {
        cin >> s;
        if(s == "push"){
            int x;
            cin >> x;
            push(x);
        }else if(s == "query"){
            get_first();
        }else if(s == "pop"){
            pop();
        }else if(s == "empty"){
            empty();
        }
    }
}