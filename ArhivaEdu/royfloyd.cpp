#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair <int, int>;

void fastios() {
    freopen("royfloyd.in", "r", stdin);
    freopen("royfloyd.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
}

const int maxn = 100;

int a[1 + maxn][1 + maxn];

int main() {
    fastios();
    int N;
    cin >> N;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            cin >> a[i][j];
    for (int k = 1; k <= N; k++)
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                if (i != j && j != k && i != k) {
                    if (a[i][k] > 0 && a[k][j] > 0 && (a[i][j] == 0 || a[i][j] > a[i][k] + a[k][j]))
                        a[i][j] = a[i][k] + a[k][j];
                }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++)
            cout << a[i][j] << " ";
        cout << "\n";
    }
    return 0;
}
