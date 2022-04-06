#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair <int, int>;

void fastios() {
    freopen("strmatch.in", "r", stdin);
    freopen("strmatch.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
}

const int mod = 214233221, base = 31, maxn = 2e6;

int sumhash[1 + maxn], power[1 + maxn];
string A, B;

void add(int &a, int b) {
    a += b;
    if (a >= mod)
        a -= mod;
}
int mult(int a, int b) {
    return 1ll * a * b % mod;
}

void precHash(string s) {
    int sz = s.size();
    power[0] = 1;
    for (int i = 0; i < sz; i++) {
        power[i + 1] = 1ll * power[i] * base % mod;
        sumhash[i + 1] = (sumhash[i] + 1ll * power[i + 1] * (s[i] - 'A' + 1)) % mod;
    }
}

int getHash(string s) {
    int sz = s.size();
    int hsh = 0;
    for (int i = 0; i < sz; i++)
        hsh = (hsh + 1ll * power[i + 1] * (s[i] - 'A' + 1)) % mod;
    return hsh;
}

int queryHash(int lb, int rb) {
    return (sumhash[rb + 1] - sumhash[lb] + mod) % mod;
}

int main() {
    fastios();
    cin >> A >> B;
    precHash(B);
    int hashA = getHash(A);
    int na = A.size(), nb = B.size();
    vector <int> sol;
    for (int i = 0; i + na <= nb; i++) {
        int hsh = queryHash(i, i + na - 1);
        if (hsh == 1ll * hashA * power[i] % mod)
            sol.push_back(i);
    }
    cout << sol.size() << "\n";
    for (int x : sol)
        cout << x << ' ';
    cout << "\n";
    return 0;
}
