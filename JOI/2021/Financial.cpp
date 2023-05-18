#include <bits/stdc++.h>

using namespace std;

struct node_info {
    int mx;
    node_info(int value = 0) {
        this->mx = value;
    }
    node_info operator + (node_info other) const {
        node_info RES;
        RES.mx = max(mx, other.mx);
        return RES;
    }
};

class SegTree {
private:
    vector <node_info> seg;
    int n;
public:
    SegTree(int n) {
        seg.resize(1 + 4 * n);
        this->n = n;
    }
    void update_pos(int node, int lb, int rb, int pos, node_info val) {
        if (lb == rb) {
            seg[node] = val;
            return;
        }
        int mid = (lb + rb) / 2, lnode = node * 2, rnode = node * 2 + 1;
        if (pos <= mid)
            update_pos(lnode, lb, mid, pos, val);
        else
            update_pos(rnode, mid + 1, rb, pos, val);
        seg[node] = seg[lnode] + seg[rnode];
    }
    void update_pos(int pos, node_info val) {
        update_pos(1, 1, n, pos, val);
    }
    node_info query_range(int node, int lb, int rb, int ql, int qr) {
        if (lb == ql && rb == qr)
            return seg[node];
        int mid = (lb + rb) / 2, lnode = node * 2, rnode = node * 2 + 1;
        if (ql <= mid && qr <= mid)
            return query_range(lnode, lb, mid, ql, qr);
        else if (mid + 1 <= ql && mid + 1 <= qr)
            return query_range(rnode, mid + 1, rb, ql, qr);
        else
            return query_range(lnode, lb, mid, ql, mid) + query_range(rnode, mid + 1, rb, mid + 1, qr);
    }
    node_info query_range(int ql, int qr) {
        if (ql > qr)
            return node_info();
        return query_range(1, 1, n, ql, qr);
    }
};

const int MAX_N = 3e5;

int a[1 + MAX_N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n, D;
    cin >> n >> D;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    vector <int> order(n);
    iota(order.begin(), order.end(), 1);
    sort(order.begin(), order.end(), [&](int x, int y) {
        if (a[x] != a[y])
            return a[x] < a[y];
        return x > y;
    });

    set <int> stk;
    stk.insert(0);
    stk.insert(n + 1);
    SegTree dp(n);
    set <int> blocked;
    for (int i = 1; i <= n - D; i++)
        blocked.insert(i);
    for (int i : order) {
        auto it = stk.lower_bound(i);
        int nxt = *it, prv = *prev(it);
        if (nxt - prv > D) {
            if (nxt - i <= D) {
                for (int j = i; j <= nxt; j++)
                    blocked.erase(j);
            }
            if (i - prv <= D)
                for (int j = prv; j <= i; j++)
                    blocked.erase(j);
        }

        it = blocked.lower_bound(i);
        int bound;
        if (it == blocked.begin())
            bound = 1;
        else
            bound = *prev(it);
        int best = dp.query_range(bound, i).mx;
        dp.update_pos(i, node_info(best + 1));
        stk.insert(i);
    }
    cout << dp.query_range(1, 1, n, 1, n).mx << "\n";

    return 0;
}
