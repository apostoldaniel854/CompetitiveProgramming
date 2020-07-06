#include <bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
#define pb push_back
#define dbg(x) cerr << #x << " " << x << "\n"
 
/**
-   We are given some words. We need to rearrange letters in each word
    so that the trie formed has a minimum number of nodes
-   N small => we can use bitmasks
-   dp[mask] = min (dp[submask1] + dp[submask2] - CommonPref) where submask1 | submask2 = mask and submask1 & submask2 = 0
-   it's easy to find the lcp, for each letter find the min count of it in the subset
**/
const int INF = 1e9;
const int N = 16, SIGMA = 26;
int dp[1 << N];
int cnt[N][SIGMA];
int n;
int getLcp (int mask) {
    int ans = 0;
    for (char ch = 'a'; ch <= 'z'; ch++) {
        int best = INF;
        for (int i = 0; i < n; i++)
            if (mask & (1 << i))
                best = min (best, cnt[i][ch - 'a']);
        ans += best;
    }
    return ans;
}
 
int main () {
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);
 
    cin >> n;
    for (int i = 0; i < n; i++) {
        string str;
        cin >> str;
        for (char ch : str)
            cnt[i][ch - 'a']++;
    }
    for (int mask = 1; mask < (1 << n); mask++) {
        int lcp = getLcp (mask);
        if (__builtin_popcount (mask) == 1)
            dp[mask] = lcp;
        else {
            dp[mask] = INF;
            for (int submask = mask & (mask - 1); submask > 0; submask = (submask - 1) & mask)
               dp[mask] = min (dp[mask], dp[submask] + dp[mask ^ submask] - lcp);
        }
    }
 
    cout << dp[(1 << n) - 1] + 1 << "\n"; /// there's a fictive node
 
    return 0;
}
