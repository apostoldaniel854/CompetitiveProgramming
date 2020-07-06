#include <bits/stdc++.h>
#include <robots.h>
using namespace std;
 
using ll = long long;
#define pb push_back
#define dbg(x) cerr << #x << " " << x << "\n"
 
/**
-   There are a robots that can only be assigned toys that weight less than x[i] and b robots can only be assigned toys of size less than y[i]
    Knowing the weight and size of toys find a ways to assign toys to the robots so that the maximum number of toys assigned to a robot is minimum
-   It's easy to see that we can binary search the number
-   We use greedy to assign weak robots so that the remaining toys are of sizes as small as possible
    than check if we can assign small robots to the remaining toys
**/
 
const int NA = 5e4, NT = 1e6;
 
int a, b, t;
int x[1 + NA], y[1 + NA];
pair <int, int> toy[1 + NT];
bool used[1 + NT];
int orderSmall[1 + NT], orderWeak[1 + NT];
 
bool check (int bound) {
    for (int i = 1; i <= t; i++)
        used[i] = false;
    priority_queue <pair <int, int>> pq;
    int j = 1;
    for (int i = 1; i <= a; i++) {
        while (j <= t && x[i] > toy[orderWeak[j]].first) {
            pq.push ({toy[orderWeak[j]].second, orderWeak[j]});
            j++;
        }
        int lft = bound;
        while (lft && pq.size ()) {
            used[pq.top ().second] = true;
            pq.pop ();
            lft--;
        }
    }
    queue <int> q;
    j = 1;
    for (int i = 1; i <= b; i++) {
        while (j <= t && y[i] > toy[orderSmall[j]].second) {
            if (not used[orderSmall[j]])
                q.push (orderSmall[j]);
            j++;
        }
        int lft = bound;
        while (lft && q.size ()) {
            used[q.front ()] = true;
            q.pop ();
            lft--;
        }
    }
    for (int i = 1; i <= t; i++)
        if (not used[i])
            return false;
    return true;
}
 
inline bool cmpWeak (int a, int b) {
    return toy[a].first < toy[b].first;
}
inline bool cmpSmall (int a, int b) {
    return toy[a].second < toy[b].second;
}
 
int putaway (int A, int B, int T, int X[], int Y[], int W[], int S[]) {
    a = A; b = B; t = T;
    for (int i = 1; i <= a; i++)
        x[i] = X[i - 1];
    for (int i = 1; i <= b; i++)
        y[i] = Y[i - 1];
    for (int i = 1; i <= t; i++)
        toy[i] = {W[i - 1], S[i - 1]};
    sort (x + 1, x + a + 1);
    sort (y + 1, y + b + 1);
    for (int i = 1; i <= t; i++)
        orderWeak[i] = i, orderSmall[i] = i;
    sort (orderWeak + 1, orderWeak + t + 1, cmpWeak);
    sort (orderSmall + 1, orderSmall + t + 1, cmpSmall);
    int lb = 1, rb = t, ans = -1;
    while (lb <= rb) {
        int mid = (lb + rb) / 2;
        if (check (mid))
            ans = mid, rb = mid - 1;
        else
            lb = mid + 1;
    }
    return ans;
}
 
/**
int X[1 + NA], Y[1 + NA];
int W[1 + NT], S[1 + NT];
 
int main () {
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);
 
    int A, B, T;
    cin >> A >> B >> T;
    for (int i = 0; i < A; i++)
        cin >> X[i];
    for (int i = 0; i < B; i++)
        cin >> Y[i];
    for (int i = 0; i < T; i++)
        cin >> W[i] >> S[i];
    cout << putaway (A, B, T, X, Y, W, S) << "\n";
    return 0;
}
