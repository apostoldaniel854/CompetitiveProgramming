#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define pb push_back
#define dbg(x) cerr << #x << " " << x << "\n"

/**
-   A first observation is that at every step our beetle is going to have drank from an interval of coordinates
    if we sort it in ascending order
-   We have the idea for dp[left][right][0/1] = we have drank from interval [l, r] and 0 -> we are at position l, 1 -> we are at position r
**/

const int N = 300;
const ll INF = 1e18;
ll dp[1 + N][1 + N][2], newDp[1 + N][1 + N][2];
void _ (ll &a, ll b) {
    if (a > b)
        a = b;
}

int main () {
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);

    int n, m;
    cin >> n >> m;
    vector <int> drops;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        drops.pb (x);
    }
    drops.pb (0);
    sort (drops.begin (), drops.end ());
    int pivot = 0;
    while (drops[pivot]) pivot++;


    /// 0 -> L
    /// 1 -> R
    ll ans = 0;
    for (int s = 1; s <= n; s++) {
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= n; j++)
                for (int k = 0; k < 2; k++)
                    newDp[i][j][k] = INF;

        for (int l = 0; l <= n; l++) {
            for (int r = l; r <= n; r++) {
                for (int k = 0; k < 2; k++) {
                    if (l > 0) {
                        _ (newDp[l][r][0], dp[l - 1][r][0] + s * (drops[l] - drops[l - 1]));
                        _ (newDp[l][r][1], dp[l - 1][r][0] + s * (drops[r] - drops[l - 1]));
                    }
                    if (r < n) {
                        _ (newDp[l][r][0], dp[l][r + 1][1] + s * (drops[r + 1] - drops[l]));
                        _ (newDp[l][r][1], dp[l][r + 1][1] + s * (drops[r + 1] - drops[r]));
                    }
                }
            }
        }
        ans = max (ans, s * m - newDp[pivot][pivot][0]);
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= n; j++)
                for (int k = 0; k < 2; k++)
                    dp[i][j][k] = newDp[i][j][k];
    }

    cout << ans << "\n";
    return 0;
}
