#include <iostream>
#include <algorithm>

using namespace std;
const int N = 100010;

int n;
struct Range{
    int l,r;
    //重载一下，以左端点从小到大排序
    bool operator<(const Range& w)const{
        return l < w.l;
    }
}range[N];

int main(){
    int need_l,need_r;
    cin >> need_l >> need_r;

    cin >> n;
    for(int i = 0; i < n;i++){
        int l,r;
        cin >> l >> r;
        range[i] = {l,r};
    }
    //1. 排序
    sort(range,range+n);

    //每当找到包含左端点的最长右区间时，就更新需要的左端点
    int res = 0, cur_l = need_l;
    //自己做的原版
//    for(int i = 0; i < n;i++){
//        if(range[i].r < cur_l)
//            continue;
//
//        if(range[i].l > cur_l)
//            break;
//
//        if(range[i].l <= cur_l && range[i].r >= cur_l){
//            //左端点比l小，右端点比l大的里面选一个
//            int max_r = -2e9;
//            while (range[i].l <= cur_l && i < n){
//                if(range[i].l <= cur_l && range[i].r >= cur_l)
//                    max_r = max(max_r,range[i].r);
//                i++;
//            }
//            i--;res++;
//            cur_l = max_r;
//            if(cur_l >= need_r){
//                cout << res << endl;
//                return 0;
//            }
//        }
//
//    }

    for(int i = 0; i < n;i++){
        if(range[i].r < cur_l)
            continue;

        //一定中间有不能覆盖的段了
        if(range[i].l > cur_l)
            break;

        if(range[i].l <= cur_l){
            //左端点比l小，右端点比l大的里面选一个 右端点伸最长的段
            int max_r = -2e9;
            //其实也是一种双指针
            //即使右端点没触到l也无所谓，max_r算最大不会用它的，能走到这里的由于上面那个continue，至少有一个肯定是覆盖到cur_l点的
            while (range[i].l <= cur_l && i < n){
                max_r = max(max_r,range[i].r);
                i++;
            }
            i--;res++;
            //更新原左端点为已经触碰到的最远点
            cur_l = max_r;
            //已经覆盖了就可以直接结束了
            if(cur_l >= need_r){
                cout << res << endl;
                return 0;
            }
        }

    }
    cout << -1;
    return 0;
}