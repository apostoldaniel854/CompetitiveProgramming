#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define dbg(x) cerr << #x << " " << x << "\n"

const int RAD = 500;
const int MAX_N = 2e5;

int H[1 + MAX_N];
vector <int> gr[1 + MAX_N];
vector <int> order[1 + MAX_N];
vector <int> v[1 + MAX_N];
int L[1 + MAX_N], R[1 + MAX_N];
int id[1 + MAX_N];
int sol[RAD][1 + MAX_N];
int freq[1 + MAX_N];


void dfs(int node, int cnt, int color) {
    if (H[node] == color)
        cnt++;
    else
        sol[id[color]][H[node]] += cnt;
    for (int son : gr[node])
        dfs(son, cnt, color);
}
int mom;
void prec(int node) {
    L[node] = ++mom;
    order[H[node]].push_back(mom);
    for (int son : gr[node])
        prec(son);
    R[node] = mom;
}
int get(int lb, int rb, int color) {
    return upper_bound(order[color].begin(), order[color].end(), rb) - lower_bound(order[color].begin(), order[color].end(), lb);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int N, RR, Q;
    cin >> N >> RR >> Q;
    for (int i = 1; i <= N; i++) {
        if (i == 1)
            cin >> H[i];
        else {
            int par;
            cin >> par >> H[i];
            gr[par].push_back(i);
        }
    }
    for (int i = 1; i <= N; i++) {
        freq[H[i]]++;
        v[H[i]].push_back(i);
    }
    int nr = 0;
    for (int i = 1; i <= RR; i++) {
        if (freq[i] > RAD) {
            id[i] = ++nr;
            dfs(1, 0, i);
        }
    }
    prec(1);
    while (Q--) {
        int a, b;
        cin >> a >> b;
        if (freq[a] > RAD)
            cout << sol[id[a]][b] << endl;
        else {
            int ans = 0;
            for (int node : v[a])
                ans += get(L[node], R[node], b);
            cout << ans << endl;
        }
    }
    return 0;
}
