#include <bits/stdc++.h>

using namespace std;

const int N = 20;

int a[1 + N];
double dp[1 << N];

int main() {
    int n;
    cin >> n;
    double sum = 0;
    for (int i = 0; i < n; i++)
        cin >> a[i], sum += a[i];
    dp[0] = 0;
    for (int mask = 1; mask < (1 << n); mask++) {
        double in = 0, out = 0;
        for (int i = 0; i < n; i++)
            if (mask & (1 << i))
                out += a[i] * dp[mask ^ (1 << i)];
            else
                in += a[i];
        in /= sum;
        out /= sum;
        in = 1 - in;
        dp[mask] = (1 + out) / in;
    }
    cout << fixed << setprecision (7) << dp[(1 << n) - 1];
    return 0;
}
