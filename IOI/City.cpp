#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9;
const int MAX_N = 1e5;
 
using ll = long long;
set <int> gr[1 + MAX_N];
int sz[1 + MAX_N];
 
void clean(int n) {
    for (int i = 1; i <= n; i++)
        gr[i].clear(), sz[i] = 0;
}
 
void dfs_cnt(int node, int par, int &ans, int total_sz) {
    for (int son : gr[node])
        if (son != par) {
            dfs_cnt(son, node, ans, total_sz);
            sz[node] += sz[son];
        }
    ans += 1ll * sz[node] * (total_sz - sz[node]) % MOD;
    ans %= MOD;
}
 
int solve(vector <pair <pair <int, int>, int>> v) {
    int n = v.size();
    sort(v.begin(), v.end());
    int tag = 0;
    for (int i = 0; i < n; i++) {
        if (i > 0 && v[i].first.first == v[i - 1].first.first && v[i].first.second == v[i - 1].first.second + 1)
            v[i].second = tag;
        else
            v[i].second = ++tag;
        sz[tag]++;
    }
    for (int i = 0; i < n; i++)
        swap(v[i].first.first, v[i].first.second);
    sort(v.begin(), v.end());
    for (int i = 0; i < n; i++) {
        if (i > 0 && v[i].first.first == v[i - 1].first.first && v[i].first.second == v[i - 1].first.second + 1) {
            int x = v[i].second, y = v[i - 1].second;
            gr[x].insert(y);
            gr[y].insert(x);
        }
    }
    int ans = 0;
    dfs_cnt(1, 0, ans, n);
    clean(n);
    return ans;
}
 
int DistanceSum(int N, int *X, int *Y) {
    vector <pair <pair <int, int>, int>> v;
    for (int i = 0; i < N; i++)
        v.push_back({{X[i], Y[i]}, 0});
    int ans = 0;
    ans += solve(v);
    for (int i = 0; i < N; i++)
        swap(v[i].first.first, v[i].first.second);
    ans += solve(v);
    return ans % MOD;
}
