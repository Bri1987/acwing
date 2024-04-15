#include <iostream>

using namespace std;
typedef long long LL;
const int N = 20;

int p[N];

int main(){
    int n,m;
    cin >> n >> m;
    for(int i = 0; i < m; i++)
        cin >> p[i];

    int res = 0;
    //注意i必须从1开始 !! 不然一来就n/1不满足n个
    /*
     * 通过bitset，既能通过某位是不是1来枚举出所有这个位代表的数是否参与的所有情况，又能清晰表示出奇偶
     */
    for(int i = 1; i < 1 << m;i++){
        //t表示乘积，cnt表示包含几个1(这样可以通过奇偶判断加减)
        int t = 1, cnt = 0;
        for(int j =0; j < m;j++){
            //看j位是不是1
            if((i >> j) & 1){
                cnt++;
                //如果超过n了就不用看了，一定不成立
                if((LL)t * p[j] > n) {
                    t = -1;
                    break;
                }
                t *= p[j];
            }
        }

        if(t != -1){
            //容斥原理是偶数就减，是奇数就加
            if(cnt % 2)
                res += n/t;
            else
                res -= n/t;
        }
    }
    cout << res << endl;
    return 0;
}