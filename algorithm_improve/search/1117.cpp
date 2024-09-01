#include <iostream>
#include <vector>

using namespace std;
const int N = 22;
int n;
vector<string> words;
int st[N];
int connectLen[N][N];
int mx = 1;

int canConnection(const string& first, const string& second){
    if(first.size() == 1 || second.size() == 1)
        return false;

    int l = min(first.size(), second.size());
    int len = 0;
    for(int i = 1; i <= l-1; i++){
        //cout << first.substr(first.size()-i,i) <<"   " << second.substr(0,i) << endl;
        if(first.substr(first.size()-i,i) == second.substr(0,i)){
            len = i;
            break;
        }
    }
    return len;
}

void init(){
    for(int i = 0; i < words.size(); i++){
        for(int j = 0; j < words.size(); j++){
            connectLen[i][j] = canConnection(words[i],words[j]);
           // cout << words[i] << "," << words[j] << " . " << connectLen[i][j] << endl;
        }
    }
}

void dfs(int first, int cur_len){
    for(int i = 0; i < words.size(); i++){
        if(st[i] < 2 && connectLen[first][i]){
            st[i]++;
            cur_len += words[i].size() - connectLen[first][i];
            mx = max(mx, cur_len);
            dfs(i, cur_len);
            cur_len -= words[i].size() - connectLen[first][i];
            st[i]--;
        }
    }
}

int main(){
    cin >> n;
    char bg;
    for(int i = 0; i < n; i++){
        string word;
        cin >> word;
        words.push_back(word);
    }
    cin >> bg;
    init();
    for(int i = 0; i < n; i++){
        if(bg == words[i][0]){
            st[i]++;
            mx = max(mx, (int)words[i].size());
            dfs(i, words[i].size());
            st[i]--;
        }
    }
    cout << mx;
    return 0;
}