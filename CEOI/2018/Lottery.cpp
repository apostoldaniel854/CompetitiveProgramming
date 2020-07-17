#include <bits/stdc++.h>
 
using namespace std;
const int N = 1e4, Q = 100;
 
int a[1 + N], ans[1 + Q + 1][1 + N + 1], match[1 + N], nrm[1 + N + 1], k[1 + N];
 
int main () {
    int n, l;
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);
    cin >> n >> l;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    int q;
    cin >> q;
    for (int i = 1; i <= q; i++) {
        cin >> k[i];
        nrm[k[i]] = 1;
    }
    for (int i = l; i >= 0; i--)
        nrm[i] += nrm[i + 1];
    for (int i = 0; i <= l; i++)
        nrm[i] = q - nrm[i] + 1;
    for (int d = 1; d + l <= n; d++) {
        memset (match, 0, sizeof match);
        for (int i = 1; i + d <= n; i++)
            if (a[i] == a[i + d])
                match[i] = 0;
            else
                match[i] = 1;
        for (int i = 1; i + d <= n; i++)
            match[i] += match[i - 1];
        for (int i = 1; i + l - 1 <= n - d; i++) {
            ans[ nrm[ match[i + l - 1] - match[i - 1] ] ][i]++;
            ans[ nrm[ match[i + l - 1] - match[i - 1] ] ][i + d]++;
        }
    }
 
    for (int i = 1; i <= q; i++)
        for (int j = 1; j <= n - l + 1; j++)
            ans[i][j] += ans[i - 1][j];
 
    for (int i = 1; i <= q; i++) {
        for (int j = 1; j <= n - l + 1; j++)
            cout << ans[nrm[k[i]]][j] << " ";
        cout << "\n";
    }
    return 0;
}
