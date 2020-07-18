#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define pb push_back
#define dbg(x) cerr << #x << " " << x << "\n"

/**
-   classic convex hull problem: https://codeforces.com/blog/entry/63823
-   dp[i] = dp[j] + s + T[i..j] * F[i..n], i < j
**/

struct F {
    int x;
    int y;
    ll val (int m) {
        return 1ll * x * m + y;
    }
};


double intersect (F a, F b) {
    return (double) (a.y - b.y) / (b.x - a.x);
}

int n, s;

const int N = 1e4;
int f[1 + N], t[1 + N];
int sumF[1 + N], sumT[1 + N];
F ec[1 + N];
int dp[1 + N];

int main () {
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);

    cin >> n;
    cin >> s;
    for (int i = 1; i <= n; i++) {
        cin >> t[i] >> f[i];
    }
    for (int i = n; i > 0; i--) {
        sumT[i] = sumT[i + 1] + t[i];
        sumF[i] = sumF[i + 1] + f[i];
    }
    deque <int> hull;
    hull.push_back (n + 1);
    ec[n + 1] = {0, 0};
    for (int i = n; i > 0; i--) {
        while (hull.size () > 1 && intersect (ec[hull[0]], ec[hull[1]]) < (double) sumF[i])
            hull.pop_front ();
        int best = hull.front ();
        dp[i] = dp[best] + (s + sumT[i] - sumT[best]) * sumF[i];
        ec[i] = {-sumT[i], dp[i]};
        while (hull.size () > 1 && intersect (ec[hull.end ()[-2]], ec[hull.end ()[-1]]) > intersect (ec[hull.end ()[-1]], ec[i]))
            hull.pop_back ();
        hull.push_back (i);
    }
    cout << dp[1] << "\n";
    return 0;
}
