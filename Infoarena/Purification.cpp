#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define pb push_back
#define dbg(x) cerr << #x << " " << x << "\n"
/**
-   We act like there's also a fictive node 0 so with w = 0 so that we can do the problem for multiple
    componenents easier
-   For each node we find the order in which we destroy the nests in the subtree of that node
-   The algorithms consists in merging the orders of two sets by running a dp till we have the best order in the root = fictive node = 0
**/

const int N = 2000;

vector <int> gr[1 + N];
int w[1 + N];
int dp[1 + N][1 + N];

void pushFront (vector <int> &v, int x) {
    reverse (v.begin (), v.end ());
    v.pb (x);
    reverse (v.begin (), v.end ());
}

void _ (int &a, int b) {
    if (a > b)
        a = b;
}

vector <int> join (vector <int> a, vector <int> b) {
    for (int i = 0; i <= a.size (); i++)
        for (int j = 0; j <= b.size (); j++)
            dp[i][j] = (1 << 30);
    dp[0][0] = 0;
    for (int i = 0; i <= a.size (); i++)
        for (int j = 0; j <= b.size (); j++) {
            if (i < a.size ()) _ (dp[i + 1][j], dp[i][j] + (i + j + 1) * w[a[i]]);
            if (j < b.size ()) _ (dp[i][j + 1], dp[i][j] + (i + j + 1) * w[b[j]]);
        }
    int i = a.size (), j = b.size ();
    vector <int> order;
    while (i > 0 || j > 0) {
        if (i > 0 && dp[i - 1][j] + (i + j) * w[a[i - 1]] == dp[i][j]) {
            i--;
            order.pb (a[i]);
        }
        else {
            j--;
            order.pb (b[j]);
        }
    }
    reverse (order.begin (), order.end ());
    return order;
}

vector <int> dfs (int node) {
    vector <int> order;
    dbg (node);
    for (int son : gr[node])
        order = join (order, dfs (son));
    pushFront (order, node);
    return order;
}

int main() {
    freopen ("purification.in", "r", stdin);
    freopen ("purification.out", "w", stdout);

    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> w[i];
    int root = 0;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x; x++;
        gr[x].pb (i);
    }
    vector <int> order = dfs (root);
    int ans = 0;
    for (int i = 0; i < order.size (); i++)
        ans += i * w[order[i]];
    cout << ans << "\n";
    return 0;
}
