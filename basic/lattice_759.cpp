#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//整体思路是先在Merge存上横竖的线段 , 分别
//按行进行区间合并
//按列进行区间合并

//merge之后存下的：
//row : -------- --      --------
//              ----------
//col :略
//按照同一行或同一列排序，这样可以降维为普通区合并
//然后在最后将重复计算的cnt减去，由于每个点最多被横竖算两次，找到一条横或竖交叉，减个1就行，一定不会被再减了(一横一竖对应唯一点)

long long int cnt = 0;
class Choice{
public:
    int k;    //第几行或第几列
    int st;   //开始
    int ed;   //结束

    //this与c比
    //sort先比k，先锁定一定在一行或者一列，再按照左端点排序
    bool operator < (const Choice& c) const {
        if(k != c.k) return k < c.k;
        if(st != c.st) return st < c.st;
        return ed < c.ed;
    }
};

void merge(vector<Choice>& choices){
    sort(choices.begin(),choices.end());
    //sort之后先出来的一定是同一行或同一列的线段，即可一行一列的按标准区合并处理

    //初始化st,ed,k
    int st = -2e9,ed = -2e9, k = -2e9;
    vector<Choice> res;         //存储最终在行或列上把能合并的都合并了的最终线段，方便后面去重
    for(auto choice : choices){
        if(choice.k == k){
            //老行
            if(choice.st <= ed){
                //可以合并的段
                //cnt删除原来段算的
                cnt -= ed - st + 1;
                ed = max(ed,choice.ed);
                //cnt加上新来的
                cnt += ed - st + 1;
                //老段被更新了，被更新的一定是刚刚push进去的最后一个段，于是先把原来存进去的pop出来
                res.pop_back();
                res.push_back({k,st,ed});
            } else{
                //新段
                st = choice.st; ed = choice.ed;
                cnt += ed - st + 1;
                //存一下这个新段
                res.push_back({k,st,ed});
            }
        } else{
            //新开一行，一定是新线段
            k = choice.k; st = choice.st; ed = choice.ed;
            cnt += ed - st + 1;
            //存一下这个新段
            res.push_back({k,st,ed});
        }
    }

    choices = res;
}

int main(){
    int n;
    cin >> n;
    vector<Choice> rows,cols;
    for(int i = 0; i < n; i++){
        int x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;
        //先都转成从小端到大端
        if(x1 == x2) // |
            cols.push_back({x1, min(y1,y2), max(y1,y2)});
        else
            rows.push_back({y1, min(x1,x2), max(x1,x2)});
    }

    merge(rows);
    merge(cols);

    //删除重复计算的点
    //     |
    //-------------
    //     |
    for(auto col : cols)
        for(auto row : rows)
            if(row.k >= col.st && row.k <= col.ed && col.k >= row.st && col.k <= row.ed)
                cnt--;
    cout << cnt << endl;
    return 0;
}