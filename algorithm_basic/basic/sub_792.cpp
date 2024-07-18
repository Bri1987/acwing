#include <iostream>
#include <vector>

//判断是否有 A >=B
bool cmp(std::vector<int> A, std::vector<int> B){
    if(A.size() != B.size())
        return A.size() > B.size();
    for(int i = A.size() - 1; i >= 0; i--){
        if(A[i] != B[i])
            return A[i] > B[i];
    }
    return true;
}

//输入进来一定是大数-小数 , A.size() >= B.size()
std::vector<int> sub(std::vector<int> A, std::vector<int> B){
    int t = 0;
    std::vector<int> C;
    //Ai - Bi + 10 - t
    //t表示借位
    for(int i = 0; i < A.size(); i++){
        t = A[i] - t;
        if(i < B.size())
            t -= B[i];
        //+10为避免t此刻是负数
        C.push_back((t + 10) % 10);

        if(t < 0) t = 1;
        else t = 0;
    }

    //删除所有前导0，比如003
    while (C.size() > 1 && C.back() == 0)
        C.pop_back();
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

    std::vector<int> C;
    if(cmp(A,B)){
        C = sub(A,B);
        for (int i = C.size() - 1; i < C.size(); i--){
            std::cout << C[i] ;
        }
    } else{
        C = sub(B,A);
        printf("-");
        for (int i = C.size() - 1; i < C.size(); i--){
            std::cout << C[i] ;
        }
    }
}