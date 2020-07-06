#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
#define pb push_back
#define dbg(x) cerr << #x << " " << "\n"
 
/**
-   we want to find to disjoint subsets of indices X (|X| = M) and Y (|Y| = S) so that sum{a[i]|i belongs to X} + sum{b[i]|i belongs to Y}
-   it's easy to prove that if we sort the indices by b[i] - a[i] we will not use a a[i] and b[j] with i > j
-   now we can see the best solution for a on prefix and the best solution for b on suffix and combine them
**/
 
const int N = 3e5;
 
int a[1 + N], b[1 + N];
int order[1 + N];
 
bool cmp (int x, int y) {
    return b[x] - a[x] < b[y] - a[y];
}
 
ll pref[1 + N], suff[1 + N + 1];
 
int main () {
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);
 
    int n, M, S;
    cin >> n >> M >> S;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
        order[i] = i;
    }
    sort (order + 1, order + n + 1, cmp);
 
    /// make pref
    ll sum = 0;
    priority_queue <int> pq;
    if (M == 0)
        pref[0] = 0;
    else
        pref[0] = -1;
    for (int i = 1; i <= n; i++) {
        int index = order[i];
        pq.push (-a[index]);
        sum += a[index];
        if (pq.size () > M) {
            sum += pq.top ();
            pq.pop ();
        }
        if (pq.size () == M)
            pref[i] = sum;
        else
            pref[i] = -1;
    }
    /// make suff
    while (pq.size ()) pq.pop ();
    sum = 0;
    if (S == 0)
        suff[n + 1] = 0;
    else
        suff[n + 1] = -1;
    for (int i = n; i > 0; i--) {
        int index = order[i];
        pq.push (-b[index]);
        sum += b[index];
        if (pq.size () > S) {
            sum += pq.top ();
            pq.pop ();
        }
        if (pq.size () == S)
            suff[i] = sum;
        else
            suff[i] = -1;
    }
    ll ans = 0;
    for (int i = 0; i <= n; i++)
        if (pref[i] != -1 && suff[i + 1] != -1)
            ans = max (ans, pref[i] + suff[i + 1]);
    cout << ans << "\n";
    return 0;
}
