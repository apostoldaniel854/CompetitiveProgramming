#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair <int, int>;

void fastios() {
    freopen("cautbin.in", "r", stdin);
    freopen("cautbin.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
}

const int maxn = 1e5;
int a[1 + maxn];
int N, M;

int bsearch(int val) {
    int best = 0, lb = 1, rb = N;
    while (lb <= rb) {
        int mid = (lb + rb) / 2;
        if (a[mid] <= val)
            best = mid, lb = mid + 1;
        else
            rb = mid - 1;
    }
    return best;
}


int main() {
    fastios();

    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> a[i];
    cin >> M;
    for (int i = 1; i <= M; i++) {
        int type, x;
        cin >> type >> x;
        if (type == 0) {
            int pos = bsearch(x);
            if (a[pos] != x)
                cout << "-1\n";
            else
                cout << pos << "\n";
        }
        else if (type == 1)
            cout << bsearch(x) << "\n";
        else
            cout << bsearch(x - 1) + 1 << "\n";
    }
    return 0;
}
