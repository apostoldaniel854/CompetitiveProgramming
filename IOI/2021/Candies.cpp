#include "candies.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define dbg(x) cerr << #x << " " << x << "\n

struct node_info {
    ll sum;
    ll sum_max;
    ll sum_min;
};

class SegTree {
private:
    vector <node_info> seg;
    node_info join(node_info L, node_info R) {
        node_info RES;
        RES.sum = L.sum + R.sum;
        RES.sum_max = max(L.sum_max, R.sum_max + L.sum);
        RES.sum_min = min(L.sum_min, R.sum_min + L.sum);
        return RES;
    }
public:
    SegTree(int n) {
        seg.resize(1 + 4 * n);
    }
    void update_pos(int node, int lb, int rb, int pos, int val) {
        if (lb == rb) {
            seg[node].sum_max = max(0, val);
            seg[node].sum_min = min(0, val);
            seg[node].sum = val;
            return;
        }
        int mid = (lb + rb) / 2, lnode = node * 2, rnode = node * 2 + 1;
        if (pos <= mid)
            update_pos(lnode, lb, mid, pos, val);
        else
            update_pos(rnode, mid + 1, rb, pos, val);
        seg[node] = join(seg[lnode], seg[rnode]);
    }
    ll go(int node, int lb, int rb, ll cap) {
        if (lb == rb)
            return min(max(seg[node].sum, 0ll), cap);
        int mid = (lb + rb) / 2, lnode = node * 2, rnode = node * 2 + 1;
        if (seg[rnode].sum_max - seg[rnode].sum_min > cap)
            return go(rnode, mid + 1, rb, cap);
        ll value = go(lnode, lb, mid, cap);
        if (value + seg[rnode].sum_max > cap)
            return cap - (seg[rnode].sum_max - seg[rnode].sum);
        if (value + seg[rnode].sum_min < 0)
            return seg[rnode].sum - seg[rnode].sum_min;
        return value + seg[rnode].sum;
    }
};

std::vector<int> distribute_candies(std::vector<int> c, std::vector<int> l,
                                    std::vector<int> r, std::vector<int> v) {
    int n = c.size(), q = v.size();
    vector <vector <int>> L(n), R(n);
    for (int i = 0; i < q; i++) {
        L[l[i]].push_back(i + 1);
        if (r[i] + 1 < n)
            R[r[i] + 1].push_back(i + 1);
    }
    SegTree DS_time(q);
    std::vector<int> s(n);
    for (int i = 0; i < n; i++) {
        for (int id : L[i]) {
            /// activate id
            DS_time.update_pos(1, 1, q, id, v[id - 1]);
        }
        for (int id : R[i]) {
            /// deactivate id
            DS_time.update_pos(1, 1, q, id, 0);
        }
        s[i] = DS_time.go(1, 1, q, c[i]);
    }
    return s;
}
/**
3
10 15 13
2
0 2 20
0 1 -11

**/
