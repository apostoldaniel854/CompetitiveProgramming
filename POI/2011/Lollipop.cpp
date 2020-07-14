#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define pb push_back
#define dbg(x) cerr << #x << " " << x << "\n"

/**
-   Very interesting case work
-   We choose what we don't use for the lollipop => k = TotalSum - k
-   Because there is just 1 and 2 choosing the best prefix that is less than k is exactly k or k - 1
-   If it's k the problem is done, else if the last element is 1 the problem is also done
-   Else if the last element FROM THE PREFIX is 1 we substract it and add the element on position n that is guarranted to be 2
-   If none of the above is true then both elements are 2, we substract the prefix while also adding to the suffix while those elements are equal
-   If the one that we add to the suffix is 1 then we can add it and it's done
-   else we substract 1 from the prefix and add 2 to the suffix if the prefix is not empty, if it is empty it can't be done
**/

const int N = 1e6;
int type[1 + N], pref[1 + N];
int lstOne[1 + N];

int main () {
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        char ch;
        cin >> ch;
        type[i] = 1 + (ch == 'T');
    }
    for (int i = 1; i <= n; i++)
        pref[i] = pref[i - 1] + type[i];
    for (int i = 1; i <= n; i++) {
        if (type[i] == 1)
            lstOne[i] = i;
        else
            lstOne[i] = lstOne[i - 1];
    }

    while (m--) {
        int k;
        cin >> k;
        k = pref[n] - k;
        if (k < 0) {
            cout << "NIE\n";
        }
        else {
            int lb = 0, rb = n, best = 0;
            while (lb <= rb) {
                int mid = (lb + rb) / 2;
                if (pref[mid] <= k)
                    best = mid, lb = mid + 1;
                else
                    rb = mid - 1;
            }
            /// the difference if less than 1
            if (pref[best] == k) { /// 0
                cout << best + 1 << " " << n << "\n";
            }
            else {
                /// 1
                if (best == n) {
                    cout << "NIE\n";
                }
                else {
                    if (type[n] == 1) {
                        cout << best + 1 << " " << n - 1 << "\n";
                    }
                    else {
                        if (type[best] == 1) {
                            cout << best << " " << n - 1 << "\n";
                        }
                        else {
                            int x = n;
                            int oneBest = best - lstOne[best];
                            int oneX = x - lstOne[x];
                            int one = min (oneBest, oneX);
                            x -= one; best -= one;
                            if (type[x] == 1) {
                                cout << best + 1 << " " << x - 1 << "\n";
                            }
                            else {
                                if (best > 0) {
                                    best--;
                                    cout << best + 1 << " " << x - 1 << "\n";
                                }
                                else {
                                    cout << "NIE\n";
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}
