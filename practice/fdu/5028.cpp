#include <iostream>
using namespace std;

int a[5],sum;

int main(){
    int m;
    cin >> m;
    while(m--){
        sum = 0;
        for(int i = 0; i < 5; i++){
            cin >> a[i];
            sum += a[i];
        }

        int res = 1e9;
        for(int i = 0; i < 5; i++){
            for(int j = i+1; j < 5; j++){
                // 求补集 !
                if((sum - a[i] - a[j]) % 10 == 0){
                    res = (a[i] + a[j]) % 10;
                    break;
                }
            }
        }
        if(res == 1e9)
            cout << -1 << endl;
        else
            cout << res << endl;
    }
    return 0;
}