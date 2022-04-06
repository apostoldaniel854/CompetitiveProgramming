#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair <int, int>;

void fastios() {
    freopen("sortaret.in", "r", stdin);
    freopen("sortaret.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
}

const int maxn = 5e4;

vector <int> gr[1 + maxn];
int deg[1 + maxn];

int main() {
    fastios();
    int N, M;
    cin >> N >> M;
    for (int i = 1; i <= M; i++) {
        int x, y;
        cin >> x >> y;
        deg[y]++;
        gr[x].push_back(y);
    }
    vector <int> topo;
    queue <int> q;
    for (int i = 1; i <= N; i++)
        if (deg[i] == 0)
            q.push(i);
    while (q.size()) {
        int node = q.front();
        q.pop();
        topo.push_back(node);
        for (int vec : gr[node]) {
            deg[vec]--;
            if (deg[vec] == 0)
                q.push(vec);
        }
    }
    for (int x : topo)
        cout << x << " ";
    cout << "\n";
    return 0;
}
