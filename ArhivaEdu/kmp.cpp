#include <bits/stdc++.h>
 
using namespace std;
 
vector <int> matches (string s, int target) {
    vector <int> pi (s.size ());
    pi[0] = 0;
    vector <int> sol;
    for (int i = 1; i < s.size (); i++) {
        int cur = pi[i - 1];
        while (cur && s[i] != s[cur])
            cur = pi[cur - 1];
        if (s[i] == s[cur])
            cur++;
        pi[i] = cur;
        if (pi[i] == target)
            sol.push_back (i - 2 * target);
    }
    return sol;
}
 
int main () {
    freopen ("strmatch.in", "r", stdin);
    freopen ("strmatch.out", "w", stdout);
 
    string a, b;
    cin >> a >> b;
    string c = a + "#" + b;
    vector <int> sol = matches (c, a.size ());
    cout << sol.size () << "\n";
    if (sol.size () > 1000)
        sol.resize (1000);
    for (int x : sol)
        cout << x << " ";
    cout << "\n";
    return 0;
}
