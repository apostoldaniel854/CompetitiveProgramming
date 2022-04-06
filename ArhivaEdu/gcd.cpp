#include <bits/stdc++.h>

using namespace std;



void fastios() {
    freopen("euclid2.in", "r", stdin);
    freopen("euclid2.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
}

int gcd(int a, int b) {
    while (b > 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

void solveTest() {
    int a, b;
    cin >> a >> b;
    cout << gcd(a, b) << "\n";
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
