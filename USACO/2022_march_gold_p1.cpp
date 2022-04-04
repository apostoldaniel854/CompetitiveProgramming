#include <bits/stdc++.h>

using namespace std;

const int COW = 1, APPLE = 2;

struct Update {
    int x;
    int y;
    int type;
    int cnt;
    bool operator < (const Update &other) const {
        if (x != other.x)
            return x < other.x;
        if (type != other.type)
            return type < other.type;
        return y < other.y;
    }
};

vector <Update> updates;
multiset <pair <int, int>> activecows;

int ans;

void pairUp(int rem, int y) {
    auto it = activecows.lower_bound({y + 1, 0});
    if (it == activecows.begin())
        return;
    it = prev(it);
    int take = min(it->second, rem);
    pair <int, int> value = *it;
    activecows.erase(it);
    ans += take;
    rem -= take;
    value.second -= take;
    if (value.second > 0)
        activecows.insert(value);
    if (rem == 0)
        return;
    pairUp(rem, y);
}

int main() {
    int N;
    cin >> N;
    for (int i = 1; i <= N; i++) {
        int type, x, y, cnt;
        cin >> type >> x >> y >> cnt;
        int newx = x + y;
        int newy = x - y;
        x = newx;
        y = newy;
        updates.push_back({x, y, type, cnt});
    }
    sort(updates.begin(), updates.end());
    for (Update u : updates) {
        if (u.type == COW) {
            activecows.insert({u.y, u.cnt});
        }
        else {
            int rem = u.cnt;
            pairUp(rem, u.y);
        }
    }
    cout << ans << "\n";
    return 0;
}
