#include <iostream>

//--------|
//    ----|----
//    |   |
//1 2 3 3 3 4 5

//右界限，是找left point
//如果大于val就在绿色，小于等于val就在红色
int bsearch_1(const int q[],int l, int r,int val){
    while (l < r){
        int mid = (l+r+1) >> 1;

        //在左边红色的，不满足条件的
        if(q[mid] <= val) {
            l = mid;
        } else {
            r = mid -1;
        }
    }
    //如果找不到该数，则返回-
    if(q[l] != val)
        return -1;
    return l;
}

//左界限，是找right point
//如果大于等于val就在绿色，小于val就在红色
int bsearch_2(const int q[],int l, int r,int val){
    while (l < r){
        int mid = (l + r) >> 1;

        //在绿色
        if(q[mid] >= val){
            r = mid;
        } else{
            l = mid + 1;
        }
    }
    if(q[l] != val)
        return -1;
    return l;
}

int main(){
    int n,time;
    scanf("%d %d",&n,&time);
    int *tmp = new int[n];

    for(int i=0;i<n;i++){
        scanf("%d",&tmp[i]);
    }

    int val;
    for(int i=0;i<time;i++){
        scanf("%d",&val);
        printf("%d ", bsearch_2(tmp,0,n-1,val));
        printf("%d\n", bsearch_1(tmp,0,n-1,val));
    }
}