#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define pb push_back
#define dbg(x) cerr << #x << " " << x << "\n"

/**
-   Obs: If we substract P from every value the problem becomes find the subsequences with sum greater than 0
=>  Now we can use an aib to solve the problem: we go through the prefix sums and find the number of prefix sums already went through lower than the current one
    but first we need to normalize the values of the prefix sums
**/

const int N = 1e6;

int n, p;
int aib[1 + N + 2];
int a[1 + N];
int val[1 + N];


inline int lsb (int x) {
    return x & -x;
}

int qry (int pos) {
    int ans = 0;
    while (pos) {
        ans += aib[pos];
        pos -= lsb (pos);
    }
    return ans;
}

void upd (int pos, int val) {
    while (pos <= n + 2) {
        aib[pos] += val;
        pos += lsb (pos);
    }
}

int main () {
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    cin >> p;
    vector <pair <ll, int>> v;
    v.pb ({0, 0});
    ll sum = 0;
    for (int i = 1; i <= n; i++) {
        a[i] -= p;
        sum += a[i];
        v.pb ({sum, i});
    }
    sort (v.begin (), v.end ());
    int cnt = 1;
    val[v[0].second] = cnt;
    for (int i = 1; i <= n; i++) {
        if (v[i].first != v[i - 1].first)
            cnt++;
        val[v[i].second] = cnt;
    }
    ll ans = 0;
    for (int i = 0; i <= n; i++) {
        ans += qry (val[i]);
        upd (val[i], 1);
    }
    cout << ans << "\n";
    return 0;
}
