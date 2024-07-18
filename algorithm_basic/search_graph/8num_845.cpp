#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

//每个状态是一个字符串 , 终点状态就是12345678x
queue<string> q;
//表示每个字符串状态是否出现过, 和之前的Maze很像
//为0代表没有走过，为正数代表从起点开始走的距离(移动的次数)
//和maze一样的道理，第一次走到的一定是最近的
unordered_map<string, int> d;

int main(){
    string c, start;
    //输入起始状态
    for(int i = 0; i < 9; i++){
        cin >> c;
        start += c;
    }

    int dx[4]={-1,1,0,0};
    int dy[4]={0,0,-1,1};

    q.push(start);
    while (!q.empty()){
        string cur = q.front();
        q.pop();

        if(cur == "12345678x"){
            cout << d[cur];
            return 0;
        }
        //找到现在这个字符串x所在的位置 , 查询x在字符串中的下标，然后转换为在矩阵中的坐标
        int k = cur.find('x');
        int x = k / 3, y = k % 3;
        for(int i = 0; i < 4; i++) {
            //求转移后'x'的坐标
            int a = x + dx[i], b = y + dy[i];
            int distance = d[cur];
            swap(cur[k], cur[a * 3 + b]);
            if(a >= 0 && a < 3 && b >= 0 && b < 3 && !d.count(cur)){
                q.push(cur);
                d[cur] = distance + 1;
            }
            //还原
            swap(cur[k], cur[a * 3 + b]);
        }
    }
    cout << -1;
    return 0;
}