#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define pb push_back
#define dbg(x) cerr << #x << " " << x << "\n"
const int N = 2e5;
int f[1 + N], which[1 + N];
vector <int> tower[1 + N];

/**
-   The answer is the number of consecutive numbers that are not in the same tower
-   We can use dsu for this using small to large technique
**/

int ft (int x) {
    return f[x] == x ? x : f[x] = ft (f[x]);
}

int main () {
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);

    int n, m;
    cin >> n >> m;
    int ans = n - 1;
    for (int i = 1; i <= n; i++) {
        f[i] = i;
        cin >> which[i];
        if (which[i] == which[i - 1])
            ans--;
        tower[which[i]].pb (i);
    }
    cout << ans << "\n";
    m--;
    while (m--) {
        int x, y;
        cin >> x >> y;
        x = ft (x); y = ft (y);
        if (tower[x].size () < tower[y].size ())
            swap (x, y);
        f[y] = x;
        for (int disc : tower[y]) {
            if (disc > 1 && which[disc - 1] == x)
                ans--;
            if (disc < n && which[disc + 1] == x)
                ans--;
        }
        for (int disc : tower[y]) {
            tower[x].pb (disc);
            which[disc] = x;
        }
        cout << ans << "\n";
    }
    return 0;
}
