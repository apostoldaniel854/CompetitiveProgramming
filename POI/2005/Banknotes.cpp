#include <bits/stdc++.h>

using namespace std;


using ll = long long;
#define pb push_back
#define dbg(x) cerr << #x << " " << x << "\n"

const int N = 200, K = 2e4;
int b[1 + N], c[1 + N], ans[1 + N];
int dp[1 + K], newDp[1 + K];
pair <int, int> from[1 + K];
int ind[1 + N];

bool cmp (int x, int y) {
    return b[x] > b[y];
}

int main () {
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    for (int i = 1; i <= n; i++)
        cin >> c[i];
    for (int i = 1; i <= n; i++)
        ind[i] = i;
    sort (ind + 1, ind + n + 1, cmp);
    int k;
    cin >> k;
    for (int cost = 0; cost <= k; cost++)
        dp[cost] = -1;
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        int index = ind[i];
        for (int curCost = 0; curCost <= k; curCost++)
            newDp[curCost] = dp[curCost];
        for (int curCost = 0; curCost < k; curCost++) {
            if (dp[curCost] != -1) {
                int cnt = 1;
                while (cnt * b[index] + curCost <= k && cnt <= c[index] && newDp[curCost + cnt * b[index]] == -1) {
                    newDp[curCost + cnt * b[index]] = dp[curCost] + cnt;
                    from[curCost + cnt * b[index]] = {cnt, index};
                    cnt++;
                }
            }
        }
        for (int curCost = 0; curCost <= k; curCost++)
            dp[curCost] = newDp[curCost];
    }

    cout << dp[k] << "\n";
    int curCost = k;
    while (curCost) {
        pair <int, int> w = from[curCost];
        ans[w.second] = w.first;
        curCost -= w.first * b[w.second];
    }
    for (int i = 1; i <= n; i++)
        cout << ans[i] << " ";
    return 0;
}
