#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef pair<int, int> PII;

const int N = 50;

int n;
int w[N];
unsigned f[N][N];
int root[N][N];

void dfs(int l, int r)
{
    if (l > r) return;

    int k = root[l][r];
    printf("%d ", k);
    dfs(l, k - 1);
    dfs(k + 1, r);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++ ) scanf("%d", &w[i]);
    for (int len = 1; len <= n; len ++ )
        for (int l = 1; l + len - 1 <= n; l ++ )
        {
            int r = l + len - 1;

            for (int k = l; k <= r; k ++ )
            {
                int left = k == l ? 1 : f[l][k - 1];
                int right = k == r ? 1 : f[k + 1][r];
                int score = left * right + w[k];
                if (l == r) score = w[k];
                if (f[l][r] < score)
                {
                    f[l][r] = score;
                    root[l][r] = k;
                }
            }
        }

    printf("%d\n", f[1][n]);
    dfs(1, n);
    puts("");

    return 0;
}