#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
#define pb push_back
#define dbg(x) cerr << #x << " " << x << "\n"
 
/**
->  We use a simple tree dp:
    dp[node][size][0/1] = the minimum time it takes to visit size nodes in the subtree of node if we start in node
    0 -> we don't visit all
    1 -> we visit all
**/
 
const int N = 10000;
vector <pair <int, int>> gr[1 + N];
 
int dp[1 + N][1 + N][2];
int sz[1 + N];
 
void _ (int &a, int b) {
    if (a > b)
        a = b;
}
 
void dfs (int node, int par) {
    sz[node] = 1;
    dp[node][1][0] = dp[node][1][1] = 0;
    for (pair <int, int> edge : gr[node]) {
        int son = edge.first;
        int cost = edge.second;
        if (par != son) {
            dfs (son, node);
            for (int cur = sz[node]; cur >= 0; cur--)
                for (int add = sz[son]; add > 0; add--) {
                    _ (dp[node][cur + add][0], dp[node][cur][0] + dp[son][add][0] + 2 * cost);
                    _ (dp[node][cur + add][1], dp[node][cur][0] + dp[son][add][1] + cost);
                    _ (dp[node][cur + add][1], dp[node][cur][1] + dp[son][add][0] + 2 * cost);
                }
            sz[node] += sz[son];
        }
    }
}
 
int main() {
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);
 
    int n, k, x;
    cin >> n >> k >> x;
    for (int i = 1; i < n; i++) {
        int x, y, c;
        cin >> x >> y >> c;
        gr[x].pb ({y, c});
        gr[y].pb ({x, c});
    }
 
    for (int node = 1; node <= n; node++)
        for (int i = 1; i <= n; i++)
            dp[node][i][0] = dp[node][i][1] = (1 << 29);
 
    dfs (x, 0);
    cout << dp[x][k][1] << "\n";
 
    return 0;
}
