#include <iostream>
#include <tuple>

using namespace std;

tuple<int,int> find_right_only_sum_index(const int A[],const int B[],int n, int m ,int x){
    //!! j的起点可以是从后开始，这样i不用后退
    //i
    //           j ______
    //i与比j大的索引一定不可能，但停下的时候由于一定是A[i] + B[j] <= x , i与比j小的索引也一定不可能，所以要么就是这个i，要么一定不是这个i，i不用后退
    //由于i是越来越大的，j也不可能后退，再退只能变大
    for(int i = 0,j = m-1; i < n && j >= 0 ;i++){
        while (A[i] + B[j] > x)
            j--;
        if(A[i] + B[j] == x)
            return {i,j};
    }
    return {-1,-1};
}

int main(){
    int n,m,x;
    cin >> n >> m >> x;
    int A[n],B[m];
    for(int i = 0; i < n; i++)
        cin >> A[i];
    for(int i = 0; i < m; i++)
        cin >> B[i];

    auto [i , j] = find_right_only_sum_index(A,B,n,m,x);
    cout << i << " " << j << endl;
}