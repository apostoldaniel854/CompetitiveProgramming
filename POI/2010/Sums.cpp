#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define pb push_back
#define dbg(x) cerr << #x << " " << x << "\n"

/**
-   We are given and array A and want to find for k values x if x can be written as a sum of
    numbers from A where each number can be used more than one
-   Observation: If we can get sum s than we can also get s + a[1] * t, t positive
-   => we want to find the first value which we can get with remainder r modulo a[1]
-   we use bfs to solve this problem
**/

const int N = 5000, MX = 5e4;
const int INF = 1e9;
int minValue[1 + MX];
int a[1 + N];


int main() {
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    sort (a + 1, a + n + 1);
    for (int i = 0; i < a[1]; i++)
        minValue[i] = INF;
    minValue[0] = 0;
    queue <pair <int, int>> pq;
    pq.push ({0, 0});
    while (pq.size ()) {
        pair <int, int> node = pq.front ();
        pq.pop ();
        if (minValue[node.second] != node.first)
            continue;
        for (int i = 2; i <= n; i++) {
            int newNode = (node.second + a[i]) % a[1];
            if (minValue[newNode] > minValue[node.second] + a[i]) {
                minValue[newNode] = minValue[node.second] + a[i];
                pq.push ({minValue[newNode], newNode});
            }
        }
    }
    int k;
    cin >> k;
    while (k--) {
        int x;
        cin >> x;
        if (minValue[x % a[1]] <= x)
            cout << "TAK\n";
        else
            cout << "NIE\n";
    }

    return 0;
}
