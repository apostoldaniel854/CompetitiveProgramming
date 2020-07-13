#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define pb push_back
#define dbg(x) cerr << #x << " " << x << "\n"

/**
-   this problem can be solved using dp[position][mask] = how many happy children (that have range till position) we have
    and mask represents the state of the last 4 cages (0 - if we remove or 1 - if not). We only need the last 4 positions
-   we solve the problem that the cages are in a circle by fixind the state of the first 4 cages
**/

const int K = 5, N = 1e4;
int n, c;

int dp[1 + N][1 << (K - 1)];
int add[1 + N][1 << K];
bool used[1 + N];

int getMask (int start, vector <int> v) {
    for (int x : v)
        used[x] = true;
    int mask = 0;
    for (int i = 0; i < K; i++)
        if (used[(start + i - 1) % n + 1])
            mask += (1 << i);
    for (int x : v)
        used[x] = false;
    return mask;
}

int solveDp (int start, int step, int mask) {
    if (step == n + 1)
        return 0;
    if (dp[step][mask] != -1)
        return dp[step][mask];
    int ans = 0;
    if (step + 4 <= n) {
        for (int state = 0; state < 2; state++)
            ans = max (ans, solveDp (start, step + 1, (mask + (state << 4)) / 2) + add[step][mask + (state << 4)]);
    }
    else {
        int state = (start >> (step - 1 - (n - K + 1))) % 2;
        ans = max (ans, solveDp (start, step + 1, (mask + (state << 4)) / 2) + add[step][mask + (state << 4)]);
    }
    dp[step][mask] = ans;
    return dp[step][mask];
}

void solveTest () {
    memset (add, 0, sizeof (add));
    cin >> n >> c;
    for (int i = 1; i <= c; i++) {
        int start, f, l;
        cin >> start >> f >> l;
        vector <int> fear, love;
        while (f--) {
            int x;
            cin >> x;
            fear.pb (x);
        }
        while (l--) {
            int x;
            cin >> x;
            love.pb (x);
        }
        int fearMask = getMask (start, fear);
        int loveMask = getMask (start, love);
        for (int mask = 0; mask < (1 << K); mask++)
            if ((mask & loveMask) | (~mask & fearMask))
                add[start][mask]++;
    }
    int ans = 0;
    for (int mask = 0; mask < (1 << (K - 1)); mask++) {/// just the first 4
        memset (dp, -1, sizeof (dp));
        ans = max (ans, solveDp (mask, 1, mask));
    }
    cout << ans << "\n";
}

int main () {
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);

    int t;
    cin >> t;
    while (t--)
        solveTest ();
    return 0;
}
