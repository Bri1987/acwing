#include<iostream>
#include<cmath>

using namespace std;

// 1- num中, 数字x出现的次数
int cnt(int num,int x){
    int len = 0, temp = num;

    //求数字的位数
    while(temp){
        len++;
        temp /= 10;
    }

    int sum = 0;
    //分x在每一位出现的情况讨论组着加
    for(int i= 1 ; i <= len; i++){

        //p 是一个用于将数字 num 切割成各个位的除数，例如当 i=1 时，p 的值为 1，当 i=2 时，p 的值为 10。
        //l 表示要找位的前面的数的大小，即 num中 位数 i 左边的数值。通过 num/p/10 计算得到，当在最高位时，l==0;
        //r 表示 num中 位数 i 右边的数值。通过 num%p 计算得到。
        //di 表示 num中 位数 i 的数值。通过 num/p%10 计算得到。
        int p = pow(10, i-1), l = num/p/10, r = num % p, di=num/p%10;

        //零不能在最高位
        if(l||x){

            //当要找的是零的时候，前面的数必定不可能是0（由于上面的判断，x和l只能一个是0）
            //只能从"001~abc-1"选数字了少了"000"这种情况，所以要(l-1) (即比如找第三位为0，可以01000，但不能00000，因为求的是1-num)
            if(x == 0) sum += (l-1) * p;

            //当要找的不是零的时候(数字可以从000~abc-1)
            if(x != 0) sum += l * p;

            //分几种情况
            //1. 要找的这位数字x和当前num循环到的这一位值相同di，num中 位数 i 右边的数可取
            if( x== di) sum += r+1;
            //2. 要找的这位数字x大于num循环到的这一位的值di，比如找3，但是循环到的位及后面连起来是256, 是不可能有的
            //3. 要找的这位数字x小于num循环到的这一位的值di，比如找3，但是循环到的位及后面连起来是456, p = 100 ,即可以有300-399 满满的p(100)个
            if( x < di ) sum+=p;

        }
    }
    return sum;
}
int main(){
    int n,m;
    while(cin >> n >> m, n || m){
        if(n > m){
            swap(n,m);
        }
        int res;
        for(int i = 0; i <= 9; i++){

            //前缀和
            res = cnt(m,i) - cnt(n-1,i);
            cout << res << " ";
        }
        cout << endl;
    }
    return 0;
}