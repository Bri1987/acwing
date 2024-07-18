#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

//默认A是大数，B是小数
std::tuple<std::vector<int>,int> div(std::vector<int> A, int B){
    int t = 0;
    std::vector<int> C;
    for(int i = 0; i < A.size(); i++){
        //t是余数
        //t先是这次拿来除的数 , 左一位除完的余数 * 10 + Ai 是本次用来除的数
        t = A[i] + t * 10;
        C.push_back( t / B);
        t %= B;
    }

    //倒转一下C，方便删除前导0
    std::reverse(C.begin(),C.end());
    //删除前导0
    while (C.size() > 1 && C.back() == 0) C.pop_back();
    return {C,t};
}

int main(){
    std::string a;
    std::cin >> a;
    int B;
    scanf("%d",&B);

    std::vector<int> A;
    //A正放进int数组
    for (int i = 0; i < a.length(); i++)
        A.push_back(a[i] - '0');

    auto[C , t] = div(A,B);
    for (int i = C.size() - 1; i < C.size(); i--){
        std::cout << C[i] ;
    }
    std::cout << std::endl;
    std::cout << t;
}