#include <iostream>
using namespace std;

bool is_son(const int a[],const int b[],int n, int m){
    int i = 0,j = 0;
    for(; i < n && j < m ;i++,j++){
        while(j < m && a[i] != b[j])
            j++;
        if(j == m)
            return false;
    }

    //注意这里，必须保证i是走完了，全都找到了才行，因为退出循环可能是因为找到一个j之后再j++超过了m
    if(i == n)
        return true;
    return false;
}

int main(){
    int n,m;
    cin >> n >> m;
    int a[n],b[m];
    for(int i = 0; i < n; i++)
        cin >> a[i];
    for(int i = 0; i < m; i++)
        cin >> b[i];

    if(is_son(a,b,n,m))
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
}