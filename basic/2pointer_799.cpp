#include <iostream>

using namespace std;

//!! 可以专门拿一个数组记录各个元素出现次数，便于判断处理是否重复
int s[100010];

//standard
//与我的主要区别是，这样只要左指针要离开的不是右指针的内容，就直接while
//i的for循环里的i++使得i更适合当右指针
int find_no_repeat_len(const int a[],int len){
    int res = 0;
    //i在前，j在后
    //注意for循环条件里j < len , i < len是取或
    for(int i = 0 , j = 0; i < len; i++){
        s[a[i]]++;
        while (s[a[i]] > 1){
            //读到新的数重复了，左指针j就得往右走，i不动
            s[a[j]]--;
            j++;
        }
        res = max(res, i - j + 1);
    }
    return res;
}

//my
//int find_no_repeat_len(const int a[],int len){
//    int res = 0;
//    for(int i = 0 , j = 0; j < len; i++){
//        while (j < len && ++s[a[j]] <= 1)
//            j++;
//
//        //j已经到满足的数的后面一个位置了，所以不j - i + 1了
//        res = max(res,j - i);
//        //防止越界加个条件
//        if(j < len){
//            //由于下次++s[a[j]]还会再+1，所以先减一次
//            s[a[j]]--;
//            //左指针得移动了，减去一次对应出现次数
//            s[a[i]]--;
//        }
//    }
//    return res;
//}

int main(){
    int n;
    cin >> n;
    int a[n];
    for(int i = 0; i < n; i++)
        cin >> a[i];

    cout << find_no_repeat_len(a,n) << endl;
}