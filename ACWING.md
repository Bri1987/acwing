# ACWING

## 第一章 基础算法（一）

### 排序

#### 快速排序

分治思想：

1. 确定分界点：left or middle or right......
2. 调整左右，比如将比分界点小的放左边，比分界点大的放右边
3. 递归处理左右两段



```c++
void quick_sort(int q[],int l, int r){
    if(l >= r) return;

    //1. 确定分界点x
    //注意这里的i和j都比元素范围要大1 , 因为在后面的步骤中会先左移右移（swap之后肯定会先移动），所以将第一次也统一
    int i = l - 1, j = r + 1, x = q[(l + r) >> 1];

    //2. 调整左右，比如将比分界点小的放左边，比分界点大的放右边
    while(i < j){
        while (q[++i] < x);
        while (q[--j] > x);
        //注意还需判断一次 i < j
        if(i < j)
            swap(q[i],q[j]);
    }

    //3. 递归处理左右两段
    //注意判断条件时不能用i，因为此时如果退出则状态一定是 i >= j，所以取最小的j
    quick_sort(q,l,j);
    quick_sort(q,j+1 , r);
}
```





#### 归并排序

1. 递归排序左边和右边
2. 归并，将两个有序的数组合并为一个有序的数组
3. 将tmp数组重新赋值回q数组



```c++
void merge_sort(int q[],int l, int r){
    if(l >= r) return;

    //1. 递归排序左边和右边
    int mid = (l + r) >>1;
    merge_sort(q,l,mid);
    merge_sort(q,mid + 1,r);

    //2. 归并，将两个有序的数组合并为一个有序的数组
    int *tmp = new int[r-l+1];
    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r){
        if(q[i] < q[j])
            tmp[k++] = q[i++];
        else
            tmp[k++] = q[j++];
    }

    while (i <= mid) tmp[k++] = q[i++];
    while (j <= r) tmp[k++] = q[j++];

    //3. 赋值回原来的q
    for(i = l,j = 0; i <= r ;i++,j++){
        q[i] = tmp[j];
    }
}
```

