#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define pb push_back
#define dbg(x) cerr << #x << "\n"

const int N = 1e5;
int a[1 + N];

/**
-   We can change the direction in 0 time so we don't care about the initial direction of each train
-   We see that if we order the trains by coordinate in ascending order we will put LRLRLRLR...
-   We can say that we want one train at a fixed coordinate, then we can find how much the other trains move,
    but we can see that if the minimum that we moved one train is mn we can move all train back by it
    => the result is (mx - mn) / 2
**/

#define double long double

int main () {
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);
    int m, n;
    cin >> m >> n;
    for (int i = 1; i <= n; i++) {
        char way;
        cin >> a[i] >> way;
    }
    sort (a + 1, a + n + 1);
    double gap = 2.0 * m / n;
    double coord = 0;
    double mn = (1 << 30);
    double mx = -(1 << 30);
    for (int i = 1; i <= n; i += 2) {
        double diff = a[i] - coord;
        mn = min (mn, diff);
        mx = max (mx, diff);
        coord += gap;
    }
    for (int i = n - n % 2; i > 0; i -= 2) {
        double diff = 2.0 * m - a[i] - coord;
        mn = min (mn, diff);
        mx = max (mx, diff);
        coord += gap;
    }
    cout << fixed << setprecision (6) << (mx - mn) / 2.0 << "\n";
    return 0;
}
