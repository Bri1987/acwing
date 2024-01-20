#include <iostream>

using namespace std;

//!! 注意存储res的数据类型大小
void merge_sort(int q[],int l, int r, unsigned long* res){
    if(l >= r) return;

    //1. 递归排序左边和右边
    int mid = (l + r) >>1;
    merge_sort(q,l,mid,res);
    merge_sort(q,mid + 1,r,res);

    //2. 归并，将两个有序的数组合并为一个有序的数组
    int *tmp = new int[r-l+1];
    int k = 0, i = l, j = mid + 1;
    //i____mid j____ , 如果 q[i] > q[j]，就是逆序对
    while (i <= mid && j <= r){
        if(q[i] <= q[j])
            tmp[k++] = q[i++];
        else{
            *res += mid - i + 1;
            tmp[k++] = q[j++];
        }
    }

    //!! 以下代码为错误代码，因为之前直接用mid -i 把i后面每个数的逆序对都已经分别对每个q[j]加上了，这里就重复计算了
    //如果是i <= mid，就说明i的这部分都比j的大了，也是逆序
//    if(i <= mid) {
//        *res += (mid - i + 1)*(r - mid);
//    }
    while (i <= mid) tmp[k++] = q[i++];
    while (j <= r) tmp[k++] = q[j++];

    //3. 赋值回原来的q
    for(i = l,j = 0; i <= r ;i++,j++){
        q[i] = tmp[j];
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int* arr = new int[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    unsigned long res = 0;
    merge_sort(arr, 0, n - 1,&res);
    printf("%ld", res);

    delete[] arr;

    return 0;
}