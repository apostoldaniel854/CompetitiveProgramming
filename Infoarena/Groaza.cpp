#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
#define pb push_back
#define dbg(x) cerr << #x << " " << x << "\n"
 
vector <pair <int, int>> edges;
 
int main () {
    freopen ("groaza.in", "r", stdin);
    freopen ("groaza.out", "w", stdout);
 
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);
 
    int n, m;
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        m--;
        edges.pb ({i, i + 1});
    }
    int l = 2;
    int cur = 3;
    while (m) {
        m--;
        edges.pb ({cur, cur - l});
        l++;
        if (cur == l) {
            cur++, l = 2;
        }
    }
 
    for (pair <int, int> edge : edges)
        cout << edge.first << " " << edge.second << "\n";
 
    return 0;
}
