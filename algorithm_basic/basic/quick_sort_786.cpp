#include <iostream>

using namespace std;

int quick_sort(int q[],int l, int r, int k){
    if(l >= r) return q[k];

    //1. 确定分界点x , 分界点选中间好像最快
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
    //根据已知的k值，左段和右段会有一部分完全不需要处理
    //注意判断条件时不能用i，因为此时如果退出则状态一定是 i >= j，所以取最小的j
    if(j >= k) return quick_sort(q,l,j,k);
    else return quick_sort(q,j+1 , r,k);
}

int main() {
    int n;
    scanf("%d", &n);

    int k;
    scanf("%d", &k);

    int* arr = new int[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("%d",quick_sort(arr, 0, n - 1,k - 1));

    delete[] arr;

    return 0;
}