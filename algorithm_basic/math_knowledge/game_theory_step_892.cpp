#include <iostream>

using namespace std;

/*
 * 因为第一阶拿到地面要拿一次，第二阶那两次，第三阶那三次…所以可以看成第二阶有两堆石子，第三阶有三堆....
 * 因为偶数阶石子为偶数堆，所以异或为0，奇数阶异或后就是原本石子数目，
 * 所以可以把原本所有奇数阶的石子进行异或，得到的就是答案
 */
int main(){
    int n;
    cin >> n;

    int res = 0;
    for(int i = 1; i <= n; i++){
        int num;
        cin >> num;
        if(i % 2){
            res ^= num;
        }
    }

    if(res != 0) puts("Yes");
    else puts("No");
    return 0;
}