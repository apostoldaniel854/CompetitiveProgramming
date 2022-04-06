#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair <int, int>;

void fastios() {
    freopen("euclid3.in", "r", stdin);
    freopen("euclid3.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
}

int extendedGcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = extendedGcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return d;
}

void solveTest() {
    int a, b, c;
    cin >> a >> b >> c;
    int x, y;
    int d = extendedGcd(a, b, x, y);
    if (c % d == 0) {
        x *= (c / d);
        y *= (c / d);
    }
    else {
        x = y = 0;
    }
    cout << x << " " << y << "\n";
}

int main()
{
    fastios();
    int T;
    cin >> T;
    for (int test = 1; test <= T; test++)
        solveTest();
    return 0;
}
