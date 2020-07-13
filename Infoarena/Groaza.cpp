#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
#define pb push_back
#define dbg(x) cerr << #x << " " << x << "\n"
/**
- It's easy to see that the best configuration is a chain,
  so first we add the edges 1 - 2, 2 - 3, 3 - 4, (n-1) - n
- Now we need to add the remaining m - n + 1 edges
- We want the edge to end as far away as possible from n
=> we start to add in order all edges that end in 3..n that aren't part of the chain till we don't have any edge left
 of course the edges that end in i will be added in order from the one that has the least length in the chain to the greatest length
 (ex: for i = 5 we add in order 4 - 5, 3 - 5, 2 - 5 if we still have edges)
**/
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
