#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair <int, int>;

void fastios() {
    freopen("rmq.in", "r", stdin);
    freopen("rmq.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
}

const int maxn = 1e5, maxk = 20;

int a[1 + maxn], rmq[maxk][1 + maxn], lg[1 + maxn];
int N, M;

void buildRmq() {
    for (int i = 1; i <= N; i++) {
        rmq[0][i] = a[i];
    }
    lg[1] = 0;
    for (int i = 2; i <= N; i++)
        lg[i] = lg[i / 2] + 1;
    for (int k = 1; k < maxk; k++)
        for (int i = 1; i <= N; i++)
            rmq[k][i] = min(rmq[k - 1][i], rmq[k - 1][min(N, i + (1 << (k - 1)))]);
}

int getRmq(int l, int r) {
    int k = lg[r - l + 1];
    return min(rmq[k][l], rmq[k][r - (1 << k) + 1]);
}

int main() {
    fastios();

    cin >> N >> M;
    for (int i = 1; i <= N; i++)
        cin >> a[i];
    buildRmq();
    for (int i = 1; i <= M; i++) {
        int l, r;
        cin >> l >> r;
        cout << getRmq(l, r) << "\n";
    }
    return 0;
}
