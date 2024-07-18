#include <iostream>

using namespace std;

const int N = 110;
int f1[N],f2[N],h[N];

int main(){
    int k;
    cin >> k;
    while(k--){
        int n;
        cin >> n;
        for(int i = 1; i <= n; i++){
            cin >> h[i];
            f1[i] = 1;
            f2[i] = 1;
        }

        int res = 1;
        //左->右
        for(int i = 2; i <= n; i++){
            for(int j = 1; j < i; j++){
                if(h[j] > h[i]){
                    f1[i] = max(f1[i],f1[j]+1);
                    res = max(res,f1[i]);
                }
            }
        }
        //右->左
        for(int i = 2; i <= n; i++){
            for(int j = 1; j < i; j++){
                if(h[j] < h[i]){
                    f2[i] = max(f2[i],f2[j]+1);
                    res = max(res,f2[i]);
                }
            }
        }
        cout << res << endl;
    }
    return 0;
}