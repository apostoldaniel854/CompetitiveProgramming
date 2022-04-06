#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair <int, int>;

void fastios() {
    freopen("cmlsc.in", "r", stdin);
    freopen("cmlsc.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
}

const int maxn = 1024;

int M, N;
int A[1 + maxn], B[1 + maxn];
int dp[1 + maxn][1 + maxn];
pii from[1 + maxn][1 + maxn];
int main() {
    fastios();
    cin >> N >> M;
    for (int i = 1; i <= N; i++)
        cin >> A[i];
    for (int i = 1; i <= M; i++)
        cin >> B[i];
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++) {
            if (dp[i - 1][j] > dp[i][j - 1]) {
                dp[i][j] = dp[i - 1][j];
                from[i][j] = {i - 1, j};
            }
            else {
                dp[i][j] = dp[i][j - 1];
                from[i][j] = {i, j - 1};
            }
            if (A[i] == B[j] && dp[i - 1][j - 1] + 1 > dp[i][j]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                from[i][j] = {i - 1, j - 1};
            }
        }
    vector <int> sol;
    int i = N, j = M;
    while (i > 0 && j > 0) {
        int ni = from[i][j].first;
        int nj = from[i][j].second;
        if (dp[ni][nj] + 1 == dp[i][j])
            sol.push_back(A[i]);
        i = ni;
        j = nj;
    }
    reverse(sol.begin(), sol.end());
    assert((int)sol.size() == dp[N][M]);
    cout << sol.size() << "\n";
    for (int x : sol)
        cout << x << " ";
    cout << "\n";
    return 0;
}
