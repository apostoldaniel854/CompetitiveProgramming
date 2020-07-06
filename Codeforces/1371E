#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define pb push_back
#define dbg(x) cerr << #x << " " << x << "\n"

const int INF = 2e9;

const int N = 1e5;
int a[1 + N];

int main() {
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);
    int n, p;
    cin >> n >> p;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    sort (a + 1, a + n + 1);
    int nr = 1;
    int l = 0, r = INF;
    for (int i = 1; i <= n; i++) {
        if (a[i] == a[i + 1])
            nr++;
        else
            nr = 1;
        if (i >= p)
            r = min (r, a[i] - i + p);
        l = max (l, a[i] - i + 1);
    }
    cout << max (0, r - l) << "\n";
    for (int i = l; i < r; i++)
        cout << i << " ";
    cout << "\n";
    return 0;
}
