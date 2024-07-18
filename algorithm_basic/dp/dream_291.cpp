#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int N = 12,M = 1<<N;

long long  f[N][M];     //注意写题一般开longlong一定比int保险
bool st[M];         //记录每种方案连续空格是不是偶数
vector<int> state[M];       //记录每种方案左侧一列可以有的方案


int main(){
    int n, m;
    while(cin >> n >> m, n && m) {
        //1. 求st[j]，看单这一列能不能合法
        //共2^n种情况，从0到(2^n)-1

        //Q&A
        //Ⅰ这里cnt为什么要每次碰见j里的1时就判断？因为碰见1了就说明0不连续了，前面都是连续的0，判断连续0个数即可
        //Ⅱ 这里cnt为什么不用清空，一直累加？  因为需要所有连续0都为偶数，最后的和也一定是偶数，在出现奇数的判断里，和一定也变为了奇数。
        //Ⅲ 这里最后为什么还要单独判断？  因为j最后的连续0可能没有被1终止，需要判断最后的0是否为偶数。
        for(int j = 0; j < (1 << n); j++){
            int cnt = 0;
            bool flag = true;
            for(int i = 0; i < n; i++){
                if((j >> i) & 1){
                    //检查目前cnt是否为奇数，也就是检查第i+1位的1到上一个1或数字末尾的区间里的0的个数是否为偶数
                    if(cnt & 1){
                        flag = false;
                        break;
                    }
                } else
                    cnt++;
            }
            if(cnt & 1) flag = false;
            st[j] = flag;
        }

        //2.看第j列的状态下 j-1列(k列)允许什么状态
        for(int j = 0; j < (1 << n); j++){
            state[j].clear();
            for(int k = 0; k < (1 << n); k++){
                // j&k如果不全为0说明有两个1相撞，
                // j|k把两者的1都收集起来看合体之后的状态是否合法
                if(!(k & j) && st[j | k]){
                    state[j].push_back(k);
                }
            }
        }

        memset(f, 0, sizeof f);
        f[0][0] = 1;//因为第0-1列无法伸向第0列，所以第0列其余方案数都是0，
                    //但是第0列可以有一个状态 就是没有东西伸向第0列，所以第0列状态为0时方案数为1

        for(int i = 1; i <= m; i++){
            for(int j = 0; j < (1 << n); j++){
                //遍历左边那列允许的全部可能
                for(auto k : state[j]){
                    f[i][j] += f[i-1][k];
                }
            }
        }
        //意思是“在0~m-1列全部摆好的情况之下，棋盘右边界的右边一列没有第m列伸过来的长方形的总方案数”
        cout << f[m][0] << endl;
    }
    return 0;
}