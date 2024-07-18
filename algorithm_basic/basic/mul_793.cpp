#include <iostream>
#include <vector>

//默认A是大数，B是小数
std::vector<int> mul(std::vector<int> A, int B){
    int t = 0;
    std::vector<int> C;
    //(Ai * Bi + t~i-1~) % 10
    //ti = (Ai * Bi + t~i-1~) / 10
    for(int i = 0; i < A.size(); i++){
        //上一次循环包含了进位
        t += A[i] * B;

        C.push_back(t % 10);
        t /= 10;
    }
    if(t)
        C.push_back(t);

    //如果t是0的话，还是得删个前导0
    while (C.size() > 1 && C.back() == 0) C.pop_back();
    return C;
}

int main(){
    std::string a;
    std::cin >> a;
    int B;
    scanf("%d",&B);

    std::vector<int> A;
    //A和B倒着放进int数组，因为有进位，倒着放容易处理
    for (int i=a.size()-1; i>=0; i--)
        A.push_back(a[i] - '0');

    std::vector<int> C = mul(A,B);
    for (int i = C.size() - 1; i < C.size(); i--){
        std::cout << C[i] ;
    }
}