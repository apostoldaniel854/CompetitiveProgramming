#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define pb push_back
#define dbg(x) cerr << #x << " " << x << "\n"

/**
->  first find all peaks using dfs
->  than we procces peaks in descending order and merge them together with their
    neighbors keeping the best height and the peaks that stil need to get assigned an answer
-> we merge by size because we have the vector inSet
**/

const int N = 2000, MX = 1e5;
int place[1 + N][1 + N];
bool viz[1 + N][1 + N];
bool used[1 + MX];
bool isPeak[1 + MX];
int h[1 + MX];
int sz[1 + MX];
int comp, n, m;
int e[1 + N][1 + N];
int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dy[] = {-1, 1, 0, 1, -1, 1, 0, -1};
int ans[1 + MX];
vector <int> inSet[1 + MX];
bool inside (int x, int y) {
    return 1 <= x && x <= n && 1 <= y && y <= m;
}

bool dfs (int x, int y) {
    place[x][y] = comp;
    viz[x][y] = true;
    bool peak = true;
    for (int dir = 0; dir < 8; dir++) {
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        if (inside (nx, ny)) {
            if (e[nx][ny] > e[x][y])
                peak = false;
            else if(e[nx][ny] == e[x][y] && not viz[nx][ny])
                peak &= dfs (nx, ny);
        }
    }
    return peak;
}

int f[1 + MX], best[1 + MX];

void use (pair <int, int> coord) {
    int x = coord.first;
    int y = coord.second;
    int index = place[x][y];
    f[index] = index;
    sz[index] = 1;
    used[index] = true;
    if (isPeak[index])
        best[index] = h[index], inSet[index].pb (index);
    else
        best[index] = -1;
}

int ft (int x) {
    return f[x] == x ? x : (f[x] = ft (f[x]));
}


void unite (int x, int y, int height) {
    x = ft (x);
    y = ft (y);
    if (x == y) return;
    if (sz[x] < sz[y])
        swap (x, y);
    sz[x] += sz[y];
    f[y] = x;
    if (best[y] == -1) return;
    if (best[x] == -1) {
        inSet[x] = inSet[y];
        best[x] = best[y];
        return;
    }
    if (best[x] > best[y])
        for (int ind : inSet[y])
            ans[ind] = height;
    else if (best[x] < best[y]) {
        for (int ind : inSet[x])
            ans[ind] = height;
        best[x] = best[y];
        inSet[x] = inSet[y];
    }
    else
        for (int ind : inSet[y])
            inSet[x].pb (ind);
}

int main() {
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> e[i][j];

    comp = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (not viz[i][j]) {
                comp++;
                h[comp] = e[i][j];
                isPeak[comp] = dfs (i, j);
            }

    vector <pair <int, pair <int, int>>> order;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            order.pb ({-e[i][j], {i, j}});
    sort (order.begin (), order.end ());

    int index = 0;
    for (auto coord : order) {
        int x = coord.second.first;
        int y = coord.second.second;
        if (not used[place[x][y]]) {
            int j = index;
            while (j < order.size () && order[index].first == order[j].first) {
                use (order[j].second);
                j++;
            }
        }
        for (int dir = 0; dir < 8; dir++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            if (inside (nx, ny) && used[place[nx][ny]])
                unite (place[x][y], place[nx][ny], -coord.first);
        }
        index++;
    }

    vector <pair <int, int>> afis;
    for (int i = 1; i <= comp; i++)
        if (isPeak[i])
            afis.pb ({h[i], ans[i]});
    sort (afis.begin (), afis.end ());
    reverse (afis.begin (), afis.end ());
    cout << afis.size () << "\n";
    for (auto it : afis)
        cout << it.first << " " << it.second << "\n";

    return 0;
}
