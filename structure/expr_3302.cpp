#include <iostream>
#include <string>
#include <stack>
#include <unordered_map>

using namespace std;

//装加减乘除
stack<char> op;
//装数字
stack<int> num;
//(和)默认pr的value为0 , value小的优先值低
unordered_map<char, int> pr = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};

void eval()
{
    int b = num.top(); num.pop();
    int a = num.top(); num.pop();
    char c = op.top(); op.pop();

    int x;
    if(c == '+') x = a + b;
    else if(c == '-') x = a - b;
    else if(c == '*') x = a * b;
    else x = a / b;

    num.push(x);
}

int main()
{
    string s;
    cin >> s;

    for(int i = 0; i < s.size(); i++)
    {
        char c = s[i];
        if(isdigit(c))
        {
            int x = 0, j = i;
            while(j < s.size() && isdigit(s[j])) x = 10 * x + s[j++] - '0';
            i = j - 1;
            num.push(x);
        }
        else if(c == '(') op.push(c);
        else if(c == ')')
        {
            //每次读到)就把这个()能算的都算出来，然后再把(弄出来，消除(
            while(op.size() && op.top() != '(') eval();
            op.pop();
        }
        else
        {
            //如果这个*/前面有优先级低(或+的还没算，那么目前就不能算，得等之后再eval()
            //比如3*(6+7)，读到+的时候前面还有(，所以不能把3,6提出来
            //比如3+6*7，读到*的时候前面还有+，所以不能把3,6提出来
            while(op.size() && pr[op.top()] >= pr[c]) eval();
            op.push(c);
        }
    }
    //此时已经消去了全部括号，顺序也都对了，比如3+6*7
    //+*
    //367
    //比如3*6+7
    //+
    //18 7
    while(op.size()) eval();
    cout << num.top() << endl;

    return 0;
}