#include <cstring>
#include <iostream>

using namespace std;

//开放寻址法一般开 数据范围的 2~3倍, 这样大概率就没有冲突了
const int N = 2e5 + 3;        //大于数据范围的第一个质数
//表示坑位没人，选择一个不在题目常数范围内(|10^9|)的数
const int null = 0x3f3f3f3f;  //规定空指针为 null 0x3f3f3f3f

int h[N];

int find(int x) {
    int t = (x % N + N) % N;
    while (h[t] != null && h[t] != x) {
        t++;
        if (t == N) {
            t = 0;
        }
    }
    return t;  //如果这个位置是空的, 则返回的是他应该存储的位置
}

int n;

int main() {
    cin >> n;

    memset(h, 0x3f, sizeof h);  //规定空指针为 0x3f3f3f3f

    while (n--) {
        string op;
        int x;
        cin >> op >> x;
        if (op == "I") {
            //这里是很精巧的操作 !!!
            h[find(x)] = x;
        } else {
            if (h[find(x)] == null) {
                puts("No");
            } else {
                puts("Yes");
            }
        }
    }
    return 0;
}