#include <bits/stdc++.h>
#include "friend.h"
 
using namespace std;
 
using ll = long long;
#define pb push_back
#define dbg(x) cerr << #x << " " << x << "\n"
 
 
/**
 
**/
 
const int N = 1e5;
int c[1 + N], d[1 + N];
 
int findSample (int n, int confidence[], int host[], int protocol[]) {
    for (int i = 0; i < n; i++) {
        c[i] = confidence[i];
        d[i] = 0;
    }
    for (int i = n - 1; i > 0; i--) {
        if (protocol[i] == 0) {
            c[host[i]] += d[i];
            d[host[i]] += max (c[i], d[i]);
        }
        if (protocol[i] == 1) {
            c[host[i]] = max (c[host[i]] + c[i], max(c[host[i]] + d[i], d[host[i]] + c[i]));
            d[host[i]] += d[i];
        }
        if (protocol[i] == 2) {
            c[host[i]] = max(c[host[i]] + d[i], d[host[i]] + c[i]);
            d[host[i]] += d[i];
        }
    }
    return max (c[0], d[0]);
}
/**
int main () {
    return 0;
}
**/
