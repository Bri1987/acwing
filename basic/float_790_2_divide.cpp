#include <iostream>

double f_bsearch(double l,double r,double val){
    //要使float精确，还是用1e-7才行
    //1e-6表示的是十进制中的小数位数，即0.000001。然而，当这个小数转换为二进制表示时，可能会产生无限循环的二进制小数。
    //因此，使用1e-6（或更大的精度）作为精度值时，可能会导致舍入误差和截断误差的累积，从而无法得到预期的精确结果。
    const double eps = 1e-7;

    while (r - l > eps){
        double mid = (r + l) / 2;
        if(mid*mid*mid == val)
            return mid;
        else if(mid*mid*mid > val)
            r = mid;
        else
            l = mid;
    }
    return l;
}

int main(){
    double val;
    scanf("%lf",&val);
    printf("%lf\n", f_bsearch(-22.0,22.0,val));
}