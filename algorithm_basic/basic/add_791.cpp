#include <iostream>
#include <vector>

std::vector<int> add(std::vector<int> A, std::vector<int> B){
    if(B.size() > A.size())
        return add(B,A);
    int t = 0;
    std::vector<int> C;
    for(int i = 0; i < A.size(); i++){
        //上一次循环包含了进位
        t += A[i];
        if(i < B.size())
            t += B[i];

        C.push_back(t % 10);
        t /= 10;
    }
    if(t)
        C.push_back(t);
    return C;
}

int main(){
    std::string a, b;
    std::cin >> a >> b;

    std::vector<int> A,B;
    //A和B倒着放进int数组，因为有进位，倒着放容易处理
    for (int i=a.size()-1; i>=0; i--)
        A.push_back(a[i] - '0');

    for (int i=b.size()-1; i>=0; i--)
        B.push_back(b[i] - '0');

    std::vector<int> C = add(A,B);
    for (int i = C.size() - 1; i >= 0; i--){
        std::cout << C[i] ;
    }
}