#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define pb push_back
#define dbg(x) cerr << #x << " " << x << "\n"

/**
-   we see that the length of interval shouldn't be larger than 2
=> We compute the lca for all adjacent elements and also single elements
=> For every lca we keep in a set the position that it occurs and query to see if there is one in [l, r]
**/

const int N = 2e5, LG = 20;
int p[LG][1 + N];
int d[1 + N], a[1 + N];
vector <int> gr[1 + N];

int n, m, q;

void dfs (int node, int par) {
    d[node] = d[par] + 1;
    p[0][node] = par;
    for (int son : gr[node])
        if (par != son)
            dfs (son, node);
}

void lift () {
    for (int k = 1; k < LG; k++)
        for (int node = 1; node <= n; node++)
            p[k][node] = p[k - 1][p[k - 1][node]];
}

int lca (int a, int b) {
    int k;
    k = LG - 1;
    while (d[a] > d[b]) {
        if (d[p[k][a]] >= d[b])
            a = p[k][a];
        k--;
    }
    k = LG - 1;
    while (d[a] < d[b]) {
        if (d[p[k][b]] >= d[a])
            b = p[k][b];
        k--;
    }
    k = LG - 1;
    while (k >= 0) {
        if (p[k][a] != p[k][b])
            a = p[k][a], b = p[k][b];
        k--;
    }
    if (a != b)
        a = p[0][a];
    return a;
}

multiset <int> simple[1 + N];
multiset <int> two[1 + N];

int main () {
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);

    cin >> n >> m >> q;
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        gr[x].pb (y);
        gr[y].pb (x);
    }

    dfs (1, 0);
    lift ();

    for (int i = 1; i <= m; i++) {
        cin >> a[i];
        simple[a[i]].insert (i);
    }
    for (int i = 1; i < m; i++)
        two[lca (a[i], a[i + 1])].insert (i);
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int pos, value;
            cin >> pos >> value;
            simple[a[pos]].erase (pos);
            if (pos > 1)
                two[lca (a[pos], a[pos - 1])].erase (pos - 1);
            if (pos < m)
                two[lca (a[pos], a[pos + 1])].erase (pos);

            a[pos] = value;
            simple[a[pos]].insert (pos);
            if (pos > 1)
                two[lca (a[pos], a[pos - 1])].insert (pos - 1);
            if (pos < m)
                two[lca (a[pos], a[pos + 1])].insert (pos);
        }
        else {
            int l, r, value;
            cin >> l >> r >> value;
            auto it = simple[value].lower_bound (l);
            if (it != simple[value].end () && *it <= r)
                cout << *it << " " << *it << "\n";
            else {
                it = two[value].lower_bound (l);
                if (it != two[value].end () && *it < r)
                    cout << *it << " " << *it + 1 << "\n";
                else
                    cout << "-1 -1\n";
            }
        }
    }
    return 0;
}
/**
5 4 4
1 2
3 1
3 4
5 3
4 5 2 3
2 1 3 1
1 3 5
2 3 4 5
2 1 3 1
**/
