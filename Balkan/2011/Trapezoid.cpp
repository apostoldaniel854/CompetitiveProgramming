#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define pb push_back
#define dbg(x) cerr << #x << " " << x << "\n"

/**
- The problem can be solved by dp optimized by an aib
- To use the aib we normaliza all coordinates
- Then we sort the top points (x is a query, y is an update) while the positions in aib mean the coordinates on bottom
**/

const int N = 1e5;
const int START = 0, FINISH = 1;
const int MOD = 30013;

struct Node {
    int best;
    int cnt;
};
Node join (Node a, Node b) {
    Node c = a;
    if (c.best < b.best)
        c.best = b.best, c.cnt = 0;
    if (c.best == b.best) {
        c.cnt += b.cnt;
        if (c.cnt >= MOD)
            c.cnt -= MOD;
    }
    return c;
};
Node aib[1 + 2 * N];
int lsb (int x) {
    return x & -x;
}
int n;
void upd (int pos, Node value) {
    while (pos <= 2 * n) {
        aib[pos] = join (aib[pos], value);
        pos += lsb (pos);
    }
}
Node qry (int pos) {
    Node ans = {0, 0};
    while (pos) {
        ans = join (ans, aib[pos]);
        pos -= lsb (pos);
    }
    return ans;
}

struct Trapezoid {
    int x1;
    int y1;
    int x2;
    int y2;
};
Trapezoid trap[1 + N];
pair <int, int> event[1 + 2 * N];
Node dp[1 + N];
int main () {
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);

    cin >> n;
    map <int, int> mpTop, mpBottom;
    for (int i = 1; i <= n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        trap[i] = {x1, y1, x2, y2};
        mpTop[x1] = 0;
        mpTop[y1] = 0;
        mpBottom[x2] = 0;
        mpBottom[y2] = 0;
    }

    int nr = 0;
    for (auto &x : mpTop) x.second = ++nr;
    nr = 0;
    for (auto &x : mpBottom) x.second = ++nr;
    for (int i = 1; i <= n; i++) {
        trap[i].x1 = mpTop[trap[i].x1];
        trap[i].y1 = mpTop[trap[i].y1];
        trap[i].x2 = mpBottom[trap[i].x2];
        trap[i].y2 = mpBottom[trap[i].y2];
        event[trap[i].x1] = {i, START};
        event[trap[i].y1] = {i, FINISH};
    }
    for (int i = 1; i <= 2 * n; i++) {
        int index = event[i].first;
        int type = event[i].second;
        if (type == START) {
            dp[index] = qry (trap[index].x2);
            if (not dp[index].cnt)
                dp[index].cnt++;
            dp[index].best++;
        }
        if (type == FINISH)
            upd (trap[index].y2, dp[index]);
    }
    Node ans = {0, 0};
    for (int i = 1; i <= n; i++)
        ans = join (ans, dp[i]);
    cout << ans.best << " " << ans.cnt << "\n";
    return 0;
}
/**
    7
    1 3 1 9
    4 7 2 8
    11 15 4 12
    10 12 15 19
    16 23 16 22
    20 22 13 25
    30 31 30 31
**/
