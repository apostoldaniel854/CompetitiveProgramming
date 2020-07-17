#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define pb push_back
#define dbg(x) cerr << #x << " " << x << "\n"

const int N = 1e5, K = 100;
int a[1 + N];
int dp[1 + K][1 + N];
int mn[1 + N];
int stk[1 + N];

int main() {
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);

    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        dp[1][i] = max (dp[1][i - 1], a[i]);
    }
    dp[1][0] = (1 << 30);
    for (int nrBlocks = 2; nrBlocks <= k; nrBlocks++) {
        int vf = 0;
        dp[nrBlocks][0] = (1 << 30);
        for (int i = 1; i <= n; i++) {
            int best = dp[nrBlocks - 1][i - 1];
            while (vf && a[stk[vf]] <= a[i]) {
                best = min (best, mn[stk[vf]]);
                vf--;
            }
            mn[i] = best;
            dp[nrBlocks][i] = a[i] + best;
            if (vf)
                dp[nrBlocks][i] = min (dp[nrBlocks][i], dp[nrBlocks][stk[vf]]);
            stk[++vf] = i;
        }
    }
    cout << dp[k][n] << "\n";
    return 0;
}
