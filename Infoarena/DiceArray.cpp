#include <bits/stdc++.h>

using namespace std;
/**
Use lazy to solve problem because 2 rotations cam be combined in a nice way
**/
void fastios() {
    freopen("dicearray.in", "r", stdin);
    freopen("dicearray.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
}

const int maxn = 7e4;


struct Dice {
    int axes[4];
};
Dice lazy[1 + 4 * maxn], seg[1 + 4 * maxn];
Dice vanilla;
Dice v[1 + maxn];


bool same(Dice &a, Dice &b) {
    for (int i = 1; i <= 3; i++)
        if (a.axes[i] != b.axes[i])
            return false;
    return true;
}

int sgn(int x) {
    if (x < 0)
        return -1;
    return 1;
}
int N;
Dice res;
void updateNode(Dice &from, Dice &toadd) {
    for (int i = 1; i <= 3; i++)
        res.axes[i] = from.axes[abs(toadd.axes[i])] * sgn(toadd.axes[i]);
    from = res;
}

void push(int node) {
    if (not same(lazy[node], vanilla)) {
        int lnode = node * 2, rnode = node * 2 + 1;
        if (lnode <= 4 * maxn) {
            updateNode(seg[lnode], lazy[node]);
            updateNode(seg[rnode], lazy[node]);
            updateNode(lazy[lnode], lazy[node]);
            updateNode(lazy[rnode], lazy[node]);

        }
        lazy[node] = vanilla;
    }
}

void updateRange(int node, int lb, int rb, int ql ,int qr, Dice &val) {
    push(node);
    if (ql <= lb && rb <= qr) {
        updateNode(seg[node], val);
        updateNode(lazy[node], val);
        return;
    }
    int mid = (lb + rb) / 2, lnode = node * 2, rnode = node * 2 + 1;
    if (ql <= mid)
        updateRange(lnode, lb, mid, ql, qr, val);
    if (qr > mid)
        updateRange(rnode, mid + 1, rb, ql, qr, val);
}

int ans;

void solve(int node, int lb, int rb) {
    push(node);
    if (lb == rb) {
        int val = seg[node].axes[1];
        if (val > 0)
            ans += v[lb].axes[val];
        else
            ans += 7 - v[lb].axes[-val];
        return;
    }
    int mid = (lb + rb) / 2, lnode = node * 2, rnode = node * 2 + 1;
    solve(lnode, lb, mid);
    solve(rnode, mid + 1, rb);
}

int main() {
    fastios();
    for (int i = 1; i <= 3; i++)
        vanilla.axes[i] = i;
    for (int i = 1; i <= 4 * maxn; i++)
        seg[i] = lazy[i] = vanilla;
    int Q;
    cin >> N >> Q;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= 3; j++)
            cin >> v[i].axes[j];
    }
    while (Q--) {
        char type; int l, r;
        cin >> l >> r >> type;
        Dice d;
        if (type == 'x') {
            d.axes[1] = -3;
            d.axes[2] = 2;
            d.axes[3] = 1;
        }
        else if (type == 'y') {
            d.axes[1] = 1;
            d.axes[2] = 3;
            d.axes[3] = -2;
        }
        else {
            d.axes[1] = 2;
            d.axes[2] = -1;
            d.axes[3] = 3;
        }
        updateRange(1, 1, N, l, r, d);
    }
    solve(1, 1, N);
    cout << ans << "\n";
    return 0;
}
