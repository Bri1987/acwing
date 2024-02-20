#include <iostream>

using namespace std;

const int N  = 100010;
long long int st[N];
int top = -1;

void push(long long int x){
    st[++top] = x;
}

void pop(){
    top--;
}

void get_top(){
    cout << st[top] << endl;
}

void empty(){
    cout << (top == -1 ? "YES" : "NO") << endl;
}

int main(){
    int M;
    cin >> M;
    string s;
    for(int i = 0; i < M; i++){
        cin >> s;
        if(s == "push"){
            int x;
            cin >> x;
            push(x);
        }else if(s == "query"){
            get_top();
        }else if(s == "pop"){
            pop();
        }else if(s == "empty"){
            empty();
        }
    }
}